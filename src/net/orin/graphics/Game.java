package net.orin.graphics;

public interface Game {

	void init();

	void tick(float deltaTime);

	void render();
	
	void dispose();

}
