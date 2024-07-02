package net.orin.math;

import java.util.*;

public class Maths {

	private static Random random = new Random();

	public static byte clamp(byte value, byte minimum, byte maximum) {
		if (value < minimum)
			value = minimum;
		if (value > maximum)
			value = maximum;
		return value;
	}

	public static short clamp(short value, short minimum, short maximum) {
		if (value < minimum)
			value = minimum;
		if (value > maximum)
			value = maximum;
		return value;
	}

	public static int clamp(int value, int minimum, int maximum) {
		if (value < minimum)
			value = minimum;
		if (value > maximum)
			value = maximum;
		return value;
	}

	public static float clamp(float value, float minimum, float maximum) {
		if (value < minimum)
			value = minimum;
		if (value > maximum)
			value = maximum;
		return value;
	}

	public static double clamp(double value, double minimum, double maximum) {
		if (value < minimum)
			value = minimum;
		if (value > maximum)
			value = maximum;
		return value;
	}

	public static long clamp(long value, long minimum, long maximum) {
		if (value < minimum)
			value = minimum;
		if (value > maximum)
			value = maximum;
		return value;
	}

	public static byte random(byte min, byte max) {
		return (byte) (random.nextInt(max - min + 1) + min);
	}

	public static short random(short min, short max) {
		return (short) (random.nextInt(max - min + 1) + min);
	}

	public static int random(int min, int max) {
		return random.nextInt(max - min + 1) + min;
	}

	public static float random(float min, float max) {
		return random.nextFloat() * (max - min) + min;
	}

	public static double random(double min, double max) {
		return random.nextDouble() * (max - min) + min;
	}

	public static long random(long min, long max) {
		return (long) (random.nextDouble() * (max - min + 1) + min);
	}

}
