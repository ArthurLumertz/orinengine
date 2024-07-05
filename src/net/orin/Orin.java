package net.orin;

import net.orin.file.*;
import net.orin.glfw.input.*;
import net.orin.graphics.*;
import net.orin.opengl.*;
import net.orin.system.*;
import net.orin.util.*;

public class Orin {

	private static final String RUNNING_VERSION = "0.0.2a";

	public static Input input = new Input();
	public static Graphics graphics = new Graphics();
	public static OperatingSystem os = new OperatingSystem();
	public static Files files = new Files();
	public static Logger log = new Logger();
	public static App app = new App();
	public static GL gl = new GL();
	
	public static String getVersion() {
		return RUNNING_VERSION;
	}
	
}
