#pragma once

#include <math.h>
//#include "Vector3f.h"

#define DEG2RAD(a) (a * 0.0174532925)


class Camera {
public:
	Vector3f eye, center, up;

	//eye: 0.807794 0.609141 1.990690
//center: 0.584573 0.472532 1.025542
//up : 0.002803 0.990037 - 0.140780
	Camera(
		/*float eyeX = 0.8f, float eyeY = 0.6f, float eyeZ = 2,
		   float centerX = 0.58f, float centerY = 0.47f, float centerZ = 1,
		   float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f*/
		   /*eye: 1.919843 1.400891 4.437348
			   center : 1.715764 1.088095 3.509711
			   up : -0.067207 0.949820 - 0.305490*/
		float eyeX = 1.919843f, float eyeY = 1.400891, float eyeZ = 4.437348,
		float centerX = 1.715764f, float centerY = 1.088095f, float centerZ = 3.509711f,
		float upX = -0.067207f, float upY = 0.949820f, float upZ = -0.305490f
	) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);

		frontView();
	}

	void frontView() {
		eye = Vector3f(2.119780, 1.525698, 5.874172);
		center = Vector3f(2.114569, 1.348448, 4.890020);
		up = Vector3f(-0.003777, 0.984162, -0.177232);

	}

	void sideView() {
		eye = Vector3f(-1.946899, 1.478364, 2.069463);
		center = Vector3f(-0.956939, 1.337186, 2.076337);
		up = Vector3f(0.141175, 0.989984, 0.000980);
	}

	void topView() {
		eye = Vector3f(1.810928, 4.520639, 2.365530);
		center = Vector3f(1.878664, 3.522935, 2.366001);
		up = Vector3f(0.997679, 0.067735, 0.006928);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};