#include "E_Weapon.h"

#pragma once
class Thunder: public E_Weapon
{
public:
	Thunder(Image &sprite_sheet, int x, int y, int vel, int direction);
	~Thunder();
	
	int damage();

private:
	int x, y, vel, direction, buttons[7], type;

	bool draw;

	ALLEGRO_BITMAP *cropping;

};

