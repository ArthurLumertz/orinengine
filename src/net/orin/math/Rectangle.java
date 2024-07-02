package net.orin.math;

public class Rectangle {

	public float x;
	public float y;
	public float width;
	public float height;

	public Rectangle(float x, float y, float width, float height) {
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}

	public void set(float x, float y, float width, float height) {
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}

	public void set(Rectangle other) {
		set(other.x, other.y, other.width, other.height);
	}

	public boolean contains(float px, float py) {
		return (px >= this.x && px <= this.x + this.width && py >= this.y && py <= this.y + this.height);
	}

	public boolean intersects(Rectangle other) {
		return (this.x < other.x + other.width && this.x + this.width > other.x && this.y < other.y + other.height && this.y + this.height > other.y);
	}

	public Rectangle grow(float x, float y) {
		this.x -= x;
		this.y -= y;
		this.width += x;
		this.height += y;
		return new Rectangle(this.x, this.y, this.width, this.height);
	}

	public boolean equals(Rectangle other) {
		if (other != null) {
			if (other.x != this.x)
				return false;
			if (other.y != this.y)
				return false;
			if (other.width != this.width)
				return false;
			if (other.height != this.height)
				return false;
			return true;
		}
		return false;
	}

}
