package net.orin.graphics;

import net.orin.math.*;

public class Camera {

	public Vector3 position = new Vector3();
	public float zoom = 1.0F;
	
	public int viewportWidth;
	public int viewportHeight;

	public Camera(int viewportWidth, int viewportHeight) {
		setPosition(0.0F, 0.0F);
		setSize(viewportWidth, viewportHeight);
	}
	
	public void setZoom(float zoom) {
		this.zoom = zoom;
	}

	public void setSize(int viewportWidth, int viewportHeight) {
		this.viewportWidth = viewportWidth;
		this.viewportHeight = viewportHeight;
	}

	public void setPosition(float x, float y, float z) {
		this.position.set(x, y, z);
	}

	public void setPosition(float x, float y) {
		this.position.set(x, y, 0.0F);
	}

	public void setPosition(Vector3 position) {
		this.position = new Vector3(position);
	}

	public void setPosition(Vector2 position) {
		this.position.x = position.x;
		this.position.y = position.y;
		this.position.z = 0.0F;
	}
	
	public Rectangle getViewRectangle() {
		return new Rectangle(this.position.x, this.position.y, this.viewportWidth, this.viewportHeight);
	}

}
