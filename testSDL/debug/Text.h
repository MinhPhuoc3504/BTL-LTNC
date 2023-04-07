
#ifndef TEXT_H_
#define TEXT_H_

#include"CommonFun.h"
#define FONT_SIZE 15

class TextObj
{
public:
    TextObj();
    ~TextObj();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip= SDL_FLIP_NONE);//show text

    int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}

    void SetText(const std::string& text){str_val = text;}
    std::string GetText() const {return str_val;}
private:
    std::string str_val;//ndung text
    SDL_Color text_color;
    SDL_Texture* texture_;
    int width_;
    int height_;
};

#endif // TEXT_H_
