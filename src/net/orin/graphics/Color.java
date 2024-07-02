package net.orin.graphics;

public class Color {
	
	public static final Color WHITE = new Color(1.0F, 1.0F, 1.0F);
	public static final Color BLACK = new Color(0.0F, 0.0F, 0.0F);
	public static final Color RED = new Color(1.0F, 0.0F, 0.0F);
	public static final Color GREEN = new Color(0.0F, 1.0F, 0.0F);
	public static final Color BLUE = new Color(0.0F, 0.0F, 1.0F);

	public float red;
	public float green;
	public float blue;
	public float alpha;
	
	public Color(float red, float green, float blue) {
		this(red, green, blue, 1.0F);
	}
	
	public Color(float red, float green, float blue, float alpha) {
		this.red = red;
		this.green = green;
		this.blue = blue;
		this.alpha = alpha;
	}
	
}
