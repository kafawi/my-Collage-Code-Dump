/**
 * @brief Provisonal Adapter to QNX console interaction
 * @author Lennart Hartmann
 * @version 17.06.2017
 */
#ifndef HDI_MANAGER_H
#define HDI_MANAGER_H
#include "Puk.h"
#include <string>

enum ErrorType{
    MISSING_WORKPIECE_IN_PROFILE_DETECTION,
    UNEXPECTED_OBJECT_IN_PROFILE_DETECTION,
    MISSING_WORKPIECE_IN_METAL_DETECTION,
    UNEXPECTED_OBJECT_IN_METAL_DETECTION,
    MISSING_WORKPIECE_IN_OUTLET,
    UNEXPECTED_OBJECT_IN_OUTLET,
    BOTH_SLIDES_FULL,
    SLIDE_OBSTRUCTED,
    NUMBER_OF_ERRORTYPES // for Array-Creation - last enum! Additional enums add above!
};

class HDI_Manager
{
 public:
  virtual void printPukdata(Puk* puk);
  virtual void printError(ErrorType errtype);
  HDI_Manager();
  virtual ~HDI_Manager();

 protected:

 private:

	std::string errMessages[NUMBER_OF_ERRORTYPES];
};

#endif // HDI_MANAGER_H
