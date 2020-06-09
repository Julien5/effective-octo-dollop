#pragma once

#if defined(DEVHOST)
#include <cassert>
#include <stdio.h>
#include <mutex>
static std::mutex stdout_mtx;

#define DBG(...)						\
  do {								\
    std::unique_lock<std::mutex> lock(stdout_mtx);		\
    printf("%s:%s:%d: ",__FILE__,__FUNCTION__,__LINE__);	\
    printf(__VA_ARGS__);					\
    fflush(stdout); \
  } while(0)
#define TRACE()							\
  do {								\
    std::unique_lock<std::mutex> lock(stdout_mtx);		\
    printf("%s:%s:%d TRACE\n",__FILE__,__FUNCTION__,__LINE__);	\
    fflush(stdout);						\
  } while(0)

#elif defined(ARDUINO)

#if !defined(NDEBUG)
/*
 * note: in debug mode, DBGTX takes memory.
 * reduce NDATA
 */
#include "Arduino.h"
#include "HardwareSerial.h"
#define DBG(...)				\
  do {						\
    printf("%s:%d: ",__FILE__,__LINE__);	\
    char buffer[32];				\
    snprintf(buffer, 32,__VA_ARGS__);		\
    Serial.print(buffer);			\
    Serial.flush();				\
  } while(0)
#define TRACE()					\
  do {						\
    Serial.print(__FILE__);			\
    Serial.print(":");				\
    Serial.print(__LINE__);			\
    Serial.println(": TRACE");			\
    Serial.flush();				\
  } while(0)
#define assert(x)				\
  do {						\
    if(!(x)) {					\
      Serial.print(__FILE__);			\
      Serial.print(":");			\
      Serial.print(__LINE__);			\
      Serial.println(": ASSERT");		\
      while(1){Serial.flush();};		\
    }						\
  } while(0)
#else
#define DBG(...) ((void) 0)			
#define TRACE() ((void) 0)
#define assert(ignore)
#endif

#elif defined(ESP8266)

#if !defined(NDEBUG)
#include <stdio.h>
#define DBG(...)				\
  do {						\
    printf("%s:%d: ",__FILE__,__LINE__);	\
    printf(__VA_ARGS__);			\
  } while(0)
#define TRACE()					\
  do {						\
    printf("%s:%d TRACE\n",__FILE__,__LINE__);	\
  } while(0)
#ifndef assert
#define assert(x)				\
  do {						\
    if(!(x)) {					\
      DBG("\r\n%s:%d assertion failed\r\n",__FILE__,__LINE__);	\
      while(1){};				\
    }						\
  } while(0)
#endif
#endif

#else

#define DBG(X) ((void) 0)			
#define TRACE() ((void) 0)
#define assert(ignore)

#endif

namespace debug {
  //! necessary for Serial.print in Arduino
  void init_serial();
  void turnBuildinLED(bool on);
  void address_range(const char *, void *, size_t L);
  int freeMemory();
}
