package net.orin.graphics;

import net.orin.*;
import net.orin.math.*;

public class Camera {

	private Vector3 position = new Vector3();
	private float zoom = 1.0F;

	private int unitSize = 1;

	private int viewportWidth;
	private int viewportHeight;

	public Camera() {
		this(Orin.graphics.getWidth(), Orin.graphics.getHeight(), 1);
	}
	
	public Camera(int unitSize) {
		this(Orin.graphics.getWidth(), Orin.graphics.getHeight(), unitSize);
	}
	
	public Camera(int viewportWidth, int viewportHeight, int unitSize) {
		setPosition(0.0F, 0.0F);
		setUnitSize(unitSize);
		setSize(viewportWidth, viewportHeight);
	}

	public void setSize(int viewportWidth, int viewportHeight) {
		this.viewportWidth = viewportWidth / this.unitSize;
		this.viewportHeight = viewportHeight / this.unitSize;
	}

	public void addPosition(Vector3 position) {
		this.position.add(position);
	}

	public void addPosition(float x, float y, float z) {
		this.position.add(x, y, z);
	}

	public void addPosition(Vector2 position) {
		this.position.add(new Vector3(position));
	}

	public void addPosition(float x, float y) {
		this.position.add(x, y, 0.0F);
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
		this.position = new Vector3(position);
	}

	public Rectangle getViewRectangle() {
		return new Rectangle(this.position.x / this.unitSize, this.position.y / this.unitSize, this.viewportWidth / this.unitSize, this.viewportHeight / this.unitSize);
	}

	public Vector3 getPosition() {
		return this.position;
	}

	public int getViewportWidth() {
		return this.viewportWidth;
	}

	public int getViewportHeight() {
		return this.viewportHeight;
	}

	public void setUnitSize(int unitSize) {
		this.unitSize = unitSize;
	}

	public int getUnitSize() {
		return this.unitSize;
	}

	public void setZoom(float zoom) {
		this.zoom = zoom;
	}

	public float getZoom() {
		return this.zoom;
	}

}
