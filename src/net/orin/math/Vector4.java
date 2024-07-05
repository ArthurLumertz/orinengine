package net.orin.math;

public class Vector4 {

	public static final Vector4 ZERO = new Vector4(0.0F, 0.0F, 0.0F, 0.0F);

	public float x;
	public float y;
	public float z;
	public float w;

	public Vector4() {
		this(ZERO);
	}

	public Vector4(Vector4 other) {
		set(other);
	}

	public Vector4(float x, float y, float z, float w) {
		set(x, y, z, w);
	}

	public void set(float x, float y, float z, float w) {
		this.x = x;
		this.y = y;
		this.z = z;
		this.w = w;
	}

	public void set(Vector4 other) {
		set(other.x, other.y, other.z, other.w);
	}

	public void add(float x, float y, float z, float w) {
		this.x += x;
		this.y += y;
		this.z += z;
		this.w += w;
	}

	public void add(Vector4 other) {
		add(other.x, other.y, other.z, other.w);
	}

	public void subtract(float x, float y, float z, float w) {
		this.x -= x;
		this.y -= y;
		this.z -= z;
		this.w -= w;
	}

	public void subtract(Vector4 other) {
		subtract(other.x, other.y, other.z, other.w);
	}

	public void scale(float scalar) {
		this.x *= scalar;
		this.y *= scalar;
		this.z *= scalar;
		this.w *= scalar;
	}

	public void normalize() {
		float length = length();
		if (length != 0.0f) {
			this.x /= length;
			this.y /= length;
			this.z /= length;
			this.w /= length;
		}
	}

	public float length() {
		return (float) Math.sqrt(x * x + y * y + z * z + w * w);
	}

	public float distance(Vector4 other) {
		float dx = this.x - other.x;
		float dy = this.y - other.y;
		float dz = this.z - other.z;
		float dw = this.w - other.w;
		return (float) Math.sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
	}

    @Deprecated
	public boolean equals(Vector4 other) {
		if (other != null) {
			if (other.x != this.x)
				return false;
			if (other.y != this.y)
				return false;
			if (other.z != this.z)
				return false;
			if (other.w != this.w)
				return false;
			return true;
		}
		return false;
	}

}
