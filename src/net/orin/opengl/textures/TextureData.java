package net.orin.opengl.textures;

public class TextureData {

	private int id;
	private int width;
	private int height;

	private float textureU0;
	private float textureU1;
	private float textureV0;
	private float textureV1;

	public TextureData(int id, int width, int height) {
		this.id = id;
		this.width = width;
		this.height = height;
		this.textureU0 = 0.0F;
		this.textureU1 = 1.0F;
		this.textureV0 = 0.0F;
		this.textureV1 = 1.0F;
	}

	public void setTextureU0(float textureU0) {
		this.textureU0 = textureU0;
	}

	public void setTextureU1(float textureU1) {
		this.textureU1 = textureU1;
	}

	public void setTextureV0(float textureV0) {
		this.textureV0 = textureV0;
	}

	public void setTextureV1(float textureV1) {
		this.textureV1 = textureV1;
	}

	public int getId() {
		return this.id;
	}

	public int getWidth() {
		return this.width;
	}

	public int getHeight() {
		return this.height;
	}

	public float getTextureU0() {
		return this.textureU0;
	}

	public float getTextureU1() {
		return this.textureU1;
	}

	public float getTextureV0() {
		return this.textureV0;
	}

	public float getTextureV1() {
		return this.textureV1;
	}

}
