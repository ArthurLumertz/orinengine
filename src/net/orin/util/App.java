package net.orin.util;

import net.orin.*;
import net.orin.graphics.window.*;

public class App {
	
	public void exit() {
		Orin.log.debug("app", "Exiting game...");
		Window.close();
		System.exit(0);
	}
	
	public void freeMemory() {
		Orin.log.debug("app", "Freeing memory...");
		System.gc();
	}

}
