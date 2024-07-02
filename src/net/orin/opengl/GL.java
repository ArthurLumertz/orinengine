package net.orin.opengl;

import static org.lwjgl.opengl.GL11.*;

import net.orin.graphics.*;

public class GL {

	public static final int COLOR = GL_COLOR_BUFFER_BIT;
	public static final int DEPTH = GL_DEPTH_BUFFER_BIT;
	public static final int INVALID = -1;
	
	public void clear(int mask) {
		glClear(mask);
	}

	public void clearColor(float red, float green, float blue, float alpha) {
		glClearColor(red, green, blue, alpha);
	}

	public void clearColor(float red, float green, float blue) {
		clearColor(red, green, blue, 1.0F);
	}

	public void clearColor(Color color) {
		clearColor(color.red, color.green, color.blue, color.alpha);
	}

	public void clearColor(int color) {
		float red = (color >> 16 & 0xFF) / 255.0F;
		float green = (color >> 8 & 0xFF) / 255.0F;
		float blue = (color & 0xFF) / 255.0F;
		clearColor(red, green, blue);
	}

}
