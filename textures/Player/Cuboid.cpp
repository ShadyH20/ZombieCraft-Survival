#include "Cuboid.h"

Cuboid::Cuboid(float w, float h, float d, std::string p) : width(w), height(h), depth(d), path(p) 
{
    textureFront.Load(const_cast<char*>((path + "front_texture.bmp").c_str()));
    textureBack.Load(const_cast<char*>((path + "back_texture.bmp").c_str()));
    textureLeft.Load(const_cast<char*>((path + "left_texture.bmp").c_str()));
    textureRight.Load(const_cast<char*>((path + "right_texture.bmp").c_str()));
    textureTop.Load(const_cast<char*>((path + "top_texture.bmp").c_str()));
    textureBottom.Load(const_cast<char*>((path + "bottom_texture.bmp").c_str()));
}

// Constructor for a cuboid without path
Cuboid::Cuboid(float w, float h, float d) : width(w), height(h), depth(d) {}

Cuboid::~Cuboid() {
    // You may want to add cleanup code here if needed
}

void Cuboid::Draw() {
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotated(180, 0, 1, 0);

    // Front face
    textureFront.Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, depth / 2);
    glEnd();

    // Back face
    textureBack.Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, -depth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, -depth / 2);
    glEnd();

    // Left face
    textureLeft.Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, -depth / 2);
    glEnd();

    // Right face
    textureRight.Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width / 2, height / 2, -depth / 2);
    glEnd();

    // Top face
    textureTop.Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, height / 2, -depth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, height / 2, -depth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, height / 2, depth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height / 2, depth / 2);
    glEnd();

    // Bottom face
    textureBottom.Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, -height / 2, -depth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, -height / 2, depth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, -height / 2, depth / 2);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
