#pragma once

class sdcard {
public:
  sdcard();
  void init();
  void info();
  void write(const char * filename, const uint8_t * data, const size_t length);
};