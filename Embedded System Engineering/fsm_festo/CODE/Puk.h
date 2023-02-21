/**
 * @brief Structure holding all Puk properties
 * @author Lennart Hartmann, Nils Eggebrecht
 * @version 16.06.2017
 */

#ifndef PUK_H_INCLUDED
#define PUK_H_INCLUDED
//#include "MCL_dispatcher.h"
#include <cstdint>
#include "timer.h"
#include "MCL_signals.h"
//////////Stub///////////////

enum PukType{
    TYPE_0
  , TYPE_1
  , TYPE_2
  , TYPE_3
  , TYPE_4
  , TYPE_5
  , TYPE_DRILLED
  , TYPE_FLAT
  , TYPE_DRILLED_METAL
  , ULO //unidentified lying object
};

enum Profile{
    FLAT
  , DRILLED
  , BITCODE_0
  , BITCODE_1
  , BITCODE_2
  , BITCODE_3
  , BITCODE_4
  , BITCODE_5
  , UNKNOWN_PROFILE
};


class Puk{
    public:
        Puk(Timer *minTimer, Timer *maxTimer);
        virtual ~Puk();
        int ID;
        bool unknownType;
        bool containsMetal;
        bool sceduledForEjection;
        enum Profile profile;
        uint16_t height1;
        uint16_t height2;
        Timer *minTimer;
        Timer *maxTimer;
        enum PukType getType();
        void setType(PukType type);
        void cancelMaxtimer();
        void resetTimers(enum MCL_input_signal signal);
        void printMe();
    protected:
    private:
     static int ID_iterator;
};

#endif // PUK_H_INCLUDED
