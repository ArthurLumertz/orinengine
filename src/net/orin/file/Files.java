package net.orin.file;

public class Files {

	public FileData internal(String resourceName) {
		return new FileData(FileType.Internal, resourceName);
	}
	
	public FileData external(String resourceName) {
		return new FileData(FileType.External, resourceName);
	}
	
	public FileData local(String resourceName) {
		return new FileData(FileType.Local, resourceName);
	}
	
	public FileData temp(String resourceName) {
		return new FileData(FileType.Temp, resourceName);
	}
	
}
