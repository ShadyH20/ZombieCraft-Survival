#include "Ammo.h"
#define TO_RADIANS 3.14/180.0

Ammo::Ammo(float _x, float _y, float _z, GLTexture _texture) :
	x(_x), y(_y), z(_z), texture(_texture) {

}

void Ammo::Draw(float rotation) {
	// draw heart
	glPushMatrix();
	glTranslatef(x,
		0.4 + 0.06 * sin(rotation * TO_RADIANS),
		z);
	// Rotate y using textOpacity var
	glRotatef(rotation * 0.5, 0, 1, 0);

	// draw a rectangle with the texture
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture.texture[0]);
		glBegin(GL_QUADS);
		float width = 0.15;
		float height = width / 1.227;
		// front face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, -height, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(width, -height, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, 0.0f);
		glEnd();
	//glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

