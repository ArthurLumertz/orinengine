package net.orin.graphics;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;

import org.lwjgl.glfw.*;

import net.orin.graphics.window.*;

public class Graphics {

	public void setTitle(String title) {
		Window.setTitle(title);
	}

	public void setWidth(int width) {
		Window.setSize(width, Window.getHeight());
	}

	public void setHeight(int height) {
		Window.setSize(Window.getWidth(), height);
	}

	public int getWidth() {
		return Window.getWidth();
	}

	public int getHeight() {
		return Window.getHeight();
	}

	public String getTitle() {
		return Window.getTitle();
	}

	public Monitor getPrimaryMonitor() {
		GLFWVidMode videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		return new Monitor(videoMode.width(), videoMode.height(), videoMode.refreshRate());
	}

	public String getGLVersion() {
		return glGetString(GL_VERSION);
	}

}
