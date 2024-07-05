package net.orin.math;

public class Vector3 {

    public static final Vector3 ZERO = new Vector3(0.0F, 0.0F, 0.0F);

    public float x;
    public float y;
    public float z;

    public Vector3() {
        this(ZERO);
    }

    public Vector3(Vector3 other) {
        set(other);
    }

    public Vector3(float x, float y, float z) {
        set(x, y, z);
    }
    
    public Vector3(Vector2 other) {
        set(other.x, other.y, 0.0F);
    }

    public void set(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public void set(Vector3 other) {
        set(other.x, other.y, other.z);
    }

    public void add(float x, float y, float z) {
        this.x += x;
        this.y += y;
        this.z += z;
    }

    public void add(Vector3 other) {
        add(other.x, other.y, other.z);
    }

    public void subtract(float x, float y, float z) {
        this.x -= x;
        this.y -= y;
        this.z -= z;
    }

    public void subtract(Vector3 other) {
        subtract(other.x, other.y, other.z);
    }

    public void scale(float scalar) {
        this.x *= scalar;
        this.y *= scalar;
        this.z *= scalar;
    }

    public void normalize() {
        float length = length();
        if (length != 0.0f) {
            this.x /= length;
            this.y /= length;
            this.z /= length;
        }
    }

    public float length() {
        return (float) Math.sqrt(x * x + y * y + z * z);
    }

    public float distance(Vector3 other) {
        float dx = this.x - other.x;
        float dy = this.y - other.y;
        float dz = this.z - other.z;
        return (float) Math.sqrt(dx * dx + dy * dy + dz * dz);
    }
    
    public boolean equals(Vector3 other) {
    	if (other != null) {
    		if (other.x != this.x)
    			return false;
    		if (other.y != this.y)
    			return false;
    		if (other.z != this.z)
    			return false;
    		return true;
    	}
    	return false;
    }
    
}
