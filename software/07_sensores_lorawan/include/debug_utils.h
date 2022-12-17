/*
debug_utils.h - Simple debugging utilities.
*/

#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H


#ifdef DEBUG
  #define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
  #define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__);
#else
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTLN(...)
  #define DEBUG_PRINTF(...)
#endif

#endif