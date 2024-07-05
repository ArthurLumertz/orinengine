package net.orin.math;

public class Vector2 {

    public static final Vector2 ZERO = new Vector2(0.0F, 0.0F);

    public float x;
    public float y;

    public Vector2() {
        this(ZERO);
    }

    public Vector2(Vector2 other) {
        set(other);
    }

    public Vector2(float x, float y) {
        set(x, y);
    }

    public void set(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public void set(Vector2 other) {
        set(other.x, other.y);
    }

	public void add(float x, float y) {
		this.x += x;
        this.y += y;
    }

    public void add(Vector2 other) {
        add(other.x, other.y);
    }

    public void subtract(float x, float y) {
        this.x -= x;
        this.y -= y;
    }

    public void subtract(Vector2 other) {
        subtract(other.x, other.y);
    }

    public void scale(float scalar) {
        this.x *= scalar;
        this.y *= scalar;
    }

    public void normalize() {
        float length = length();
        if (length != 0.0f) {
            this.x /= length;
            this.y /= length;
        }
    }

    public float length() {
        return (float) Math.sqrt(x * x + y * y);
    }

    public float distance(Vector2 other) {
        float dx = this.x - other.x;
        float dy = this.y - other.y;
        return (float) Math.sqrt(dx * dx + dy * dy);
    }
    
    @Deprecated
    public boolean equals(Vector2 other) {
    	if (other != null) {
    		if (other.x != this.x)
    			return false;
    		if (other.y != this.y)
    			return false;
    		return true;
    	}
    	return false;
    }
    
}
