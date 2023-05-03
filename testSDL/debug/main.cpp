#include "CommonFun.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "Timer.h"
#include "Threats.h"
#include"Text.h"
#include "Geometric.h"

#define BUG_LIFE 20



BaseObject g_background;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;

using namespace std;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window = SDL_CreateWindow("Game cua Phuoc", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1,SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if(TTF_Init()==-1)
        {
            success = false;
        }
        font_time = TTF_OpenFont("font/dlxfont_.ttf", FONT_SIZE);
        font_menu = TTF_OpenFont("font/dlxfont_.ttf", FONT_MENU);
        if(font_time==NULL)
        {
            success = false;
        }
         if(font_menu==NULL)
        {
            success = false;
        }
    }
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
     if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
      return success;
}

bool LoadBackgroung()
{
    bool ret = g_background.LoadBackGr("image/background/3.png", g_screen);
    if(ret==false)
        return false;

    return true;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load music
    gMusic = Mix_LoadMUS( "sound/Action.mid" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load sound effects
    gBullet = Mix_LoadWAV( "sound/Fire1.wav" );
    if( gBullet == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gKill = Mix_LoadWAV( "sound/Explosion+1.wav" );
    if( gKill == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gDie = Mix_LoadWAV( "sound/Bomb1.wav" );
    if( gDie == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gCollect = Mix_LoadWAV( "sound/beep_.wav" );
    if( gCollect == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;

    //Free the sound effects
    Mix_FreeChunk( gBullet );
    Mix_FreeChunk( gKill );
    Mix_FreeChunk( gDie );
    Mix_FreeChunk( gCollect );
    gBullet = NULL;
    gKill = NULL;
    gDie = NULL;
    gCollect = NULL;

    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;


    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObj*> ThreatsList()
{
    std::vector<ThreatsObj*> list_threats;

    ThreatsObj* dynamic_threats = new ThreatsObj[20];//threat di chuyen
    for(int i = 0; i< 20; i++)
    {
        ThreatsObj* p_threat = (dynamic_threats + i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("image/threats_dong/1/threats5.png", g_screen);
            p_threat->set_clip();
            p_threat->set_type_move(ThreatsObj::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*500); // dieu chinh lai
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos()-60;
            int pos2 = p_threat->get_x_pos()+60;
            p_threat->set_animationPos(pos1,pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObj* threats_objs = new ThreatsObj[20];//threat co dinh
    for(int i = 0;i < 20; i++)
    {
        ThreatsObj* p_threat = (threats_objs+i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("image/threats_tinh/threat51.png", g_screen);
            p_threat->set_clip();
            p_threat->set_x_pos(700 + i*1200); // dieu chinh lai
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObj::STATIC_THREAT);

            BulletObj* p_bullet = new BulletObj();
            p_threat->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat);
        }

    }

    return list_threats;
}


int main(int argc, char** argv)
{
    bool quit= false;
    while(!quit)
    {
    int max_score;
    ifstream read("high_score.txt");
    read >> max_score;
    int LIFE = BUG_LIFE + 1;
    ImpTimer fps_timer;
    if(InitData()==false)
        return -1;
    bool is_quit = false;
    int ret_menu = SDLCommonFun::ShowMenu(g_screen, font_menu, "Play Game", "Exit", "image/menu.jpg");
    if (ret_menu == 1)
    {
        is_quit = true;
    }
    if(LoadBackgroung()==false)
        return -1;
    if(loadMedia()==false)
        return -1;

    if( Mix_PlayingMusic() == 0 )
     {
        Mix_PlayMusic( gMusic, -1 );
     }
     else
     {
         if( Mix_PausedMusic() == 1 )
         {
            Mix_ResumeMusic();
         }
         else
         {
            Mix_PauseMusic();
         }
      }
    GameMap game_map;
    game_map.LoadMap("map/map.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("image/player/p1/player_right.png", g_screen);
    p_player.set_clips();

    std::vector<ThreatsObj*> threats_list = ThreatsList();
    //time text
    TextObj high_score;
    TextObj score_game;
    TextObj lifes_game;
    high_score.SetColor(TextObj::WHITE_TEXT);
    score_game.SetColor(TextObj::WHITE_TEXT);
    lifes_game.SetColor(TextObj::WHITE_TEXT);

    //duy trì ctrinh
    while(!is_quit && !p_player.GetEndGame())
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type==SDL_QUIT)
            {
                is_quit=true;
            }

            p_player.HandelInputAction(g_event, g_screen, gBullet);
        }
        // set lại màu cho màn hình
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        // xóa màn hình đi reset lại để làm mới
        SDL_RenderClear(g_screen);
        // fill lại vào màn hình
        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPalyer(map_data, gCollect);
        p_player.Show(g_screen);
        //cout<<p_player.GetScore()<<endl;

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        //DRAW GEOMETRIC
        GeometricFormat rectangle_size(0,0, SCREEN_WIDTH, 40);
        ColorData color_data(0,80,150);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

        GeometricFormat outLineSize(1,1,SCREEN_WIDTH-1,38);
        ColorData color_data2(255,255,255);

        Geometric::RenderOutline(outLineSize, color_data2, g_screen);

        if(p_player.get_NUM_DIE()>3)
        {
            is_quit=true;
        }

        for(int i = 0; i< threats_list.size(); i++)
        {
            ThreatsObj* p_threat = threats_list.at(i);
            if(p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_,map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                // xoa dan cua threat khi cham nvat
                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCoL1= false;

                std::vector<BulletObj*> threatBullet_list = p_threat->get_bullet_list();
                for(int jj =0;jj<threatBullet_list.size();++jj)
                {

                    BulletObj* pthreat_bullet= threatBullet_list.at(jj);
                    if(pthreat_bullet != NULL)
                    {
                        bCoL1 = SDLCommonFun::CheckCollision(pthreat_bullet->GetRect(), rect_player);
                        if(bCoL1)
                        {
                           if(LIFE>0)
                           {
                               LIFE--;
                           }

                        }

                    }
                }
                // nhan vat chet
                SDL_Rect threatRect;
                        threatRect.x = p_threat->GetRect().x;
                        threatRect.y = p_threat->GetRect().y;
                        threatRect.w = p_threat->get_width_frame();
                        threatRect.h = p_threat->get_height_frame();
                bool bCol2 = SDLCommonFun::CheckCollision(rect_player, threatRect);
                if( bCol2|| LIFE == 0 )
                {
                    Mix_PlayChannel(-1, gDie, 0);
                    if(p_player.get_NUM_DIE()<=3)
                    {
                        LIFE++;
                        p_player.SetRect(0,0);
                        p_player.set_comeback_time(60);
                        SDL_Delay(500);
                        continue;
                    }
                    else
                    {
                        p_threat->Free();
                        close();
                        SDL_Quit();
                        return 0;
                    }
                }

            }
        }

        std::vector<BulletObj*>bullet_arr = p_player.get_bullet_list();
        for(int i = 0; i< bullet_arr.size();i++)
        {
            BulletObj* p_bullet = bullet_arr.at(i);
            if(p_bullet != NULL)
            {
                for(int thr=0;thr<threats_list.size();thr++)
                {
                    ThreatsObj* obj_threat = threats_list.at(thr);
                    if(obj_threat != NULL)
                    {
                        SDL_Rect threatRect;
                        threatRect.x = obj_threat->GetRect().x;
                        threatRect.y = obj_threat->GetRect().y;
                        threatRect.w = obj_threat->get_width_frame();
                        threatRect.h = obj_threat->get_height_frame();

                        SDL_Rect bulletRect = p_bullet->GetRect();

                        bool bulletCol = SDLCommonFun::CheckCollision(bulletRect, threatRect);

                        if(bulletCol)
                        {
                            Mix_PlayChannel(-1, gKill,0);
                            p_player.RemoveBullet(i);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin()+thr);
                            p_player.SetScore(1);
                        }
                    }
                }
            }
        }

        //Show game time
        std::string str_score= "Score: ";
        std::string str_lifes = "Lifes: ";
        std::string str_high_score="High Score: ";

        std::string score_val = std::to_string(p_player.GetScore());
        std::string lifes_val = std::to_string(3-p_player.get_NUM_DIE());
        std::string max_score_val = std::to_string(max_score);

        str_score+=score_val;
        str_lifes+=lifes_val;
        str_high_score += max_score_val;

        score_game.SetText(str_score);
        score_game.LoadFromRenderText(font_time, g_screen);
        score_game.RenderText(g_screen, 100,15);

        lifes_game.SetText(str_lifes);
        lifes_game.LoadFromRenderText(font_time, g_screen);
        lifes_game.RenderText(g_screen, SCREEN_WIDTH/2-50,15);

        high_score.SetText(str_high_score);
        high_score.LoadFromRenderText(font_time, g_screen);
        high_score.RenderText(g_screen, SCREEN_WIDTH-300,15);

        SDL_RenderPresent(g_screen);//ham xu ly

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;//ms
        if(real_imp_time < time_one_frame)
        {
            // time thuc te be hon ly thuyet thi tao do tre de can bang
            int delay_time = time_one_frame -real_imp_time;
            if(delay_time >= 0)
                SDL_Delay(delay_time); //fps cang nho thi delay cang lon => tang fps

        }

    }
    for(int i = 0; i< threats_list.size();i++)
    {
        ThreatsObj* p_threat = threats_list.at(i);
        if(p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();

    int end_score = p_player.GetScore();
    string last_score = "Score: "+ to_string(p_player.GetScore());

    if(p_player.GetEndGame())
    {
        if(end_score > max_score)
        {
            max_score = end_score;
            ofstream write("high_score.txt");
            write << max_score;
        }
        int ret_highscore = SDLCommonFun::ShowMenu(g_screen, font_menu, last_score, "Exit", "image/victory.jpg");
        if (ret_highscore == 1)
        {
            close();
        }
    }
    else
    {

        int ret_over = SDLCommonFun::ShowMenu(g_screen, font_menu, "Play Again", "Exit", "image/gameover.jpg");
        if (ret_over== 1)
        {
            close();
            quit=true;
        }
        if(ret_over==0){ close(); continue;}
    }
    }
    close();
    return 0;
}

