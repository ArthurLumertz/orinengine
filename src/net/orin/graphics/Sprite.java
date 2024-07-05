package net.orin.graphics;

import net.orin.math.*;
import net.orin.opengl.*;
import net.orin.opengl.textures.*;

public class Sprite {

	private Texture texture = null;

	private Vector2 position = Vector2.ZERO;
	private Rectangle aabb = Rectangle.ZERO;

	private float width;
	private float height;

	private Color color = Color.WHITE;
	
	public Sprite(Texture texture) {
		this.texture = texture;
		setPosition(0.0F, 0.0F);
		setSize(1.0F, 1.0F);
	}

	public void setSize(float width, float height) {
		this.width = width;
		this.height = height;
	}

	public void addPosition(Vector2 position) {
		addPosition(position.x, position.y);
	}
	
	public void addPosition(float x, float y) {
		this.position.add(x, y);
		this.aabb.x += x;
		this.aabb.y += y;
	}
	
	public void setPosition(Vector2 position) {
		addPosition(position.x, position.y);
	}

	public void setPosition(float x, float y) {
		this.position.set(x, y);
		this.aabb.set(x, y, this.width, this.height);
	}
	
	public void setTexture(Texture texture) {
		this.texture = texture;
	}
	
	public boolean intersects(Rectangle other) {
		return this.aabb.intersects(other);
	}
	
	public void setColor(Color color) {
		this.color.set(color);
	}
	
	public void setColor(float red, float green, float blue) {
		this.color.set(red, green, blue);
	}
	
	public void setColor(float red, float green, float blue, float alpha) {
		this.color.set(red, green, blue, alpha);
	}
	
	public void render(Batch batch) {
		batch.setColor(this.color);
		batch.drawTexture(this.texture, this.position, this.width, this.height);
		batch.setColor(Color.WHITE);
	}
	
	public void setX(float x) {
		this.position.x = x;
	}
	
	public void setY(float y) {
		this.position.y = y;
	}
	
	public float getX() {
		return this.position.x;
	}
	
	public float getY() {
		return this.position.y;
	}
	
	public Vector2 getPosition() {
		return this.position;
	}
	
	public Rectangle getBoundingBox() {
		return this.aabb;
	}

}
