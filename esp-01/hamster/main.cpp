#include "application.h"

extern "C" {
  void setup()
  {
    application::setup();
  }

  void loop() {
    application::loop();
  }
}

#ifdef DEVHOST
int main(int argc, char ** argv) {
  setup();
  while(true) {
    loop();
  }
  return 0;
}
#endif
