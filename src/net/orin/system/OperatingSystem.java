package net.orin.system;

import java.awt.*;
import java.awt.Desktop.*;
import java.net.*;

public class OperatingSystem {
	
	public void openURL(String url) {
		try {
			Desktop desktop = Desktop.getDesktop();
			if (desktop.isSupported(Action.BROWSE)) {
				desktop.browse(new URI(url));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public enum OS {
		WINDOWS, MAC, LINUX, SOLARIS, UNIX, UNKNOWN
	}

	public OS getOs() {
		String osName = getFamily().toLowerCase();
		if (osName.contains("win"))
	        return OS.WINDOWS;
	    if (osName.contains("mac") || osName.contains("darwin"))
	        return OS.MAC;
	    if (osName.contains("nux"))
	        return OS.LINUX;
	    if (osName.contains("nix"))
	        return OS.UNIX;
	    if (osName.contains("sunos"))
	        return OS.SOLARIS;
	    return OS.UNKNOWN;
	}

	public String getFamily() {
		return System.getProperty("os.name");
	}

	public String getVersion() {
		return System.getProperty("os.version");
	}

	public String getArchitecture() {
		return System.getProperty("os.arch");
	}

	public String getUserHome() {
		return System.getProperty("user.home");
	}

	public String getUserDir() {
		return System.getProperty("user.dir");
	}

	public String getTempDir() {
		return System.getProperty("java.io.tmpdir");
	}

	public String getLineSeparator() {
		return System.getProperty("line.separator");
	}

	public boolean isJvm64Bit() {
		String architecture = getArchitecture();
		return architecture.contains("64");
	}

}
