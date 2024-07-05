package net.orin.opengl;

import static org.lwjgl.opengl.GL11.*;

import net.orin.*;
import net.orin.graphics.*;
import net.orin.math.*;
import net.orin.opengl.textures.*;

public class Batch {

	private static Tessellator t = Tessellator.instance;

	public Batch() {
		setupProjection();
	}

	private void setupProjection() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, Orin.graphics.getWidth(), Orin.graphics.getHeight(), 0, -1.0F, 1.0F);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	public void pushMatrix() {
		glPushMatrix();
	}

	public void popMatrix() {
		glPopMatrix();
	}

	public void setCamera(Camera camera) {
		float zoom = camera.getZoom();
		float viewportWidth = camera.getViewportWidth();
		float viewportHeight = camera.getViewportHeight();
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewportWidth * zoom, 0, viewportHeight * zoom, -1.0F, 1.0F);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		Vector3 position = camera.getPosition();
		glTranslatef(-position.x, -position.y, -position.z);
	}

	public void begin() {
		t.init();
	}

	public void end() {
		t.flush();
	}

	public void setColor(float red, float green, float blue, float alpha) {
		t.color(red, green, blue, alpha);
	}

	public void setColor(float red, float green, float blue) {
		setColor(red, green, blue, 1.0F);
	}

	public void setColor(Color color) {
		setColor(color.red, color.green, color.blue, color.alpha);
	}

	public void setColor(int color) {
		float red = (color >> 16 & 0xFF) / 255.0F;
		float green = (color >> 8 & 0xFF) / 255.0F;
		float blue = (color & 0xFF) / 255.0F;
		setColor(red, green, blue);
	}

	public void drawTexture(Texture texture, float x, float y, float width, float height) {
		if (texture == null)
			texture = new Texture(Orin.files.internal("unknown.png"));
		texture.bind();
		t.vertexUV(x, y, 0.0F, texture.getTextureData().getTextureU0(), texture.getTextureData().getTextureV0());
		t.vertexUV(x + width, y, 0.0F, texture.getTextureData().getTextureU1(), texture.getTextureData().getTextureV0());
		t.vertexUV(x + width, y + height, 0.0F, texture.getTextureData().getTextureU1(), texture.getTextureData().getTextureV1());
		t.vertexUV(x, y + height, 0.0F, texture.getTextureData().getTextureU0(), texture.getTextureData().getTextureV1());
	}
	
	public void drawTexture(Texture texture, Vector2 position, float width, float height) {
		drawTexture(texture, position.x, position.y, width, height);
	}

	public void drawRect(float x, float y, float width, float height) {
		t.vertex(x, y, 0.0F);
		t.vertex(x + width, y, 0.0F);
		t.vertex(x + width, y + height, 0.0F);
		t.vertex(x, y + height, 0.0F);
	}

	public void enableTextures() {
		glEnable(GL_TEXTURE_2D);
	}

	public void disableTextures() {
		glDisable(GL_TEXTURE_2D);
	}

	public void enableBlending() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	public void disableBlending() {
		glDisable(GL_BLEND);
	}
	
	public void dispose() {
		t.dispose();
	}

}
