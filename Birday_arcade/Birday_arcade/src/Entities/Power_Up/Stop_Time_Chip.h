#include "Power_Up.h"

#pragma once
class Stop_Time_Chip: public Power_Up
{
public:
	Stop_Time_Chip(Image image, int x, int y);
	~Stop_Time_Chip();

	void power_up_abilities(Sound sound, Player* &player, std::vector<Enemy*>& enemy, std::vector <B_2_Bomber*> &b2, std::vector <needle_wind*> &nw, Options option);

private:
	int x, y;

};

