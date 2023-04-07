#include "MenuGame.h"

MenuGame::MenuGame(bool is_bkgn /*= true*/)
{
	m_Type = 0;
	m_isDrawBkgn = is_bkgn;
    m_Select = -1;
}

MenuGame::~MenuGame()
{

}

void MenuGame::LoadBkgn(const char* file, SDL_Renderer* screen)
{
    if (m_isDrawBkgn == true)
    {
        m_Background.LoadImg(file, screen);
    }
}

void MenuGame::Render(SDL_Renderer* screen)
{
    if (m_isDrawBkgn == true)
    {
        m_Background.Render(screen);
    }
}

void MenuGame::MenuAction(SDL_Event events, SDL_Renderer* screen)
{

}

void MenuGame::Free()
{
    m_Background.Free();
}

bool MenuGame::OnRect(int x, int y, SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////

MenuGameStart::MenuGameStart()
{
    m_Select = -1;
}

MenuGameStart::~MenuGameStart()
{
    FreeData();
}


void MenuGameStart::SetImgOptionList(const VT(BaseObject*)& img_list)
{
    FreeData();
    m_ImgOptionList = img_list;
}

void MenuGameStart::FreeData()
{
    if (m_ImgOptionList.empty())
    {
        for (auto x : m_ImgOptionList)
        {
            if (x != NULL)
            {
                x->Free();
            }
        }
        m_ImgOptionList.clear();
    }
}

void MenuGameStart::Render(SDL_Renderer* screen)
{
    MenuGame::Render(screen);
    for (auto x : m_ImgOptionList)
    {
        x->Render(screen);
    }
}

void MenuGameStart::MenuAction(SDL_Event events, SDL_Renderer* screen)
{
    switch (events.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                m_Select = i;
                break;
            }
        }
        break;
    }
    case SDL_MOUSEMOTION:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                ;// m_ImgOptionList[i]->SetTextureIndex(1);
            }
            else
            {
                ;// m_ImgOptionList[i]->SetTextureIndex(0);
            }
        }
        break;
    }
    default: break;
    }
}

///////////////////////////////////////////////////////////////////////
MenuGamePause::MenuGamePause()
{
    m_Select = -1;
}

MenuGamePause::~MenuGamePause()
{
    FreeData();
}


void MenuGamePause::SetImgOptionList(const VT(BaseObject*)& img_list)
{
    FreeData();
    m_ImgOptionList = img_list;
}

void MenuGamePause::FreeData()
{
    if (m_ImgOptionList.empty())
    {
        for (auto x : m_ImgOptionList)
        {
            if (x != NULL)
            {
                x->Free();
            }
        }
        m_ImgOptionList.clear();
    }
}

void MenuGamePause::InitFrameGeo()
{
    int x1 = H_WIDTH - 120;
    int y1 = H_HEIGHT - 60;
    m_Rect.rect_ = { x1, y1, 300, 120 };
    m_Rect.color_ = SDLCommonFun::GetBaseColor(GRAY_COLOR);

    int x2 = m_Rect.rect_.x + 1;
    int y2 = m_Rect.rect_.y + 1;
    int w2 = m_Rect.rect_.w - 1;
    int h2 = m_Rect.rect_.h - 1;

    m_RectOutLine.rect_ = { x2, y2, w2, h2};
    m_RectOutLine.color_ = SDLCommonFun::GetBaseColor(WHITE_COLOR);

    int xPos = m_Rect.rect_.x + 100;
    int yPos = m_Rect.rect_.y + 10;

    for (size_t i = 0; i < m_ImgOptionList.size(); i++)
    {
        m_ImgOptionList[i]->SetRect(xPos, yPos);
        yPos += 50;
    }
}

void MenuGamePause::Render(SDL_Renderer* screen)
{
    Gemometric::RenderRectange(m_Rect, screen);
    Gemometric::RenderOutline(m_RectOutLine, screen);

    MenuGame::Render(screen);
    for (auto x : m_ImgOptionList)
    {
        x->Render(screen);
    }
}

void MenuGamePause::MenuAction(SDL_Event events, SDL_Renderer* screen)
{
    switch (events.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                m_Select = i;
                break;
            }
        }
        break;
    }
    case SDL_MOUSEMOTION:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                m_ImgOptionList[i]->SetTextureIndex(1);
            }
            else
            {
                m_ImgOptionList[i]->SetTextureIndex(0);
            }
        }
        break;
    }
    default: break;
    }
}

///////////////////////////////////////////////////////////////

MenuGameEnd::MenuGameEnd()
{
    m_Select = -1;
    m_Font = NULL;
}

MenuGameEnd::~MenuGameEnd()
{

}

void MenuGameEnd::SetImgOptionList(const VT(BaseObject*)& img_list)
{
    FreeData();
    m_ImgOptionList = img_list;
}


void MenuGameEnd::FreeData()
{
    MenuGame::Free();
    if (m_ImgOptionList.empty())
    {
        for (auto x : m_ImgOptionList)
        {
            if (x != NULL)
            {
                x->Free();
            }
        }
        m_ImgOptionList.clear();
    }

    for (auto t : m_TextList)
    {
        t->Free();
    }
    m_TextList.clear();
}

void MenuGameEnd::Render(SDL_Renderer* screen)
{
    MenuGame::Render(screen);
    for (auto x : m_TextList)
    {
        x->LoadFromRenderText(m_Font, screen);
        x->RenderText(screen);
    }

    for (auto x : m_ImgOptionList)
    {
        x->Render(screen);
    }
}

void MenuGameEnd::MenuAction(SDL_Event events, SDL_Renderer* screen)
{
    switch (events.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                m_Select = i;
                break;
            }
        }
        break;
    }
    case SDL_MOUSEMOTION:
    {
        int x = events.button.x;
        int y = events.button.y;
        for (size_t i = 0; i < m_ImgOptionList.size(); ++i)
        {
            m_ImgOptionList[i]->SetTextureIndex(0);
            SDL_Rect item_rect = m_ImgOptionList[i]->GetRect();
            bool bRet = OnRect(x, y, item_rect);
            if (bRet)
            {
                m_ImgOptionList[i]->SetTextureIndex(1);
            }
            else
            {
                m_ImgOptionList[i]->SetTextureIndex(0);
            }
        }
        break;
    }
    default: break;
    }
}

void MenuGameEnd::SetTextContent(std::string sData, int idx)
{
    if (idx >= 0 && idx < (int)m_TextList.size())
    {
        TextObj* pText = m_TextList[idx];
        if (pText)
        {
            pText->SetText(sData);
        }
    }
}
