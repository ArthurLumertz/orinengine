package net.orin;

import net.orin.glfw.*;
import net.orin.graphics.*;
import net.orin.opengl.*;

public class Demonstration implements Game {

	private Batch batch;
	private Camera camera;

	private Sprite sprite;

	@Override
	public void init() {
		this.batch = new Batch();
		this.camera = new Camera(48);

		this.sprite = new Sprite(null);
	}

	@Override
	public void tick(float deltaTime) {
		this.sprite.addPosition(1.0F * deltaTime, 0.0F);
	}

	@Override
	public void render() {
		Orin.gl.clear(GL.COLOR);
		Orin.gl.clearColor(Color.CORNFLOWER_BLUE);

		this.batch.setCamera(this.camera);

		this.batch.begin();
		this.sprite.render(this.batch);
		this.batch.end();
	}

	@Override
	public void dispose() {
		this.batch.dispose();
	}

	public static void main(String[] args) {
		LWJGL3 app = new LWJGL3();
		app.setResizable(true);
		app.setFPS(60);
		app.create(new Demonstration());
	}

}
