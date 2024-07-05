package net.orin.graphics.animation;

import net.orin.opengl.textures.*;

public class Animation {

	private Texture[] frames;

	private int current = 0;

	private float timer = 0.0F;

	public Animation(Texture... frames) {
		this.frames = frames;
	}

	public void tick(float speed) {
		this.timer += speed;
		if (this.timer >= 1.0F) {
			this.current++;
			if (this.current >= this.frames.length)
				this.current = 0;
			this.timer = 0.0F;
		}
	}
	
	public Texture getCurrentFrame() {
		return this.frames[this.current];
	}

}
