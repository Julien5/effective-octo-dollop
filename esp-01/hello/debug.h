#pragma once

#ifndef ARDUINO
#include <iostream>
#include <cassert>
#define debug(X)							\
  do {									\
    std::cout << __LINE__ << ":" << #X << "=" << (X) << std::endl;	\
  } while(0)
#define DBGTX(X)					\
  do {							\
    std::cout << __LINE__ << ":" << #X << "=" << (X);	\
  } while(0)
#define DBGTXLN(X)							\
  do {									\
    std::cout << __LINE__ << ":" << #X << "=" << (X) << std::endl;	\
  } while(0)

#define TRACE()					\
  do {						\
    static int __counter__ = 0;			\
    std::cout << __FILE__;			\
    std::cout << ":";				\
    std::cout << __LINE__;			\
    std::cout << ":";				\
    std::cout << counter++ << "\n";		\
  } while(0)

using test_ms = uint32_t;
test_ms millis();
void delay(test_ms d);


#else

/*
 * note: in debug mode, DBGTX takes memory.
 * reduce NDATA
 */

#include "Arduino.h"
#include "HardwareSerial.h"
#if 0
#define DBGTX(X)				\
  do {						\
    Serial.write((X));				\
  } while(0)
#define DBGTXLN(X)				\
  do {						\
    Serial.println((X));			\
  } while(0)
#define TRACE()					\
  do {						\
    Serial.print(__FILE__);			\
    Serial.print(":");				\
    Serial.print(__LINE__);			\
    Serial.print(":");				\
    printMemory(0);				\
  } while(0)
#else
#define DBGTX(X) ((void) 0)
#define DBGTXLN(X) ((void) 0)
#define TRACE() ((void) 0)
#endif
#define assert(ignore)
#define debug(X)((void) 0)
#endif
