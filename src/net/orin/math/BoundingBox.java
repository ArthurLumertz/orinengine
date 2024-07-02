package net.orin.math;

public class BoundingBox {

	public float x0;
	public float y0;
	public float x1;
	public float y1;

	public BoundingBox(float x0, float y0, float x1, float y1) {
		this.x0 = x0;
		this.y0 = y0;
		this.x1 = x1;
		this.y1 = y1;
	}

	public void set(float x0, float y0, float x1, float y1) {
		this.x0 = x0;
		this.y0 = y0;
		this.x1 = x1;
		this.y1 = y1;
	}

	public void set(BoundingBox other) {
		this.x0 = other.x0;
		this.y0 = other.y0;
		this.x1 = other.x1;
		this.y1 = other.y1;
	}

	public boolean intersects(BoundingBox other) {
		return (this.x1 > other.x0 && this.x0 < other.x1 && this.y1 > other.y0 && this.y0 < other.y1);
	}

	public BoundingBox grow(float x, float y) {
		this.x0 -= x;
		this.y0 -= y;
		this.x1 += x;
		this.y1 += y;
		return new BoundingBox(this.x0, this.y0, this.x1, this.y1);
	}

	public boolean equals(BoundingBox other) {
		if (other != null) {
			if (other.x0 != this.x0)
				return false;
			if (other.y0 != this.y0)
				return false;
			if (other.x1 != this.x1)
				return false;
			if (other.y1 != this.y1)
				return false;
			return true;
		}
		return false;
	}

}
