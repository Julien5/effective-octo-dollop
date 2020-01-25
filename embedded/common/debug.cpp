#include "debug.h"

#ifdef DEVHOST
void debug::turnBuildinLED(bool on) {
}
int debug::freeMemory() {
  return 0;
}
#endif

#ifdef ESP8266
#include "driver/gpio.h"
void debug::turnBuildinLED(bool on) {
  static bool init_done=false;
  if (!init_done) {
    gpio_config_t conf;
    conf.pin_bit_mask = GPIO_Pin_2;
    conf.intr_type = GPIO_INTR_DISABLE;
    conf.mode = GPIO_MODE_OUTPUT;
    conf.pull_up_en = GPIO_PULLUP_DISABLE;
    conf.pull_down_en =GPIO_PULLDOWN_DISABLE;
    gpio_config(&conf);
    init_done=true;
  }
  if (on)
    gpio_set_level(GPIO_NUM_2,1);
  else
    gpio_set_level(GPIO_NUM_2,0);
}
int debug::freeMemory() {
  // FIXME
  return 0;
}
#endif

#ifdef ARDUINO
#include "Arduino.h"
void debug::turnBuildinLED(bool on) {
  pinMode(LED_BUILTIN, OUTPUT);
  if (on)
    digitalWrite(LED_BUILTIN,HIGH);
  else
    digitalWrite(LED_BUILTIN,LOW);
}
extern char __heap_start;
extern void *__brkval;
struct __freelist {
  size_t sz;
  struct __freelist *nx;
};
extern struct __freelist *__flp;
namespace {
  int freeListSize() {
  struct __freelist* current;
  int total = 0;
  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }
  return total;
}
}

int debug::freeMemory() {
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
    free_memory += freeListSize();
  }
  return free_memory;
}
#endif
