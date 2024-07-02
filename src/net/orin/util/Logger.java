package net.orin.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Logger {

	private final HashMap<String, String> logs = new HashMap<String, String>();
	
	private boolean showDebug = true;
	private boolean showWarn = true;
	
	public void hideDebug() {
		this.showDebug = false;
	}
	
	public void hideWarn() {
		this.showWarn = false;
	}
	
	public void info(String tag, String message) {
		this.logs.put(tag, "[INFO]: " + message);
		System.out.println("[INFO]: " + message);
	}
	
	public void debug(String tag, String message) {
		this.logs.put(tag, "[DEBUG]: " + message);
		if (this.showDebug)
			System.out.println("[DEBUG]: " + message);
	}
	
	public void warn(String tag, String message) {
		this.logs.put(tag, "[WARN]: " + message);
		if (this.showWarn)
			System.out.println("[WARN]: " + message);
	}
	
	public void error(String tag, String message) {
		this.logs.put(tag, "[ERROR]: " + message);
		System.err.println("[ERROR]: " + message);
	}
	
	public void fatal(String tag, String message) {
		this.logs.put(tag, "[FATAL]: " + message);
		System.err.println("[FATAL]: " + message);
	}
	
	public String get(String tag) {
		return this.logs.get(tag);
	}
	
	public List<String> getLog() {
		List<String> log = new ArrayList<String>();
		for (Map.Entry<String, String> entry : this.logs.entrySet()) {
			log.add(entry.getKey() + ", " + entry.getValue());
		}
		return log;
	}
	
}
