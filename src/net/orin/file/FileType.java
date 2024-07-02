package net.orin.file;

public enum FileType {

	Internal("internal"), External("external"), Local("local"), Temp("temp");

	private String path;

	FileType(String path) {
		switch (path) {
		case "internal":
			path = "/";
			break;
		case "external":
			path = System.getProperty("user.home") + "/";
			break;
		case "local":
			path = System.getProperty("user.dir") + "/";
			break;
		case "temp":
			path = System.getProperty("java.io.tmpdir") + "/";
			break;
		default:
			path = "/";
			break;
		}
		this.path = path;
	}

	public String getPath() {
		return this.path;
	}

	public boolean equals(FileType other) {
		if (other != null) {
			if (other.hashCode() == hashCode())
				return true;
		}
		return false;
	}
	
}
