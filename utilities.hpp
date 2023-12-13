#include <string.h>




// Color using RGB
void colorRGB(float red, float green, float blue) {
	glColor3f(red / 255, green / 255, blue / 255);
}

void colorRGBA(float red, float green, float blue, float alpha) {
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glColor4f(red / 255, green / 255, blue / 255, alpha);
}
void bgColorRGB(float red, float green, float blue, float opacity) {
	glClearColor(red / 255, green / 255, blue / 255, opacity);
}


void TEAL_COLOR() {
	colorRGB(72, 134, 104);
}

void SKIN_COLOR() {
	colorRGB(231, 171, 122);
}

//rgb(162, 178, 124)
void LIGHT_GREEN_COLOR() {
	colorRGB(162, 178, 124);
}

//rgb(65, 90, 105)
void BLUE_GREY_COLOR() {
	colorRGB(65, 90, 105);
}

//rgb(244, 233, 0)
void YELLOW_COLOR() {
	colorRGB(244, 233, 0);
}

//rgb(114, 86, 0)
void BROWN_COLOR() {
	colorRGB(114, 86, 0);
}

//rgb(237, 60, 187)
void PINK_COLOR() {
	colorRGB(237, 60, 187);
}

//rgb(22, 22, 22)
void BLACK_COLOR() {
	colorRGB(22, 22, 22);
}

//rgb(147, 77, 44)
void WOOD_COLOR() {
	colorRGB(147, 77, 44);
}

//rgb(171, 201, 229)
void LIGHT_BLUE_COLOR() {
	colorRGB(171, 201, 229);
}

//rgb(243, 87, 0)
void ORANGE_COLOR() {
	colorRGB(243, 87, 0);
}

void GOLD_COLOR() {
	colorRGB(255, 215, 0);
}

// grey
void GREY_COLOR() {
	colorRGB(128, 128, 128);
}

//green
void GREEN_COLOR() {
	colorRGB(0, 255, 0);
}

//rgb(59, 148, 65)
void DARK_GREEN_COLOR() {
	colorRGB(59, 148, 65);
}

//rgb(135, 167, 0)
void DARKER_GREEN_COLOR() {
	colorRGB(135, 167, 0);
}

void glutSolidCylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks) {
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
	gluDeleteQuadric(quadric);
}

void drawCylinder(float radiusBase, float radiusTop, float height, bool drawBase, bool drawTop) {
	glPushMatrix();
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); // Use GLU_FILL for filled geometry

	// Draw the main cylinder
	gluCylinder(qobj, radiusBase, radiusTop, height, 100, 100);

	// Draw circular planes at the top and bottom
	if (drawBase) {
		gluDisk(qobj, 0, radiusBase, 100, 1);
	}

	glTranslatef(0, 0, height);

	if (drawTop) {
		gluDisk(qobj, 0, radiusTop, 100, 1);
	}
	glPopMatrix();
}

void print(int x, int y, char* string, float scale)
{
	int len, i;

	// Save the current model-view matrix
	glPushMatrix();

		// Scale the text using the provided scale factor
		glScalef(scale, scale, 1.0);

		// Set the position of the scaled text in the window using the x and y coordinates
		glRasterPos2f(x / scale, y / scale);

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

void printStroke(int x, int y, char* string, float scale, float lineWidth)
{
	int len, i;

	// Save the current model-view matrix
	glPushMatrix();

	// Scale the text using the provided scale factor
	glScalef(scale, scale, 1.0);

	// Set the position of the scaled text in the window using the x and y coordinates
	glTranslatef(x / scale, y / scale, 0);

	// get the length of the string to display
	len = (int)strlen(string);

	glLineWidth(lineWidth);

	// loop to display character by character
	for (i = 0; i < len; i++)
	{
		// choose a font from those available in windows fonts
		/*glutBitmapCharacter(
			GLUT_BITMAP_TIMES_ROMAN_24
			, string[i]);*/
		//glutStrokeWidth(GLUT_STROKE_ROMAN, string[i]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
	}

	// Restore the model-view matrix
	glPopMatrix();
}

void print3D(float x, float y, float z, char* string, float rot)
{
	int len, i;

	// Save the current model-view matrix
	glPushMatrix();

	// Rotate
	glRotatef(rot, 0, 1, 0);


	// Set the position of the scaled text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);

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



void drawTime(float scrW, float scrH, int timeLeft)
{
	int x = 60;
	int y = scrH - 60;
	// TIME
	GOLD_COLOR();
	print(x, y, "TIME", 1);

	char* p0s[20];
	sprintf((char*)p0s, "%i", timeLeft);

	glColor3f(1, 1, 1);
	// print(830, 550, cstr);
	print(x + 80, y, (char*)p0s, 1);


}

void enable2D() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 1600, 0, 900);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
}

void enable3D() {
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

// Ease-in and ease-out functions
float easeInOutQuad(float t) {
	return t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
}

void loadBMP(GLuint* textureID, char* strFileName, int wrap) {
	AUX_RGBImageRec* pBitmap = NULL;
	FILE* pFile = NULL;

	fopen_s(&pFile, strFileName, "r");
	if (pFile) {
		pBitmap = auxDIBImageLoadA(strFileName);
	}
	else {
		MessageBoxA(NULL, "Texture file not found!", "Error!", MB_OK);
		exit(EXIT_FAILURE);
	}

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);

	if (pBitmap) {
		if (pBitmap->data) {
			free(pBitmap->data);
		}
		free(pBitmap);
	}
}




