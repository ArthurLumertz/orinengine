package net.orin;

import net.orin.glfw.*;
import net.orin.graphics.*;
import net.orin.opengl.*;

public class Demonstration implements Game {

	private Batch batch;
	private Camera camera;
	
	private int[][] level;
	
	@Override
	public void init() {
		this.batch = new Batch();
		this.camera = new Camera(Orin.graphics.getWidth(), Orin.graphics.getHeight(), 48);
	
		this.level = new int[100][100];
		
		for (int x = 0; x < 100; x++) {
			for (int y = 0; y < 100; y++) {
				this.level[x][y] = 1;
			}
		}
	}

	@Override
	public void tick(float deltaTime) {
		this.camera.addPosition(1 * deltaTime, 0.0F);
	}

	@Override
	public void render() {
		Orin.gl.clear(GL.COLOR);
		Orin.gl.clearColor(Color.CORNFLOWER_BLUE);

		this.batch.begin();
		this.batch.setCamera(this.camera);
		
		
		
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
