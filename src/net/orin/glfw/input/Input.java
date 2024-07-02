package net.orin.glfw.input;

import static org.lwjgl.glfw.GLFW.*;

import org.lwjgl.glfw.GLFWCursorPosCallback;
import org.lwjgl.glfw.GLFWKeyCallback;
import org.lwjgl.glfw.GLFWMouseButtonCallback;

public class Input extends GLFWKeyCallback {
	
	private static int x;
	private static int y;

	private static boolean[] keys = new boolean[GLFW_KEY_LAST];
	private static boolean[] keysJustPressed = new boolean[GLFW_KEY_LAST];

    private static boolean[] buttons = new boolean[GLFW_MOUSE_BUTTON_LAST];
    private static boolean[] buttonsJustPressed = new boolean[GLFW_MOUSE_BUTTON_LAST];

	@Override
	public void invoke(long window, int key, int scancode, int action, int mods) {
		if (key >= 0 && key < GLFW_KEY_LAST) {
			keys[key] = action != GLFW_RELEASE;
			keysJustPressed[key] = action == GLFW_PRESS;
		}
	}

	public boolean isKeyPressed(int key) {
		if (key > 0 && key < GLFW_KEY_LAST) {
			return keys[key];
		}
		return false;
	}

	public boolean isKeyJustPressed(int key) {
		if (key > 0 && key < GLFW_KEY_LAST) {
			boolean result = keysJustPressed[key];
			keysJustPressed[key] = false;
			return result;
		}
		return false;
	}
	
	public boolean isButtonPressed(int button) {
        if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
            return buttons[button];
        }
        return false;
    }

    public boolean isButtonJustPressed(int button) {
        if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
            boolean result = buttonsJustPressed[button];
            buttonsJustPressed[button] = false;
            return result;
        }
        return false;
    }
    
    public boolean isTouched() {
    	return isButtonPressed(0);
    }
    
    public boolean isJustTouched() {
    	return isButtonJustPressed(0);
    }
	
	public int getX() {
		return x;
	}
	
	public int getY() {
		return y;
	}
	
	public static class MousePos extends GLFWCursorPosCallback {

		@Override
		public void invoke(long window, double x, double y) {
			Input.x = (int) x;
			Input.y = (int) y;
		}
		
	}
	
	public static class MouseButton extends GLFWMouseButtonCallback {

		@Override
        public void invoke(long window, int button, int action, int mods) {
			if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
                buttons[button] = action != GLFW_RELEASE;
                buttonsJustPressed[button] = action == GLFW_PRESS;
            }
		}
		
	}

}
