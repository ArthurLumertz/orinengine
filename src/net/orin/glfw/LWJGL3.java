package net.orin.glfw;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;

import org.lwjgl.opengl.GL;

import net.orin.Orin;
import net.orin.file.FileData;
import net.orin.graphics.Game;
import net.orin.graphics.window.Window;
import net.orin.opengl.textures.Textures;
import net.orin.util.OrinError;

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

		long lastTime = System.nanoTime();
		double nsPerTick = 1000000000.0 / this.fps;
		double unprocessed = 0;

		try {
			while (!Window.shouldClose()) {
				long now = System.nanoTime();
				unprocessed += (now - lastTime) / nsPerTick;
				lastTime = now;

				while (unprocessed >= 1) {
					double deltaTime = glfwGetTime();
					glfwSetTime(0);

					game.tick((float) deltaTime);
					game.render();

					Window.update();

					unprocessed -= 1;
				}
			}
		} catch (OrinError e) {
			Orin.log.fatal("loop", e.toString());
		} catch (OutOfMemoryError e) {
			Orin.app.freeMemory();
		} finally {
			game.exit();
			
			Textures.dispose();			
			Window.terminate();
		}
	}

}
