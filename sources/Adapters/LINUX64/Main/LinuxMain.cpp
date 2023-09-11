#include <string.h>
#include "Adapters/LINUX64/System/LinuxSystem.h"
#include "Adapters/SDL/GUI/SDLGUIWindowImp.h"
#include "Application/Application.h"


int main(int argc,char *argv[]) {
  LinuxSystem::Boot(argc,argv);

  SDLCreateWindowParams params;
  params.title = "littlegptracker";
  params.cacheFonts_ = true;

  Application::GetInstance() -> Init(params);

  return LinuxSystem::MainLoop();
}
