#include "GLTexture.h"
#include <string>

class Ammo {
private:
public:
	// string path
	std::string path;
	// size
	float width;
	float height;
	GLTexture texture;

	float x;
	float y;
	float z;

	float rotationVar;

	Ammo(float _x, float _y, float _z, GLTexture _texture);

	void Draw(float rotation);
};
