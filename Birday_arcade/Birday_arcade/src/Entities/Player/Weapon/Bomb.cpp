#include "Bomb.h"



Bomb::Bomb(Image &sprite_sheet, int x, int y, int vel, int direction, int num_of_bounce): P_Weapon(sprite_sheet, x, y, vel, direction, num_of_bounce)
{
	set_id(BOMBS);
	set_x(x);
	set_y(y);
	set_vel(vel);
	set_direction(direction);

	
	bomb_detonate.set_frame(0);
	type = 1;
}


Bomb::~Bomb()
{
}

void Bomb::abilities()
{
	if (weapon_explosion.get_frame() > 0)
	{
		set_enemy_status(1);
		set_hit(true, is_hit().second);
		set_enemy_damage(true);
	}

	else
	{
		set_hit(false, is_hit().second);
		set_enemy_damage(false);
	}
}

int Bomb::damage()
{
	return 2;
}

void Bomb::render(Image expl, Sound sound, bool play_sound)
{
	if (weapon_explosion.get_frame() > 0)
	{
		if (play_sound)
		{
			al_play_sample_instance(sound.sound_effects(1));
		}
	}
	if (bomb_detonate.get_frame() < 200)
	{
		if (bomb_detonate.get_frame() <= 100)
		{
			if (bomb_detonate.get_frame_position(21) >= 0 && bomb_detonate.get_frame_position(21) <= 10)
			{
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 0, 0, al_get_bitmap_width(cropping2), al_get_bitmap_height(cropping2), get_x(), get_y(), NULL);
			}

			else
			{
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 40, 0, al_get_bitmap_width(cropping2), al_get_bitmap_height(cropping2), get_x(), get_y(), NULL);
			}
		}

		else if (bomb_detonate.get_frame() > 100)
		{
			if (bomb_detonate.get_frame_position(11) >= 0 && bomb_detonate.get_frame_position(11) <= 5)
			{
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 0, 0, al_get_bitmap_width(cropping2), al_get_bitmap_height(cropping2), get_x(), get_y(), NULL);
			}

			else
			{
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 40, 0, al_get_bitmap_width(cropping2), al_get_bitmap_height(cropping2), get_x(), get_y(), NULL);
			}
		}
	}

	else
	{
		if (weapon_explosion.get_frame_position(11) >= 0 && weapon_explosion.get_frame_position(11) <= 5)
		{
			al_draw_bitmap_region(expl.Destruction_image(2).first, 0, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);

		}

		else
		{
			al_draw_bitmap_region(expl.Destruction_image(2).first, 0, 80, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
		}
	}
}
