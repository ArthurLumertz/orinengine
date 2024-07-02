package net.orin;

import net.orin.glfw.LWJGL3;
import net.orin.graphics.Camera;
import net.orin.graphics.Color;
import net.orin.graphics.Game;
import net.orin.opengl.Batch;
import net.orin.opengl.GL;
import net.orin.opengl.textures.Texture;

public class Demonstration extends Game {

	private Batch batch;
	private Camera camera;

	private Texture tex;

	@Override
	public void init() {
		this.batch = new Batch();
		this.camera = new Camera(Orin.graphics.getWidth(), Orin.graphics.getHeight());
	}

	@Override
	public void tick(float deltaTime) {

	}

	@Override
	public void render() {
		Orin.gl.clear(GL.COLOR);
		Orin.gl.clearColor(Color.BLACK);
		
		this.batch.begin();
		this.batch.setCamera(this.camera);
		this.batch.drawTexture(this.tex, 0.0F, 0.0F, 32.0F, 32.0F);
		this.batch.end();
	}

	@Override
	public void exit() {
		
	}

	public static void main(String[] args) {
		LWJGL3 app = new LWJGL3();
		app.setFPS(60);
		app.create(new Demonstration());
	}

}
