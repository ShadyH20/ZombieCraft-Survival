#include "GLTexture.h"
#include <string>

class Cuboid {
private:
	// string path
	std::string path;
	// size
	float width;
	float height;
	float depth;
	GLTexture textureFront;
	GLTexture textureBack;
	GLTexture textureLeft;
	GLTexture textureRight;
	GLTexture textureTop;
	GLTexture textureBottom;
public:
	Cuboid(float w, float h, float d, std::string p);
	Cuboid(float w, float h, float d);
	~Cuboid();

	void Draw();
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	float GetDepth() { return depth; }
};
