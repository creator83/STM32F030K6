#include "device.h"             // Device header
#include "pin.h"


#ifndef BUTTON_H
#define BUTTON_H

class Button
{
//variables
public:
private:
  uint16_t counter;
  bool shortPress;
  bool longPress;
  bool lastState;
  //bool pushState;
  bool currentState;
  uint8_t state;
  uint16_t shortLimit;
  uint16_t longLimit;
  void (*shortFunction)();
  void (*longFunction)();
  uint8_t p;
  Pin pin_;
//func
public:
Button (Gpio::Port, uint8_t pin_);
  void scanButton ();
  void scanAction ();
  void setShortLimit (uint16_t);
  void setLongLimit (uint16_t);
  bool & getShortPress (){return shortPress;}
  bool & getLongPress (){return longPress;}
  void setshortPressAction (void (*f)());
  void setlongPressAction (void (*f)());
};

#endif
