package net.orin.util;

import java.awt.Desktop;
import java.awt.Desktop.Action;
import java.net.URI;

public class Sys {

	public static void openURL(String url) {
		try {
			Desktop desktop = Desktop.getDesktop();
			if (desktop.isSupported(Action.BROWSE)) {
				desktop.browse(new URI(url));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
}
