#include "Menu.h"



Menu::Menu()
{
	options = GAME_SCREEN;
	rect_out = false;


	choice.set_alpha(0);
	bg.set_alpha(0);
	title.set_alpha(0);
	intro.set_alpha(0);
	intro.enable_fade_out(false);
	intro.enable_fade_in(true);

	Sel = al_map_rgba(255, 0, 0, choice.get_alpha());
	notSel = al_map_rgba(0, 255, 0, choice.get_alpha());
}


Menu::~Menu()
{
}

void Menu::update(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE* q, Image image, Sound sound, Options &option, ALLEGRO_EVENT &e, int &screennum, bool &done)
{
	//waits until key is pressed (can be neglected since timer is on)
	al_wait_for_event(q, &e);

	if (e.type == ALLEGRO_EVENT_KEY_DOWN && choice.get_alpha() == 255)
	{
		//goes to the quit screen when escape key is pressed
		if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			option.set_last_screen(MENU_SCREEN);
			screennum = QUIT_SCREEN;
		}

		//direction of choice go up if up arrow is pressed
		if (e.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			al_set_sample_instance_position(sound.sound_effects(17), 0);
			al_play_sample_instance(sound.sound_effects(17));
			options--;
			if (options < 1)
			{
				options = 4;
			}
		}

		//direction of choice go down if down arrow is pressed
		if (e.keyboard.keycode == ALLEGRO_KEY_DOWN)
		{
			al_set_sample_instance_position(sound.sound_effects(17), 0);
			al_play_sample_instance(sound.sound_effects(17));
			options++;
			if (options > 4)
			{
				options = 1;
			}
		}

		//selection occurs when enter key is pressed
		if (e.keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			if (options == OPTION_SCREEN)
			{
				option.set_last_screen_to_option(MENU_SCREEN);
				option.set_last_screen(MENU_SCREEN);
				screennum = options;
			}

			else
			{
				option.set_last_screen(MENU_SCREEN);
				screennum = options;
			}
			
			al_stop_sample_instance(sound.bg_music(6));
		}


	}

	//updates info
	if (e.type == ALLEGRO_EVENT_TIMER)
	{
		if (rect_out)
		{
			Sel = al_map_rgba(255, 0, 0, choice.get_alpha());
			notSel = al_map_rgba(0, 255, 0, choice.get_alpha());

			choice.fade_in(5);
			bg.fade_in(5);
			title.fade_in(5);
		}

		else
		{
			intro.fade_in(1.50);
			intro.fade_out(1.50);
			intro.fade_transition();

			if (intro.get_num_of_fades() == 1 && intro.get_alpha() <= 0)
			{
				rect_out = true;
			}
		}
	
	}
}

void Menu::render(Image image, Sound sound, Font font)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	//after terpos intro
	if (rect_out)
	{
		//plays birday's main theme
		al_play_sample_instance(sound.bg_music(6));
		
		//displays the title and background
		al_draw_tinted_bitmap(image.Background_image(MENU).first, al_map_rgba(255, 255, 255, bg.get_alpha()), 0, 0, NULL);
		al_draw_tinted_bitmap(image.Background_image(BANNER).first, al_map_rgba(255, 255, 255, title.get_alpha()), 0, 0, NULL);

		//renders all texts to the screen
		al_draw_text(font.get_font(0), notSel, 500, 330, NULL, "PLAY");
		al_draw_text(font.get_font(0), notSel, 500, 360, NULL, "MATERIALS IN THE GAME");
		al_draw_text(font.get_font(0), notSel, 500, 390, NULL, "OPTION");
		al_draw_text(font.get_font(0), notSel, 500, 420, NULL, "QUIT");

		//renders the text based on selection
		switch (options)
		{
		case GAME_SCREEN:
			al_draw_text(font.get_font(0), Sel, 500, 330, NULL, "PLAY");
			break;
		case GAME_MATERIAL_SCREEN:
			al_draw_text(font.get_font(0), Sel, 500, 360, NULL, "MATERIALS IN THE GAME");
			break;
		case OPTION_SCREEN:
			al_draw_text(font.get_font(0), Sel, 500, 390, NULL, "OPTION");
			break;
		case QUIT_SCREEN:
			al_draw_text(font.get_font(0), Sel, 500, 420, NULL, "QUIT");
			break;
		}
	}

	//during terpos intro
	else
	{
		al_draw_tinted_bitmap(image.Background_image(9).first, al_map_rgba(255, 255, 255, intro.get_alpha()), -25, 0, NULL);
	}
}

void Menu::error_notify(Font font, int x)
{
	if (x == 101)
	{
		al_draw_text(font.get_font(0), al_map_rgb(0, 200, 100), 500, 720, NULL, "Player Image not found!");
	}
}