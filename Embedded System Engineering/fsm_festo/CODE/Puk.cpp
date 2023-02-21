/**
 * @brief Structure holding all Puk properties
 * @author Lennart Hartmann, Nils Eggebrecht
 * @version 16.06.2017
 */
#include "Puk.h"
#include "timerController.h"
#include "timer.h"
#include <iostream>
Puk::Puk (Timer * minTimer, Timer * maxTimer)
: ID (ID_iterator++)
, unknownType (true)
, containsMetal (false)
, sceduledForEjection (false)
, profile (UNKNOWN_PROFILE)
, height1 (0)
, height2 (0)
, minTimer (minTimer)
, maxTimer (maxTimer) { }
Puk::~Puk ()
{
  minTimer->destroy ();
  maxTimer->destroy ();
}
enum PukType
Puk::getType ()
{
  enum PukType type = ULO;
  switch (profile)
  {
    case(FLAT):
      type = TYPE_FLAT;
      break;
    case(DRILLED):
      if (!containsMetal)
      {
        type = TYPE_DRILLED;
      }
      else
      {
        type = TYPE_DRILLED_METAL;
      }
      break;
    case(BITCODE_0):
      type = TYPE_0;
      break;
    case(BITCODE_1):
        type = TYPE_1;
      break;
    case(BITCODE_2):
        type = TYPE_2;
      break;
    case(BITCODE_3):
        type = TYPE_3;
      break;
    case(BITCODE_4):
        type = TYPE_4;
      break;
    case(BITCODE_5):
        type = TYPE_5;
      break;
    case(UNKNOWN_PROFILE):
      if (containsMetal)
      {
        type = TYPE_DRILLED_METAL;
      }
      break;
  }
  return type;
}
void
Puk::setType (PukType type)
{
  switch (type)
  {
    case(TYPE_0):
      containsMetal = false;
      profile = BITCODE_0;
      break;
    case(TYPE_1):
      containsMetal = false;
      profile = BITCODE_1;
      break;
    case(TYPE_2):
      containsMetal = false;
      profile = BITCODE_2;
      break;
    case(TYPE_3):
      containsMetal = false;
      profile = BITCODE_3;
      break;
    case(TYPE_4):
      containsMetal = false;
      profile = BITCODE_4;
      break;
    case(TYPE_5):
      containsMetal = false;
      profile = BITCODE_5;
      break;
    case(TYPE_DRILLED):
      containsMetal = false;
      profile = DRILLED;
      break;
    case(TYPE_FLAT):
      containsMetal = false;
      profile = FLAT;
      break;
    case(TYPE_DRILLED_METAL):
      containsMetal = true;
      profile = DRILLED;
      break;
    case(ULO):
      containsMetal = false;
      profile = UNKNOWN_PROFILE;
      break;
  }
}
void
Puk::cancelMaxtimer ()
{
  maxTimer->cancel ();
}
void
Puk::resetTimers (enum MCL_input_signal signal)
{
  std::cout << "Bitte diese Funktion nicht verwenden" << std::endl;
}

void
Puk::printMe(){
	std::cout << "Puk --" << ID << "h1-2" << height1 << "-" << height2 << std::endl;
}

int
Puk::ID_iterator = 0;
