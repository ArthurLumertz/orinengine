package net.orin.graphics;

import net.orin.math.*;

public class Color {
	
	public static final Color WHITE = new Color(1.0F, 1.0F, 1.0F);
	public static final Color GRAY = new Color(0.5F, 0.5F, 0.5F);
	public static final Color BLACK = new Color(0.0F, 0.0F, 0.0F);
	public static final Color RED = new Color(1.0F, 0.0F, 0.0F);
	public static final Color GREEN = new Color(0.0F, 1.0F, 0.0F);
	public static final Color BLUE = new Color(0.0F, 0.0F, 1.0F);
	public static final Color CORNFLOWER_BLUE = new Color(0.39F, 0.58F, 0.92F);
	public static final Color YELLOW = new Color(1.0F, 1.0F, 0.0F);
	public static final Color ORANGE = new Color(1.0F, 0.5F, 0.0F);
	public static final Color MAGENTA = new Color(1.0F, 0.0F, 1.0F);
	public static final Color PURPLE = new Color(0.4F, 0.0F, 1.0F);
	public static final Color BROWN = new Color(0.38F, 0.31F, 0.21F);

	public float red;
	public float green;
	public float blue;
	public float alpha;
	
	public Color(float red, float green, float blue) {
		this(red, green, blue, 1.0F);
	}
	
	public Color(float red, float green, float blue, float alpha) {
		this.red = Maths.clamp(red, 0.0F, 1.0F);
		this.green = Maths.clamp(green, 0.0F, 1.0F);
		this.blue = Maths.clamp(blue, 0.0F, 1.0F);
		this.alpha = Maths.clamp(alpha, 0.0F, 1.0F);
	}
	
}
