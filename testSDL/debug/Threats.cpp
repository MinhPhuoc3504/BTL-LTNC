
#include "Threats.h"
using namespace std;

ThreatsObj::ThreatsObj()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    on_ground = 0;
    come_back_time = 0;
    frame_ = 0;

    animation_a = 0;
    animation_b = 0;
    input_type.left = 0;
    type_move = STATIC_THREAT;
}

ThreatsObj::~ThreatsObj()
{

}

bool ThreatsObj::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret)
    {
        width_frame_=rect_.w/ THREAT_FRAME_NUM;
        height_frame_=rect_.h;
    }
    return ret;
}

SDL_Rect ThreatsObj::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;

}

void ThreatsObj::set_clip()
{
    if(width_frame_>0 && height_frame_ > 0)
    {
        frame_clip_[0].x=0;
        frame_clip_[0].y=0;
        frame_clip_[0].w=width_frame_;
        frame_clip_[0].h=height_frame_;

        frame_clip_[1].x=width_frame_;
        frame_clip_[1].y=0;
        frame_clip_[1].w=width_frame_;
        frame_clip_[1].h=height_frame_;

        frame_clip_[2].x=2*width_frame_;
        frame_clip_[2].y=0;
        frame_clip_[2].w=width_frame_;
        frame_clip_[2].h=height_frame_;

        frame_clip_[3].x=3*width_frame_;
        frame_clip_[3].y=0;
        frame_clip_[3].w=width_frame_;
        frame_clip_[3].h=height_frame_;

        frame_clip_[4].x=4*width_frame_;
        frame_clip_[4].y=0;
        frame_clip_[4].w=width_frame_;
        frame_clip_[4].h=height_frame_;

        frame_clip_[5].x=5*width_frame_;
        frame_clip_[5].y=0;
        frame_clip_[5].w=width_frame_;
        frame_clip_[5].h=height_frame_;

        frame_clip_[6].x=6*width_frame_;
        frame_clip_[6].y=0;
        frame_clip_[6].w=width_frame_;
        frame_clip_[6].h=height_frame_;

        frame_clip_[7].x=7*width_frame_;
        frame_clip_[7].y=0;
        frame_clip_[7].w=width_frame_;
        frame_clip_[7].h=height_frame_;
    }
}

void ThreatsObj::Show(SDL_Renderer* des)
{
    if(come_back_time == 0)
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        frame_++;
        if(frame_>=8)
        {
            frame_=0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
    }
}

void ThreatsObj::DoPlayer(Map& gMap)
{
    if(come_back_time == 0)
    {
        x_val = 0;
        y_val += THREAT_GRAVITY_SPEED;
        if(y_val> THREAT_MAX_FALL_SPEED)
        {
            y_val = THREAT_MAX_FALL_SPEED;
        }

        if(input_type.left== 1)
        {
            x_val -= THREAT_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += THREAT_SPEED;
        }
        CheckToMap(gMap);
    }
    else if (come_back_time>0)
    {
        come_back_time--;
        if(come_back_time==0)
        {
            InitThreats();
        }
    }
}

void ThreatsObj::InitThreats()
{
    x_val = 0;
    y_val = 0;
    if(x_pos > 4*TILE_SIZE)
    {
        x_pos -= 4*TILE_SIZE;
        animation_a -= 4*TILE_SIZE;
        animation_b -= 4*TILE_SIZE;
    }
    else
    {
        x_pos = 0;
    }
        y_pos = 0;
        come_back_time = 0;
        input_type.left = 1;
}

void ThreatsObj::RemoveBullet(const int& index)
{
    int siz = bullet_list.size();
    if(siz > 0 && index <siz)
    {
        //BulletObj* p_bullet = bullet_list.at(index);
        bullet_list.erase(bullet_list.begin()+index);

        //if(p_bullet != NULL)
        {
            //delete p_bullet;
            //p_bullet = NULL;
            //money_count++;
        }
    }
}

void ThreatsObj::CheckToMap(Map& map_data)
{
    //gioi han kiem tra tu a den b theo chieu x
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0; //kiem tra theo chieu doc

    // check chieu ngang
    int height_min = height_frame_ <TILE_SIZE ? height_frame_ :TILE_SIZE;

    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame_-1)/TILE_SIZE;

    y1 = (y_pos )/TILE_SIZE;
    y2 = (y_pos +  height_min -1)/TILE_SIZE;

    if(x1 >= 0 && x2<MAX_MAP_X && y1 >=0 && y2< MAX_MAP_Y)
    {
        if(x_val > 0) //player di chuyen sang phai
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if((val1 != BLANK_TILE && val1!=VAT_PHAM)|| (val2 != BLANK_TILE && val2 != VAT_PHAM))
            {
                // va cham map
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame_ +1;
                x_val = 0;
            }
        }
        else if(x_val <0)
            {
                int val1 = map_data.tile[y1][x1];
                int val2 = map_data.tile[y2][x1];
                if((val1 != BLANK_TILE && val1 !=VAT_PHAM) || (val2 != BLANK_TILE && val2!=VAT_PHAM))
                {
                    x_pos = (x1+1)*TILE_SIZE;
                    x_val =0;

                }
            }
    }

    // check chieu doc

    int width_min = width_frame_ <TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos +y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame_ -1)/TILE_SIZE;


    if(x1>=0 && x2< MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if(y_val >0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if((val1 != BLANK_TILE && val1!=VAT_PHAM)|| (val2 != BLANK_TILE && val2 != VAT_PHAM))
            {
                y_pos = y2*TILE_SIZE;
                y_pos -=height_frame_ +1;
                y_val = 0;
                on_ground = true;
            }
        }
        else if (y_val <0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 =  map_data.tile[y1][x2];
            if((val1 != BLANK_TILE && val1!=VAT_PHAM)|| (val2 != BLANK_TILE && val2 != VAT_PHAM))
            {
                y_pos=(y1 +1)*TILE_SIZE;
                y_val=0;

            }
        }
    }
    x_pos +=x_val;
    y_pos +=y_val;

    if(x_pos <0)
    {
        x_pos = 0;
    }
    else if(x_pos +width_frame_ > map_data.max_x_)
    {
        x_pos = map_data.max_x_ - width_frame_ -1;
    }

    // xu ly roi vuc
    if(y_pos > map_data.max_y_)
    {
        come_back_time = REVIVE;
    }
}

void ThreatsObj::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move == STATIC_THREAT)
    {
        ;
    }
    else
    {
        if(on_ground==true)
        {
            if(x_pos>animation_b)
            {
                input_type.left = 1;
                input_type.right = 0;
                LoadImg("image/threats_dong/1/threats5.png", screen);

            }
            else if (x_pos < animation_a)
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("image/threats_dong/1/threats5_right.png", screen);
            }
        }
        else
        {
            if(input_type.left == 1)
            {
                LoadImg("image/threats_dong/1/threats5.png", screen);
            }
        }
    }
}

void ThreatsObj::InitBullet(BulletObj* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet != NULL)
    {
        p_bullet-> LoadImg("image/bullet/b4.png", screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_direct(BulletObj::DIR_LEFT);
        p_bullet->SetRect(rect_.x+5,rect_.y+30);//set vi tri dan ban
        p_bullet->set_x_val(THREAT_BULLET_SPEED);
        bullet_list.push_back(p_bullet);
    }
}

void ThreatsObj::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for(int i = 0;i <bullet_list.size(); i++)
    {
        BulletObj* p_bullet = bullet_list.at(i);
        if(p_bullet!=NULL)
        {

            if(p_bullet->get_is_move())
            {

                int bullet_distance = rect_.x+ width_frame_ - p_bullet->GetRect().x;//kc cua dan vs threat
                if(bullet_distance < THREAT_BULLET_MAX_DISTANCE && bullet_distance>0)
                {

                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {

                    p_bullet->set_is_move(false);
                }
            }
            else
            {

                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x+5, rect_.y+30);
            }
        }
    }
}
