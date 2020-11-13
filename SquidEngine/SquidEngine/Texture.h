#pragma once

#include "SquidEngine.h"

#define TEXTURE_UNITS 32

#define NO_TEXTURE_PATH "";

extern int defaultTextureID;

class Texture {
protected:
	unsigned int textureID = 0;
	std::string imagePath;
	void createBlankTexture(float red, float green, float blue, int imgWidth, int imgHeight);
public:
	Texture();
	Texture(float red, float green, float blue, int imgWidth, int imgHeight);
	Texture(const char* textureFile);
	bool openFile(const char* fileName);

	unsigned int getID();
	std::string getImagePath();

	void setScaleUpFilter(int filter);
	void setScaleDownFilter(int filter);
	void setWrappingX(int wrapper);
	void setWrappingY(int wrapper);
	void setBorderColour(glm::vec4 borderColour);

	void setWrapping(int wrapX, int wrapY);
	void setFiltering(int scaleUp, int scaleDown);

	void initTexture();
};

