#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH    900
#define WINDOW_HEIGHT   300
#define START_RADIUS    20
#define START_COLOR     0x00FFFF

#define TARGET_FPS      60
#define COLOR_RECT_SIZE 30

Uint32 color = START_COLOR;
Uint32 color_pallete[] = {	0x000000, 0xFFFFFF, 0xFF0000, 0x00FF00,
							0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF	};
const int color_pallete_size = 8;

bool inside_color_palette(int x, int y)
{
	if (x <= color_pallete_size*COLOR_RECT_SIZE && y <= COLOR_RECT_SIZE) {
		return true;
	} else {
		return false;
	}
}

// Check if user clicked color palette and updates color if so
static void check_color_palette_chosen(int x, int y)
{
	int i;
	if (inside_color_palette(x, y)) {
		// mouse is inside x, y range of color palette
		i = x / COLOR_RECT_SIZE;
		color = color_pallete[i];
	}


	return;
}

// Draws the color palette consiting of size elements of colors
static void draw_palette(SDL_Surface *surface, Uint32 *colors, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		SDL_Rect color_rect = { i*COLOR_RECT_SIZE, 0, COLOR_RECT_SIZE, COLOR_RECT_SIZE };
		if (SDL_FillRect(surface, &color_rect, colors[i]) != 0) {
			SDL_Log("Unable to fill rect: %s", SDL_GetError());
			return ;
		}
	}
}

// Draws a circle at center coordinates with given radius and color
static void draw_circle(SDL_Surface *surface, int x_center, int y_center, int radius, Uint32 color)
{
	SDL_Rect pixel = { 0, 0, 1, 1 };
	int x, y;
	for(x = x_center - radius; x < x_center + radius; x++)
	{
		for (y = y_center - radius; y < y_center + radius; y++)
		{
			// Is this pixel part of the circle
			int distance_from_center = sqrt(
				pow(x - x_center, 2) + pow(y - y_center, 2));
			if (distance_from_center < radius) {
				// Part of the circle
				pixel.x = x;
				pixel.y = y;
				SDL_FillRect(surface, &pixel, color);
			}
		}
	}
}

int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
		"Ultra Pain",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0
 	);

	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface *surface = SDL_GetWindowSurface(window);

	int x, y;
	int radius = START_RADIUS;
	bool draw = false;
	bool running = true;
	float delay_milis = (1.0 / TARGET_FPS) * 1000;
	Uint32 color = START_COLOR;

	draw_palette(surface, color_pallete, 8);
	SDL_UpdateWindowSurface(window);
	while (running)
	{

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.motion.x;
				y = event.motion.y;
				check_color_palette_chosen(x, y);
				if(inside_color_palette(x, y) == false) {
					printf("Drawing now\n");
					draw = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				printf("Stopped drawing\n");
				draw = false;
				break;

			}

		}
		if (draw) {
			draw_circle(surface, x, y, radius, color);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(delay_milis);
		}
		draw_palette(surface, color_pallete, color_pallete_size);
	}
	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}    Ultra Pain - Paint but it hurts
    Copyright (C) 2026  Quadsam

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
