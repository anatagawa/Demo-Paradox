#ifndef __STARFIELD_H__
#define __STARFIELD_H__ 

#pragma once

#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXSTARS 15

typedef struct Stars {
	float x;
	float y;
	float speedX;
	float speedY;
} Stars;

typedef struct Starfield2D {
	Texture2D sprite;
	Vector2 position;
	Vector2 size;
	Stars stars[MAXSTARS];
} Starfield2D;

Starfield2D Init_Starfield2D(Texture2D sprite, Vector2 position, Vector2 size);
void SetSpeed_Starfield2D(Starfield2D *starfield, Vector2 speed);
void Draw_Starfield2D(Starfield2D *starfield, Vector2 velocity);

inline static float Rand(float a) {
	return (float)rand()/(float)(RAND_MAX/a);
}

#endif
