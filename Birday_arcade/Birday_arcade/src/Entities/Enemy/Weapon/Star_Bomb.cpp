#include "Star_Bomb.h"



Star_Bomb::Star_Bomb(Image &sprite_sheet, int x, int y, int vel, int direction): E_Weapon(sprite_sheet, x, y, vel, direction)
{
	set_id(STAR_SHOT);
	set_x(x);
	set_y(y);
	set_vel(vel);
	set_direction(direction);

	cropping = al_create_bitmap(80, 80);
}


Star_Bomb::~Star_Bomb()
{
}

int Star_Bomb::damage()
{
	return 30;
}
