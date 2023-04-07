
#ifndef DEFINE_H_
#define DEFINE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <time.h>
#include "BaseObject.h"


#include<string>
#include<vector>

#define VT(T) std::vector<T>


/*#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800*/




const int H_WIDTH = (int)(0.5 * SCREEN_WIDTH);
const int H_HEIGHT = (int)(0.5 * SCREEN_HEIGHT);

/*const int RENDER_DRAW_COLOR = 0X00;

const int COLOR_KEY_RED = 125;
const int COLOR_KEY_GREEN = 125;
const int COLOR_KEY_BLUE = 125;

const int FRAMES_PER_SECOND = 35;

#define FRAME_HEIGHT 45 */


static char g_MenuFont[] = { "font\\pilotcommand.otf" };

/*typedef struct MovingStyle
{
	bool sLeft;
	bool sRight;
	bool sUp;
	bool sDown;
} MOVING_STYLE;*/


enum GameStatus
{
	GAME_START = 100,
	GAME_PLAYING,
	GAME_GUIDE,
	GAME_PAUSE,
	GAME_END,
};

enum ColorBase
{
	RED_COLOR = 0,
	WHITE_COLOR = 1,
	BLACK_COLOR = 2,
	GREEN_COLOR = 3,
	BLUE_COLOR = 4,
	ORANGE_COLOR = 5,
	GRAY_COLOR = 6,
};

#endif
