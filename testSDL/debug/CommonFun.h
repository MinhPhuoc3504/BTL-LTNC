
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include<bits/stdc++.h>
#include<vector>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Renderer* g_menu = NULL;
static SDL_Event g_event;

//Screen khỏi tạo cho màn hình
const int FRAME_PER_SECOND = 28;//dieu chinh fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

// kích thước màn hình
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


const int RENDER_DRAW_COLOR = 0xff;


#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define GAME_TIME 300

//The music that will be played
 static Mix_Music *gMusic = NULL;

//The sound effects that will be used
static Mix_Chunk *gBullet = NULL;
static Mix_Chunk *gKill = NULL;
static Mix_Chunk *gDie = NULL;
static Mix_Chunk *gCollect = NULL;

typedef struct Input
{
  int left;
  int right;
  int up;
  int down;
  int jump;
};

typedef struct Map // cấu trúc dữ liệu Map
{   // vị trí chia 64 lấy phần nguyên ra chỉ số của ô
    int start_x_;
    int start_y_;
    // chỉ số của ô
    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFun
{
    int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
    const std::string& menu1,
    const std::string& menu2,
    const std::string& img_name);
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // COMMON_FUNCTION_H_
