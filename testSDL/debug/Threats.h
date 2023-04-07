
#ifndef THREATS_H_
#define THREATS_H_

#include "CommonFun.h"
#include "BaseObject.h"
#include "Bullet.h"

#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
#define THREAT_BULLET_MAX_DISTANCE 600
#define THREAT_BULLET_SPEED 15


class ThreatsObj : public BaseObject
{
public:
    ThreatsObj();
    ~ThreatsObj();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_val(const float& xVal){x_val=xVal;}
    void set_y_val(const float& yVal){y_val=yVal;}

    void set_x_pos(const float& xp){x_pos=xp;}
    void set_y_pos(const float& yp){y_pos=yp;}

    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}

    void SetMapXY(int& mpx, int& mpy){map_x=mpx;map_y=mpy;}

    void set_clip();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    SDL_Rect GetRectFrame();
    void InitThreats();
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);

    void set_type_move(const int& typeMove){type_move = typeMove;}

    void set_animationPos(const int& pos_a, const int& pos_b){animation_a = pos_a, animation_b = pos_b;}
    // trang thai di chuyen phai hay trai
    void set_input_left(const int& ipleft){input_type.left = ipleft;};
    //Xu ly van de duy chuyen trong a b
    void ImpMoveType(SDL_Renderer* screen);

    std::vector<BulletObj*> get_bullet_list()const {return bullet_list;}
    void set_bullet_list(const std::vector<BulletObj*>& bulletList){bullet_list = bulletList;}

    void InitBullet(BulletObj* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& index);
private:

    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int map_x;
    int map_y;
    bool on_ground;
    int come_back_time;

    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;

    // di chuyen threat
    int type_move;
    int animation_a;
    int animation_b;
    Input input_type;

    std::vector<BulletObj*> bullet_list;
};

#endif // THREATS_H_
