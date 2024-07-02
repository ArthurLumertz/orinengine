package net.orin.opengl.textures;

import static org.lwjgl.opengl.GL11.*;

import java.awt.image.*;
import java.io.*;
import java.nio.*;
import java.util.*;

import javax.imageio.*;

import org.lwjgl.*;

import net.orin.*;
import net.orin.file.*;

public class Textures {

	private static HashMap<String, TextureData> idMap = new HashMap<String, TextureData>();
	
	public static TextureData loadTexture(FileData fileData, int x, int y, int width, int height) {
		try {
			if (idMap.containsKey(fileData.getResourceName()))
				return idMap.get(fileData.getResourceName());

			int id = glGenTextures();
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			BufferedImage parentImage = ImageIO.read(Orin.class.getResourceAsStream(fileData.getPath()));
			
			BufferedImage image = parentImage.getSubimage(x, y, width, height);
			int w = image.getWidth();
			int h = image.getHeight();
			int[] rawPixels = new int[w * h];
			image.getRGB(0, 0, w, h, rawPixels, 0, w);

			for (int i = 0; i < rawPixels.length; i++) {
				int alpha = rawPixels[i] >> 24 & 0xFF;
				int red = rawPixels[i] >> 16 & 0xFF;
				int green = rawPixels[i] >> 8 & 0xFF;
				int blue = rawPixels[i] & 0xFF;
				rawPixels[i] = alpha << 24 | blue << 16 | green << 8 | red;
			}

			ByteBuffer byteBuffer = BufferUtils.createByteBuffer(w * h * 4);
			byteBuffer.asIntBuffer().put(rawPixels);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, byteBuffer);

			Orin.log.debug("textures", "Loaded texture: " + fileData.getResourceName());

			TextureData data = new TextureData(id, w, h);
			idMap.put(fileData.getResourceName(), data);
			
			return data;
		} catch (IOException e) {
			Orin.log.fatal("textures", "Failed to load texture: " + fileData.getResourceName());
			return null;
		}
	}

	public static TextureData loadTexture(FileData fileData) {
		try {
			if (idMap.containsKey(fileData.getResourceName()))
				return idMap.get(fileData.getResourceName());

			int id = glGenTextures();
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			BufferedImage image = ImageIO.read(Orin.class.getResourceAsStream(fileData.getPath()));
			int width = image.getWidth();
			int height = image.getHeight();
			int[] rawPixels = new int[width * height];
			image.getRGB(0, 0, width, height, rawPixels, 0, width);

			for (int i = 0; i < rawPixels.length; i++) {
				int alpha = rawPixels[i] >> 24 & 0xFF;
				int red = rawPixels[i] >> 16 & 0xFF;
				int green = rawPixels[i] >> 8 & 0xFF;
				int blue = rawPixels[i] & 0xFF;
				rawPixels[i] = alpha << 24 | blue << 16 | green << 8 | red;
			}

			ByteBuffer byteBuffer = BufferUtils.createByteBuffer(width * height * 4);
			byteBuffer.asIntBuffer().put(rawPixels);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, byteBuffer);

			Orin.log.debug("textures", "Loaded texture: " + fileData.getResourceName());

			TextureData data = new TextureData(id, width, height);
			idMap.put(fileData.getResourceName(), data);
			
			return data;
		} catch (IOException e) {
			Orin.log.fatal("textures", "Failed to load texture: " + fileData.getResourceName());
			return null;
		}
	}

	public static void dispose() {
		for (Map.Entry<String, TextureData> entry : idMap.entrySet()) {
			TextureData textureData = entry.getValue();
			if (textureData != null) {
				Orin.log.debug("textures", "Disposing texture: " + textureData.getId());
				glDeleteTextures(textureData.getId());
			}
		}
		idMap.clear();
	}

}
