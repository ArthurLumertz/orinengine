package net.orin.graphics;

public abstract class Game {

	public abstract void init();

	public abstract void tick(float deltaTime);

	public abstract void render();
	
	public abstract void exit();

}
