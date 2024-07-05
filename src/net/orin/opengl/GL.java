package net.orin.opengl;

import static org.lwjgl.opengl.GL11.*;

import net.orin.graphics.*;

public class GL {

	public static final int COLOR = GL_COLOR_BUFFER_BIT;
	public static final int DEPTH = GL_DEPTH_BUFFER_BIT;
	public static final int LEQUAL = GL_LEQUAL;
	public static final int SMOOTH = GL_SMOOTH;
	public static final int TRUE = GL_TRUE;
	public static final int FALSE = GL_FALSE;
	public static final int NO_ERROR = GL_NO_ERROR;
	
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
	
	public void clearDepth(double depth) {
		glClearDepth(depth);
	}
	
	public void depthFunc(int func) {
		glDepthFunc(func);
	}
	
	public int getError() {
		return glGetError();
	}
	
	public String getString(int name) {
		return glGetString(name);
	}

	public void clearColor(int color) {
		float red = (color >> 16 & 0xFF) / 255.0F;
		float green = (color >> 8 & 0xFF) / 255.0F;
		float blue = (color & 0xFF) / 255.0F;
		clearColor(red, green, blue);
	}
	
	public void viewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
	}
	
	public void viewport(int width, int height) {
		viewport(0, 0, width, height);
	}

}
