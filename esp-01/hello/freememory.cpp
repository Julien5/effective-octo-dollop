#include "debug.h"

#ifdef ARDUINO

#include <Arduino.h>

extern char __heap_start;
extern void *__brkval;

/*
 * The free list structure as maintained by the
 * avr-libc memory allocation routines.
 */
struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

#include "freememory.h"

/* Calculates the size of the free list */
int freeListSize() {
  struct __freelist* current;
  int total = 0;
  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }
  return total;
}

int freeMemory() {
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
    free_memory += freeListSize();
  }
  return free_memory;
}

int min_free_mem=2048;

void printMemory(int marker) {
  Serial.print("mem(");
  Serial.print(int(marker));
  Serial.print(")=");
  int m=freeMemory();
  if (m<min_free_mem)
    min_free_mem=m;
  Serial.print(m);
  Serial.print(" min=");
  Serial.println(min_free_mem);
}

#else

extern "C" {
  void printMemory(char marker) {
    DBG("mem");
  }
}

#endif
