#pragma once
//
//    FILE: HX710AB.h (Marlin-compatible version)
//  AUTHOR: Rob Tillaart (modified for Marlin)
// VERSION: 0.2.0-MARLIN
// PURPOSE: Marlin-compatible library for HX710A/B 24-Bit ADC
//    DATE: 2024-11-08 (modified 2023-08-20)

#include "../inc/MarlinConfig.h"
#include "../inc/MarlinConfigPre.h"

// Remove Arduino dependencies
#define HX710AB_LIB_VERSION "0.2.0-MARLIN"

// Marlin-compatible GPIO macros
#define HX_READ(pin)    READ(pin)
#define HX_WRITE(pin,v) WRITE(pin,v)
#define HX_MODE_IN(pin) SET_INPUT(pin)
#define HX_MODE_OUT(pin) SET_OUTPUT(pin)

//////////////////////////////////////////////////////////////////////////////
class HX710AB
{
public:
  HX710AB(pin_t dataPin, pin_t clockPin)
  {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _value = 0;
    _lastTimeRead = 0;
    _fastProcessor = false;
    _offset = 0;
    _scale = 1;
  };

  void begin(bool fastProcessor = false)
  {
    HX_MODE_IN(_dataPin);
    HX_MODE_OUT(_clockPin);
    HX_WRITE(_clockPin, LOW);
    _fastProcessor = fastProcessor;
  };

  // Modified read functions for Marlin
  bool is_ready()
  {
    return (HX_READ(_dataPin) == LOW);
  };

protected:
  void clock_pulse()
  {
    HX_WRITE(_clockPin, HIGH);
    if (_fastProcessor) DELAY_US(1);
    HX_WRITE(_clockPin, LOW);
    if (_fastProcessor) DELAY_US(1);
  };

  pin_t   _dataPin;
  pin_t   _clockPin;
  uint32_t _lastTimeRead;
  int32_t  _value;
  bool     _fastProcessor;
  float    _offset;
  float    _scale;
};

//////////////////////////////////////////////////////////////////////////////
class HX710B : public HX710AB
{
public:
  HX710B(pin_t dataPin, pin_t clockPin) : HX710AB(dataPin, clockPin) {};

  int32_t fetch(bool differential = true)
  {
    _value = 0;
    for (uint8_t i = 0; i < 24; i++)
    {
      clock_pulse();
      _value <<= 1;
      if (HX_READ(_dataPin)) _value++;
    }

    // Differential mode handling
    clock_pulse();
    clock_pulse();
    if (differential) clock_pulse();

    _lastTimeRead = millis();
    if (_value & 0x800000) _value |= 0xFF000000;
    return _value;
  };
};
// -- END OF FILE --