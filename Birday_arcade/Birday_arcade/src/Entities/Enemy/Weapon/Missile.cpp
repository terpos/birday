#include "Missile.h"



Missile::Missile(Image &sprite_sheet, int x, int y, int vel, int direction) : E_Weapon(sprite_sheet, x, y, vel, direction)
{
	set_id(MISSILE);
	set_x(x);
	set_y(y);
	set_vel(vel);
	set_direction(direction);

	cropping = al_create_bitmap(80, 80);
}


Missile::~Missile()
{
}

int Missile::damage()
{
	return 35;
}
