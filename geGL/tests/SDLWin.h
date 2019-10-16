#pragma once

class SDLWinImpl;
class SDLWin{
  public:
    enum ContextType{
      CORE,
      COMPATIBILITY,
      ES,
    };
    SDLWin(int w=1,int h=1,int version = 450,ContextType type = CORE);
    ~SDLWin();
    void beginFrame();
    void endFrame();
  private:
    SDLWinImpl*impl = nullptr;
};
