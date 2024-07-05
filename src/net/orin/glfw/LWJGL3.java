package net.orin.glfw;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;

import org.lwjgl.opengl.*;

import net.orin.*;
import net.orin.file.*;
import net.orin.graphics.*;
import net.orin.graphics.window.*;
import net.orin.opengl.textures.*;
import net.orin.util.*;

public class LWJGL3 {

	private int fps = 60;
	private FileData iconData;

	public LWJGL3() {
		this("Game");
	}

	public LWJGL3(String title) {
		Window.setTitle(title);
		Window.setSize(854, 480);
	}

	public void setTitle(String title) {
		Window.setTitle(title);
	}

	public void setResizable(boolean resizable) {
		Window.setResizable(resizable);
	}

	public void setIcon(FileData fileData) {
		this.iconData = fileData;
	}

	public void setSize(int width, int height) {
		Window.setSize(width, height);
	}

	public void setFPS(int fps) {
		this.fps = fps;
	}

	public void create(Game game) {
		Orin.log.info("startup", "Orin Engine " + Orin.getVersion() + " initialized");
		Orin.log.info("startup", "Operating system: " + Orin.os.getFamily());

		Orin.log.info("startup", "Creating window");
		Window.create();
		Orin.log.info("startup", "Creating OpenGL capabilities");
		GL.createCapabilities();

		Orin.log.info("startup", "OpenGL version: " + Orin.graphics.getGLVersion());

		Orin.log.info("startup", "Setting OpenGL defaults");
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (this.iconData != null)
			Window.setIcon(this.iconData);

		Orin.log.info("startup", "Starting the game...");
		start(game);
	}

	public void start(Game game) {
		glfwSetTime(0);

		game.init();

		try {
			long lastTime = System.nanoTime();
			double unprocessed = 0;

			while (!Window.shouldClose()) {
				Orin.gl.viewport(Orin.graphics.getWidth(), Orin.graphics.getHeight());
				
				long now = System.nanoTime();
			    double deltaTime = (now - lastTime) / 1000000000.0;
			    lastTime = now;

			    unprocessed += deltaTime;

			    while (unprocessed >= 1.0 / this.fps) {
			        game.tick(1.0f / this.fps);
			        unprocessed -= 1.0 / this.fps;
			    }

				game.render();
				Window.update();
			}
		} catch (OrinError e) {
			Orin.log.fatal("loop", e.toString());
		} catch (OutOfMemoryError e) {
			Orin.app.freeMemory();
		} finally {
			game.dispose();
			Textures.dispose();
			Window.terminate();
		}
	}
}
