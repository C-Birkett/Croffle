// Main entry point for Ogre test app

#include "Application.h"

int main(int argc, char* argv[])
{
  if(App::Init());
  {
    App::StartRendering();  // main loop
  }
  App::Close();

  return 0;
}

