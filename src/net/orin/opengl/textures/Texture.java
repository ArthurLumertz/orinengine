package net.orin.opengl.textures;

import static org.lwjgl.opengl.GL11.*;

import net.orin.Orin;
import net.orin.file.FileData;

public class Texture {
	
	private TextureData textureData;
	private FileData fileData;
	
	public Texture(FileData fileData) {
		this.fileData = fileData;
		this.textureData = Textures.loadTexture(fileData);
	}
	
	public Texture(FileData fileData, int x, int y, int width, int height) {
		this.fileData = fileData;
		this.textureData = Textures.loadTexture(fileData, x, y, width, height);
	}
	
	public Texture(Texture texture, int x, int y, int width, int height) {
		this.fileData = texture.getFileData();
		this.textureData = Textures.loadTexture(this.fileData, x, y, width, height);
	}
	
	public void bind() {
		glBindTexture(GL_TEXTURE_2D, this.textureData.getId());
	}
	
	public void unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	public void dispose() {
		Orin.log.debug("texture", "Disposing texture: " + this.fileData.getResourceName());
		glDeleteTextures(this.textureData.getId());
	}
	
	public FileData getFileData() {
		return this.fileData;
	}
	
	public TextureData getTextureData() {
		return this.textureData;
	}
	
	public int getWidth() {
		return this.textureData.getWidth();
	}
	
	public int getHeight() {
		return this.textureData.getHeight();
	}

}
