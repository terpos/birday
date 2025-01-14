#include "P_Weapon.h"



P_Weapon::P_Weapon(Image &sprite_sheet, int x, int y, int vel, int direction, int num_of_bounce)
{
	set_image(sprite_sheet);
	set_x(x);
	set_y(y);
	set_vel(vel);
	set_direction(direction);
	set_kill(false);
	set_enemy_damage(false);
	
	this->temp_vel = vel;

	cropping = al_create_bitmap(80, 80);
	cropping2 = al_create_bitmap(40, 40);

	seed = std::chrono::system_clock::now().time_since_epoch().count();
	movement.seed(seed);
	
	type = 0;
	hit = false;

}


P_Weapon::~P_Weapon()
{
	al_destroy_bitmap(cropping);
	al_destroy_bitmap(cropping2);
}

int P_Weapon::get_x()
{
	return this->x;
}

int P_Weapon::get_y()
{
	return this->y;
}

int P_Weapon::get_vel()
{
	return this->vel;
}

int P_Weapon::get_direction()
{
	return this->direction;
}

int P_Weapon::damage()
{
	return 1;
}

int P_Weapon::enemy_status()
{
	return this->status_enemy;
}

int P_Weapon::get_id()
{
	return this->id;
}

bool P_Weapon::is_dead()
{
	return this->kill;
}

bool P_Weapon::enemy_damaged()
{
	return this->damage_enemy;
}

Image P_Weapon::get_image()
{
	return this->image;
}

std::pair <bool, int> P_Weapon::is_hit()
{
	return std::make_pair(hit, hit_count);
}

void P_Weapon::set_x(int x)
{
	this->x = x;
}

void P_Weapon::set_y(int y)
{
	this->y = y;
}

void P_Weapon::set_vel(int vel)
{
	this->vel = vel;
}

void P_Weapon::set_direction(int direction)
{
	this->direction = direction;
}

void P_Weapon::set_kill(bool kill)
{
	this->kill = kill;
}

void P_Weapon::abilities()
{
	set_enemy_status(1);
	set_hit(true, is_hit().second);
	set_enemy_damage(true);
}

void P_Weapon::set_enemy_damage(bool damage)
{
	this->damage_enemy = damage;
}

void P_Weapon::set_enemy_status(int status)
{
	this->status_enemy = status;
}

void P_Weapon::set_id(int id)
{
	this->id = id;
}

void P_Weapon::set_hit(bool hit, int hit_count)
{
	this->hit = hit;
	this->hit_count = hit_count;
}

void P_Weapon::change_direction()
{
	std::uniform_int_distribution <int> d(0, 1);


	if (get_direction() == 0)
	{
		set_y(get_y() - get_vel());
		set_direction(d(movement) + 2);
	}

	else if (get_direction() == 1)
	{
		set_y(get_y() + get_vel());
		set_direction(d(movement) + 2);
	}

	else if (get_direction() == 2)
	{
		set_x(get_x() - get_vel());
		set_direction(d(movement));
	}

	else if (get_direction() == 3)
	{
		set_x(get_x() + get_vel());
		set_direction(d(movement));
	}



}



void P_Weapon::set_image(Image image)
{
	this->image = image;
}

void P_Weapon::update()
{
	if (type == 0)
	{
		if (bomb_detonate.get_frame() < 200)
		{
			bomb_detonate.increment_frame();
		}

		if (bomb_detonate.get_frame() >= 200)
		{
			weapon_explosion.increment_frame();
		}


		if (animation.get_frame() >= 100)
		{
			animation.reset_frame();
		}

		if (weapon_explosion.get_frame() >= 10)
		{
			
			if (is_hit().second == 0)
			{
				set_kill(true);
			}

			else
			{
				set_hit(false, is_hit().second - 1);
				set_vel(this->temp_vel);
				change_direction();
				weapon_explosion.reset_frame();
			}
		}

		if (is_hit().first)
		{
			set_vel(0);
			weapon_explosion.increment_frame();
		}

		animation.increment_frame();

		switch (get_direction())
		{
		case 0:
			set_y(get_y() + get_vel());
			break;
		case 1:
			set_y(get_y() - get_vel());
			break;
		case 2:
			set_x(get_x() + get_vel());
			break;
		case 3:
			set_x(get_x() - get_vel());
			break;
		}
	}

	else
	{

		set_x(get_x());
		set_y(get_y());
	}
	
}

void P_Weapon::render(Image expl, Sound sound, bool play_sound)
{
	if (is_hit().first)
	{
		if (weapon_explosion.get_frame_position(11) >= 0 && weapon_explosion.get_frame_position(11) <= 5)
		{
			al_draw_bitmap_region(expl.Destruction_image(1).first, 0, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
			
		}

		else
		{
			al_draw_bitmap_region(expl.Destruction_image(1).first, 80, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
		}
	}

	else
	{
		if (al_get_bitmap_width(get_image().Player_Weapon_image(get_id()).first) > 160)
		{
			switch (get_direction())
			{
			case 0:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 0, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			case 1:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 160, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			case 2:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 240, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			case 3:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 80, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			}
		}

		else if (al_get_bitmap_width(get_image().Player_Weapon_image(get_id()).first) == 160)
		{
			switch (get_direction())
			{
			case 0:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 0, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			case 1:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 0, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			case 2:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 80, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			case 3:
				al_draw_bitmap_region(get_image().Player_Weapon_image(get_id()).first, 80, 0, al_get_bitmap_width(cropping), al_get_bitmap_height(cropping), get_x(), get_y(), NULL);
				break;
			}
		}

	}
}

