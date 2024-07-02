package net.orin.opengl;

import static org.lwjgl.opengl.GL11.*;

import java.nio.*;

import org.lwjgl.*;

import net.orin.*;

public class Tessellator {

	public static Tessellator instance = new Tessellator();

	public static final int MAX_VERTICES = 10000;

	private final FloatBuffer vertexBuffer = BufferUtils.createFloatBuffer(MAX_VERTICES * 3);
	private final FloatBuffer textureCoordinateBuffer = BufferUtils.createFloatBuffer(MAX_VERTICES * 2);
	private final FloatBuffer colorBuffer = BufferUtils.createFloatBuffer(MAX_VERTICES * 4);

	private int vertices = 0;

	private boolean hasTexture = false;
	private float textureU;
	private float textureV;

	private boolean hasColor = false;
	private float red;
	private float green;
	private float blue;
	private float alpha;

	private boolean drawing = false;

	public void init() {
		this.drawing = true;
		clear();
	}

	public void clear() {		
		this.vertexBuffer.clear();
		this.textureCoordinateBuffer.clear();
		this.colorBuffer.clear();
		this.hasTexture = false;
		this.hasColor = false;
		this.vertices = 0;
	}

	public void flush() {
		if (!this.drawing) {
			Orin.log.fatal("tessellator", "begin() must be called before end()!");
			Orin.app.exit();
		}
		
		this.drawing = false;
		if (this.vertices > 0) {
			this.vertexBuffer.flip();
			this.textureCoordinateBuffer.flip();
			this.colorBuffer.flip();

			glVertexPointer(3, GL_FLOAT, GL_POINTS, this.vertexBuffer);
			if (this.hasTexture)
				glTexCoordPointer(2, GL_FLOAT, GL_POINTS, this.textureCoordinateBuffer);
			if (this.hasColor)
				glColorPointer(4, GL_FLOAT, GL_POINTS, this.colorBuffer);

			glEnableClientState(GL_VERTEX_ARRAY);
			if (this.hasTexture)
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			if (this.hasColor)
				glEnableClientState(GL_COLOR_ARRAY);

			glDrawArrays(GL_QUADS, GL_POINTS, this.vertices);

			glDisableClientState(GL_VERTEX_ARRAY);
			if (this.hasTexture)
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			if (this.hasColor)
				glDisableClientState(GL_COLOR_ARRAY);

			clear();
		} else {
			Orin.log.warn("tessellator", "Vertices cannot be 0!");
		}
	}

	public void vertex(float x, float y, float z) {
		if (!this.drawing) {
			Orin.log.fatal("tessellator", "begin() must be called before vertex()!");
			Orin.app.exit();
			return;
		}
		
		this.vertexBuffer.put(this.vertices * 3, x);
		this.vertexBuffer.put(this.vertices * 3 + 1, y);
		this.vertexBuffer.put(this.vertices * 3 + 2, z);

		if (this.hasTexture) {
			this.textureCoordinateBuffer.put(this.vertices * 2, this.textureU);
			this.textureCoordinateBuffer.put(this.vertices * 2 + 1, this.textureV);
		}
		if (this.hasColor) {
			this.colorBuffer.put(this.vertices * 4, this.red);
			this.colorBuffer.put(this.vertices * 4 + 1, this.green);
			this.colorBuffer.put(this.vertices * 4 + 2, this.blue);
			this.colorBuffer.put(this.vertices * 4 + 3, this.alpha);
		}

		this.vertices++;
		if (this.vertices >= MAX_VERTICES)
			flush();
	}

	public void texture(float textureU, float textureV) {
		this.hasTexture = true;
		this.textureU = textureU;
		this.textureV = textureV;
	}

	public void vertexUV(float x, float y, float z, float textureU, float textureV) {
		texture(textureU, textureV);
		vertex(x, y, z);
	}

	public void color(float red, float green, float blue, float alpha) {
		this.hasColor = true;
		this.red = red;
		this.green = green;
		this.blue = blue;
		this.alpha = alpha;
	}

}
