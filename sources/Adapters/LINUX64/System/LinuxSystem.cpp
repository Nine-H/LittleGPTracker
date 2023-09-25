#include "LinuxSystem.h"
#include "Adapters/Dummy/Audio/DummyAudio.h"
#include "Adapters/Dummy/Midi/DummyMidi.h"
#include "Adapters/SDL/GUI/GUIFactory.h"
#include "Adapters/SDL/GUI/SDLEventManager.h"
#include "Adapters/SDL/GUI/SDLGUIWindowImp.h"
#include "Adapters/SDL/Process/SDLProcess.h"
#include "Adapters/SDL/Timer/SDLTimer.h"
#include "Adapters/Unix/FileSystem/UnixFileSystem.h"
#include "System/Console/Logger.h"
#include <malloc.h>

#ifdef USE_SDLAUDIO
#include "Adapters/SDL/Audio/SDLAudio.h"
#endif

EventManager *LinuxSystem::eventManager_ = NULL;


void LinuxSystem::AddUserLog(const char *msg) {
  fprintf(stderr,"LOG: %s\n",msg) ;
};


void LinuxSystem::Boot(int argc,char **argv) {
  System::Install(new LinuxSystem());

  // install filesystem
  FileSystem::Install(new UnixFileSystem());
  Path::SetAlias("bin", ".");
  Path::SetAlias("root", ".");

  // setup logger
  Trace::GetInstance() -> SetLogger(*(new StdOutLogger()));

  // install gui
  I_GUIWindowFactory::Install(new GUIFactory());

  // install timers
  TimerService::GetInstance() -> Install(new SDLTimerService());

  // install audio
  AudioSettings hint;
  hint.bufferSize_ = 1024;
  hint.preBufferCount_ = 8;
  Audio::Install(new DummyAudio(hint));

  #ifdef USE_SDLAUDIO
  Audio::Install(new SDLAudio(hint));
  #endif

  // install midi
  MidiService::Install(new DummyMidi());

  // install threads
  SysProcessFactory::Install(new SDLProcessFactory());
  if (SDL_Init(SDL_INIT_EVENTTHREAD | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0) {
      return;
  }
  SDL_EnableUNICODE(1);
  atexit(SDL_Quit);

	eventManager_ = I_GUIWindowFactory::GetInstance() -> GetEventManager();
	eventManager_ -> Init();
};


void LinuxSystem::Free(void *ptr) {
  free(ptr);
};


int LinuxSystem::GetBatteryLevel() {
  return -1;
}


unsigned long LinuxSystem::GetClock() {
  return 0;
}


unsigned int LinuxSystem::GetMemoryUsage() {
  return 0;
};


int LinuxSystem::MainLoop() {
  eventManager_ -> InstallMappings();
  return eventManager_ -> MainLoop();
};


void *LinuxSystem::Malloc(unsigned size) {
  void *ptr = malloc(size);
  return ptr;
};


void LinuxSystem::Memset(void *addr,char val,int size) {
  memset(addr, val, size);
};


void *LinuxSystem::Memcpy(void *s1, const void *s2, int n) {
  return memcpy(s1, s2, n);
};


void LinuxSystem::PostQuitMessage() {
	SDLEventManager::GetInstance() -> PostQuitMessage() ;
};


void LinuxSystem::ShutDown() {};


void LinuxSystem::Sleep(int millisec) {};
