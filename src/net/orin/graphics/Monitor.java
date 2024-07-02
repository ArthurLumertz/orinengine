package net.orin.graphics;

public class Monitor {

	private final int width;
	private final int height;
	private final int refreshRate;

	public Monitor(int width, int height, int refreshRate) {
		this.width = width;
		this.height = height;
		this.refreshRate = refreshRate;
	}

	public int getWidth() {
		return this.width;
	}

	public int getHeight() {
		return this.height;
	}

	public int getRefreshRate() {
		return this.refreshRate;
	}

}
