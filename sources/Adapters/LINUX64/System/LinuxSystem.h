#include <SDL/SDL.h>
#include "System/System/System.h"
#include "UIFramework/SimpleBaseClasses/EventManager.h"

class LinuxSystem: public System {
  public:
    static void Boot(int argc, char**argv);
    static int MainLoop();
    static void ShutDown();

  public:
    virtual unsigned long GetClock();
    virtual void Sleep(int millisec);
    virtual void *Malloc(unsigned size);
    virtual void Free(void *);
    virtual void Memset(void *addr,char val,int size);
    virtual void *Memcpy(void *s1, const void *s2, int n);
    virtual void AddUserLog(const char *);
    virtual int GetBatteryLevel();
    virtual void PostQuitMessage();
    virtual unsigned int GetMemoryUsage();

  protected:
    static unsigned short getButtonMask(SDL_Event&);
    static void readConfig();
    static void checkKey(int ,const char *,const char *[]);

  private:
    static int keyRepeat_;
    static int keyDelay_;
    static bool finished_;
    static EventManager *eventManager_;
};
