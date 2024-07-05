package net.orin.graphics.window;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.system.MemoryUtil.*;

import java.awt.image.*;
import java.io.*;
import java.nio.*;

import javax.imageio.*;

import org.lwjgl.*;
import org.lwjgl.glfw.*;

import net.orin.*;
import net.orin.file.*;
import net.orin.glfw.input.*;
import net.orin.graphics.*;

public class Window {

	public static long window;
	public static int width;
	public static int height;
	public static boolean resizable = true;
	public static boolean fullscreen = false;
	public static String title;

	public static void setTitle(String title) {
		if (title == null || title.equalsIgnoreCase(""))
			title = "Game";
		if (Window.window != NULL)
			glfwSetWindowTitle(window, title);

		Window.title = title;
	}

	public static void setFullscreen(boolean fullscreen) {
		Monitor monitor = Orin.graphics.getPrimaryMonitor();

		if (fullscreen) {
			setSize(monitor.getWidth(), monitor.getHeight());
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, monitor.getWidth(), monitor.getHeight(), monitor.getRefreshRate());
		} else {
			setSize(854, 480);
			glfwSetWindowMonitor(window, 0, (monitor.getWidth() - 854) / 2, (monitor.getHeight() - 480) / 2, 854, 480, 0);
		}
		Window.fullscreen = fullscreen;
	}

	public static void setResizable(boolean resizable) {
		Window.resizable = resizable;
	}

	public static void setSize(int width, int height) {
		if (width <= 0)
			width = 1;
		if (height <= 0)
			height = 1;
		if (Window.window != NULL)
			glfwSetWindowSize(window, width, height);

		Window.width = width;
		Window.height = height;
	}

	public static void create() {
		if (!glfwInit())
			throw new IllegalStateException("Failed to initialize GLFW!");

		glfwWindowHint(GLFW_RESIZABLE, (resizable ? GLFW_TRUE : GLFW_FALSE));
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
			throw new RuntimeException("Failed to create GLFW window!");

		GLFWVidMode videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, (videoMode.width() - width) / 2, (videoMode.height() - height) / 2);

		glfwSetKeyCallback(window, Orin.input);
		glfwSetCursorPosCallback(window, new Input.MousePos());
		glfwSetMouseButtonCallback(window, new Input.MouseButton());

		glfwSetWindowSizeCallback(window, new GLFWWindowSizeCallback() {
			@Override
			public void invoke(long window, int width, int height) {
				setSize(width, height);
			}
		});

		glfwMakeContextCurrent(window);

		glfwShowWindow(window);
	}

	public static void setIcon(FileData fileData) {
		if (window == NULL)
			return;
		try {
			BufferedImage image = ImageIO.read(Orin.class.getResourceAsStream(fileData.getPath()));
			int width = image.getWidth();
			int height = image.getHeight();
			int[] rawPixels = new int[width * height];
			image.getRGB(0, 0, width, height, rawPixels, 0, width);

			for (int i = 0; i < rawPixels.length; i++) {
				int alpha = rawPixels[i] >> 24 & 0xFF;
				int red = rawPixels[i] >> 16 & 0xFF;
				int green = rawPixels[i] >> 8 & 0xFF;
				int blue = rawPixels[i] & 0xFF;
				rawPixels[i] = alpha << 24 | blue << 16 | green << 8 | red;
			}

			ByteBuffer byteBuffer = BufferUtils.createByteBuffer(width * height * 4);
			byteBuffer.asIntBuffer().put(rawPixels);

			GLFWImage.Buffer imageBuffer = GLFWImage.malloc(1);
			GLFWImage iconImage = GLFWImage.malloc();

			iconImage.set(width, height, byteBuffer);
			imageBuffer.put(0, iconImage);

			glfwSetWindowIcon(window, imageBuffer);

			iconImage.free();
			imageBuffer.free();
		} catch (IOException e) {
			Orin.log.fatal("window", "Something went wrong while trying to set GLFW icon!");
		}
	}

	public static boolean shouldClose() {
		return glfwWindowShouldClose(window);
	}

	public static void update() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	public static void close() {
		glfwSetWindowShouldClose(window, true);
	}

	public static void terminate() {
		glfwTerminate();
	}

	public static int getWidth() {
		return width;
	}

	public static int getHeight() {
		return height;
	}

	public static String getTitle() {
		return title;
	}

	public static boolean isResizable() {
		return resizable;
	}

	public static boolean isFullscreen() {
		return fullscreen;
	}

}
