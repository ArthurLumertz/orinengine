package net.orin.file;

public class FileData {

	private String resourceName;
	private FileType type;

	public FileData(FileType type, String resourceName) {
		this.type = type;
		this.resourceName = resourceName;
	}
	
	public String getPath() {
		return this.type.getPath() + this.resourceName;
	}

	public String getResourceName() {
		return this.resourceName;
	}

	public FileType getType() {
		return this.type;
	}

}
