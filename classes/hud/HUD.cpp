//#include <glew.h>
#include "HUD.h"
#include <glut.h>

//#define GLT_IMPLEMENTATION
//#include "gltext.h"
//#include "utilities.hpp"

// init inventory <int, Weapon*>
std::unordered_map<int, Weapon*> HUD::inventory = std::unordered_map<int, Weapon*>();


void drawSquareTexture(GLTexture texture, int x, int y, int w, int h);
void printText(int x, int y, char* string);

HUD::HUD(int _screenW, int _screenH, Player* _player, Goal* _goal, Wave* _wave) {
	player = _player;
	screenW = _screenW;
	screenH = _screenH;
	goal = _goal;
	wave = _wave;

	// if inventory is empty, initialize it
	if (inventory.empty()) {
		inventory = std::unordered_map<int, Weapon*>();
	}

	// Load textures
	heart.Load("Textures/heart.png");
	heartHalf.Load("Textures/heart_half.png");
	heartEmpty.Load("Textures/heart_empty.png");

	//print player hp and max hp
	printf("Player hp: %d\n", player->hp);
	printf("Player max hp: %d\n", player->maxHp);

	//GLenum err = glewInit();

	//if (!gltInit())
	//{
	//	printf("Failed to initialize glText\n");
	//}
}

HUD::~HUD() {
	// delete all the inventory venctor
	for (auto it = inventory.begin(); it != inventory.end(); ++it) {
		delete it->second;
	}
}

void HUD::goalHP() {
	// Draw hp bar at top of screen with dark grey background and red foreground
	// Draw background
	//glDisable(GL_BLEND);
	glPushMatrix();
		glColor4f(0.2, 0.2, 0.2, 1);
		// it should be 20 pixels tall and 1/2 the screen width, and centered
		int barHeight = 20;
		int yFromTop = 60;
		glBegin(GL_QUADS);
			glVertex2f(screenW / 2 - screenW / 4, screenH - yFromTop);
			glVertex2f(screenW / 2 + screenW / 4, screenH - yFromTop);
			glVertex2f(screenW / 2 + screenW / 4, screenH - yFromTop + barHeight);
			glVertex2f(screenW / 2 - screenW / 4, screenH - yFromTop + barHeight);
			glEnd();
			glPopMatrix();

		// Draw foreground
		glColor4f(1, 0, 0, 1);
		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex2f(screenW / 2 - screenW / 4, screenH - yFromTop);
				glVertex2f(screenW / static_cast<GLfloat>(2) - screenW / static_cast<GLfloat>(4) + (screenW / static_cast<GLfloat>(2)) * (static_cast<GLfloat>(goal->hp) / goal->maxHp), screenH - yFromTop);
				glVertex2f(screenW / static_cast<GLfloat>(2) - screenW / static_cast<GLfloat>(4) + (screenW / static_cast<GLfloat>(2)) * (static_cast<GLfloat>(goal->hp) / goal->maxHp), screenH - yFromTop + barHeight);
				glVertex2f(screenW / 2 - screenW / 4, screenH - yFromTop + barHeight);
			glEnd();
		glPopMatrix();
	
	glPopMatrix();

	// Write Wave # above the bar in the center
	char* p0s[20];
	sprintf((char*)p0s, "Wave %i", wave->waveNumber);

	// black
	glColor3f(0, 0, 0);

	printText(screenW / 2 - 50, screenH - 30, (char*)p0s);

	// Creating text
	//GLTtext* text = gltCreateText();
	//gltSetText(text, (char*)p0s);

	//// Begin text drawing (this for instance calls glUseProgram)
	//gltBeginDraw();

	//// Draw any amount of text between begin and end
	//gltColor(0,0,0,1.0f);
	//gltDrawText2D(text, screenW / 2 - 50, screenH - 30, 1);

	//// Finish drawing text
	//gltEndDraw();

	// Reset color
	glColor3f(1, 1, 1);


}

void HUD::draw() {
	// Draw hearts in bottom center
	// there are 10 hearts
	// the player has hp and maxHp
	// each heart represents maxHp/10

	// Draw hearts
	float heartSize = 32;
	float heartSpacing = -3.2;
	int heartX = screenW / 2 - (heartSize * 10 + heartSpacing * 9) / 2;
	int heartY = heartSize + 20;


	// Draw ammo above hearts (36 / 98)
	// Draw ammo
	char* p0s[20];
	sprintf((char*)p0s, "%i / %i", 36, 98);

	//// white
	glColor3f(1, 1, 1);
	printText(screenW / 2 - heartSize, heartY + heartSize + 10, (char*)p0s);

	// Creating text
	//GLTtext* text = gltCreateText();
	//gltSetText(text, (char*)p0s);

	//// Begin text drawing (this for instance calls glUseProgram)
	//gltBeginDraw();

	//// Draw any amount of text between begin and end
	//gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	//gltDrawText2D(text, screenW / 2 - heartSize, heartY + heartSize + 10, 1);

	//// Finish drawing text
	//gltEndDraw();


	// Goal HP bar
	goalHP();

	// Draw hearts
	//they will be a 2d square with a gltexture2d

	//Draw hearts
	glEnable(GL_TEXTURE_2D);/*
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);*/

	int heartHp = player->maxHp / 10;

	// Draw hearts
	for (int i = 0; i < 10; i++) {
		int highestHp = heartHp * (i + 1);
		int lowestHp = highestHp - heartHp;

		if (player->hp >= highestHp) {
			// Draw full heart
			drawSquareTexture(heart, heartX + (heartSize + heartSpacing) * i, heartY, heartSize, heartSize);
		}
		else if (player->hp <= lowestHp) {
			// Draw empty heart
			drawSquareTexture(heartEmpty, heartX + (heartSize + heartSpacing) * i, heartY, heartSize, heartSize);
		}
		else {
			// Draw half heart
			drawSquareTexture(heartHalf, heartX + (heartSize + heartSpacing) * i, heartY, heartSize, heartSize);
		}
	}

	//glDisable(GL_TEXTURE_2D);
}

void drawSquareTexture(GLTexture texture, int x, int y, int w, int h) {
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture.texture[0]);	// Bind the ground texture
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + w, y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + w, y + h);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + h);
	glEnd();
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);
}

void printText(int x, int y, char* string)
{
	//printf("printing text\n");
	int len, i;

	// Save the current model-view matrix
	glPushMatrix();

	// Set the position of the scaled text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	// get the length of the string to display
	len = (int)strlen(string);

	// loop to display character by character
	for (i = 0; i < len; i++)
	{
		// choose a font from those available in windows fonts
		glutBitmapCharacter(
			GLUT_BITMAP_TIMES_ROMAN_24
			, string[i]);
	}

	// Restore the model-view matrix
	glPopMatrix();
}