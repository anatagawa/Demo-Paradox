#include "starfield.h"

//-----------------------------------------------------------------------------------------------------------------------------------------
// Starfield 2D
//-----------------------------------------------------------------------------------------------------------------------------------------

Starfield2D Init_Starfield2D(Texture2D sprite, Vector2 position, Vector2 size) {
	Starfield2D p;
	p.sprite = sprite;
	p.position = position;
	p.size = size;
	
	for(int i = 0; i < MAXSTARS; i++) {
		p.stars[i].x = GetRandomValue(p.position.x , p.position.x + p.size.x);
		p.stars[i].y = GetRandomValue(p.position.y , p.position.y + p.size.y);
	}

	return p;
}

void SetSpeed_Starfield2D(Starfield2D *starfield, Vector2 speed) {
	for(int i = 0; i < MAXSTARS; i++) {
		starfield->stars[i].speedX = speed.x;
		starfield->stars[i].speedY = speed.y;
	}
}

void Draw_Starfield2D(Starfield2D *starfield, Vector2 velocity) {
	for(int i = 0; i < MAXSTARS; i++) {
		starfield->stars[i].x += starfield->stars[i].speedX * velocity.x;
		starfield->stars[i].y += starfield->stars[i].speedY * velocity.y;

		if( starfield->stars[i].x > ( starfield->position.x + starfield->size.x ) ) {
			starfield->stars[i].x = starfield->position.x;
			starfield->stars[i].y = GetRandomValue(starfield->position.y , starfield->position.y + starfield->size.y);;
		}

		if( starfield->stars[i].x < starfield->position.x ) starfield->stars[i].x = starfield->position.x + starfield->size.x;
		if( starfield->stars[i].y > ( starfield->position.y + starfield->size.y ) ) starfield->stars[i].y = starfield->position.y;
		if( starfield->stars[i].y < starfield->position.y ) starfield->stars[i].y = starfield->position.y + starfield->size.y;

		DrawTexture(starfield->sprite, starfield->stars[i].x, starfield->stars[i].y, WHITE);
	}
}
