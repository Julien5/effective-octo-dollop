#include "clock.h"
#include "debug.h"
#include "platform.h"

namespace Clock {
  ms millis_since_start() {
    return millis();
  }
  
  mn minutes_since_start() {
    return millis_since_start()/(1000L*60);
  }
  
  int test() {
    assert(millis_since_start()==0);
    delay(1000);
    assert(millis_since_start()==1000);
    return 0;
  }
}