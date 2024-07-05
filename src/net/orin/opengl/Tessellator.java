package net.orin.opengl;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

import java.nio.*;

import org.lwjgl.system.jemalloc.*;

import net.orin.*;

public class Tessellator {

	public static Tessellator instance = new Tessellator();

	public static final int MAX_VERTICES = 10000;

	private FloatBuffer vertexBuffer;
	private FloatBuffer textureCoordinateBuffer;
	private ByteBuffer colorBuffer;

	private int vertices = 0;

	private boolean hasTexture = false;
	private float textureU;
	private float textureV;

	private boolean hasColor = false;
	private float red;
	private float green;
	private float blue;
	private float alpha;

	public Tessellator() {
		ByteBuffer vertexBufferAddress = JEmalloc.je_malloc(MAX_VERTICES * 3 * Float.BYTES);
		ByteBuffer textureCoordinateBufferAddress = JEmalloc.je_malloc(MAX_VERTICES * 2 * Float.BYTES);
		ByteBuffer colorBufferAddress = JEmalloc.je_malloc(MAX_VERTICES * 4 * Float.BYTES);

		if (vertexBufferAddress == null || textureCoordinateBufferAddress == null || colorBufferAddress == null) {
			throw new OutOfMemoryError("Failed to allocate memory using jemalloc");
		}

		this.vertexBuffer = memFloatBuffer(memAddress(vertexBufferAddress), MAX_VERTICES * 3);
		this.textureCoordinateBuffer = memFloatBuffer(memAddress(textureCoordinateBufferAddress), MAX_VERTICES * 2);
		this.colorBuffer = colorBufferAddress;
	}

	public void init() {
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
		if (this.vertices > 0) {
			this.vertexBuffer.flip();
			this.textureCoordinateBuffer.flip();
			this.colorBuffer.flip();

			glVertexPointer(3, GL_FLOAT, GL_POINTS, this.vertexBuffer);
			if (this.hasTexture)
				glTexCoordPointer(2, GL_FLOAT, GL_POINTS, this.textureCoordinateBuffer);
			if (this.hasColor)
				glColorPointer(4, GL_BYTE, GL_POINTS, this.colorBuffer);

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
		}
	}

	public void vertex(float x, float y, float z) {
		this.vertexBuffer.put(this.vertices * 3, x);
		this.vertexBuffer.put(this.vertices * 3 + 1, y);
		this.vertexBuffer.put(this.vertices * 3 + 2, z);

		if (this.hasTexture) {
            this.textureCoordinateBuffer.put(this.vertices * 2, this.textureU);
            this.textureCoordinateBuffer.put(this.vertices * 2 + 1, this.textureV);
		}
		if (this.hasColor) {
			this.colorBuffer.put(this.vertices * 4, (byte) (this.red * 127));
			this.colorBuffer.put(this.vertices * 4 + 1, (byte) (this.green * 127));
			this.colorBuffer.put(this.vertices * 4 + 2, (byte) (this.blue * 127));
			this.colorBuffer.put(this.vertices * 4 + 3, (byte) (this.alpha * 127));
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

	public void dispose() {
		JEmalloc.je_free(this.vertexBuffer);
		JEmalloc.je_free(this.textureCoordinateBuffer);
		JEmalloc.je_free(this.colorBuffer);
	}

}
