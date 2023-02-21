/**
 * @brief   Controlling warning lights by addressing HAL
 * @author  Lennart Hartmann
 * @version 07.06.2017
 */
#ifndef WARNINGLIGHTSCONTROLLER_H
#define WARNINGLIGHTSCONTROLLER_H

#include "thread.h"
#include "channel.h"
//class Thread;
//class Worker;

enum Color {GREEN, YELLOW, RED};

#define PERIOD1000MS     1000
#define PERIOD500MS       500
#define FLASHTIMESYELLOW    3

class WarningLightsController :public Stoppable
{
    public:
        WarningLightsController();
        virtual ~WarningLightsController();
        void setGreen(bool on);
        void setRed(bool on);
        void setYellowFlash(bool on);
        void setFlashFast(bool on);
        void setFlashSlow(bool on);
        virtual void step();
        void stop();
        
    private:
      int flashPeriod_;
      Color flashCol_; 
      int flashCountDown_;
      bool redOn_;
      bool yellowOn_;
      bool greenOn_;
      PulseTransmitter trans_;
      Pulse_t pout_;
      Thread *th_;
      Worker *worker_;
};

#endif // WARNINGLIGHTSCONTROLLER_H
