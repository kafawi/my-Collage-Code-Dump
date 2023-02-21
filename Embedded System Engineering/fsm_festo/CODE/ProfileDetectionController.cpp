#include "ProfileDetectionController.h"
#include "mcl.h"
#include "MCL_signals.h"
#include "HAL_commands.h"
#include "ProfileDetection_signals.h"
#include <iostream>
#include <utility>
ProfileDetectionController::ProfileDetectionController (Data *data)
: sensorIn_ (*(Mcl::getInstance ()->getChAnalogSensorIn ()))
, sensorOut_ (*(Mcl::getInstance ()->getChActorOut ()))
, mclMasterTrans_ (*(Mcl::getInstance ()->getChMasterControlIn ()))
, data (data)
, processedPuk (nullptr)
, bucketList_ ()
, th_ (nullptr)
, worker_ (nullptr)
{
	  worker_ = new Worker (*this);
	  th_ = new Thread ((*worker_));
	  std::cout << "ProfileDetectionCtrl ctor"  << std::endl;
  //ctor
}
ProfileDetectionController::~ProfileDetectionController () {
	  th_->join ();
	  delete ( th_);
	  delete ( worker_);
  //dtor
}
void
ProfileDetectionController::requestDetection ()
{
  //todo: real implementation
  Pulse_t pout;
  pout.code = PROFILOMETER;
  pout.value.i = START_SAMPLING;
  processedPuk = data->pukInProfileDetection;
  sensorOut_.push (pout);
  std::cout << "sensorOutChannel <- request Detection" << std::endl;
  std::cout << "worker: sensorInChannel => sensor data" << std::endl;

}
void
ProfileDetectionController::stopDetection ()
{
  Pulse_t pout;
  pout.code = PROFILOMETER;
  pout.value.i = END_SAMPLING;
  sensorOut_.push (pout);
  //todo: real implementation
  std::cout << "worker: evaluating sensor data" << std::endl;
  std::cout << "writing data to processedPuk" << std::endl;
}
void
ProfileDetectionController::step ()
{
  Pulse_t pin = sensorIn_.pull ();
  static std::list<Bucket> bucketList_;
  switch (pin.code)
  {
    case(SAMPLE):
    {
      if (bucketList_.empty ()) {
          bucketList_.push_back(Bucket(pin.value.i,0));
      } else {
    	  int16_t lastx = bucketList_.back ().x;
    	  if (
    	     (lastx - TOLERANCE) >= pin.value.i ||
    	     (lastx + TOLERANCE) <= pin.value.i
    	     )
    	  {
            bucketList_.push_back(Bucket(pin.value.i,0));
    	  } else {
            bucketList_.back ().x = ((5*lastx)+pin.value.i)/6;
            bucketList_.back ().n += 1;
    	  }
      }

    }
      break;
    case(ENDSAMPLING):
    {
      int16_t minValue_ = bucketList_.front ().x;
      int16_t maxValue_ = bucketList_.back ().x;
      int16_t range = 0;
      std::list<int16_t> list;
      for (std::list<Bucket>::iterator it = bucketList_.begin ();
              it != bucketList_.end ();
              it++)
      {
        std::cout << "x: " << it->x << " n: " <<  it->n << "\n";
        if (it->n > MIN_N)
        {
          if (list.empty ())
          {
            list.push_back (it->x);
          }
          else if (list.back () - TOLERANCE <= it->x ||
                   list.back () + TOLERANCE >= it->x)
          {
            list.push_back (it->x);
          }
        }
        if (minValue_ > it->x) minValue_ = it->x;
        if (maxValue_ < it->x) maxValue_ = it->x;
      }
      for (std::list<int16_t>::iterator it = list.begin (); it != list.end (); it++){
        std::cout << "list : " << *it - minValue_ << "\n";
      }
      range = maxValue_ - minValue_;
      std::cout << "range " << range <<std::endl;
      if (data->isReceivingEnd)
      {
        processedPuk->height2 = range;
      }
      else
      {
        processedPuk->height1 = range;
      }
      // calc the delta
      std::list<int16_t> delta;
      int16_t deltaLo = maxValue_;
      int16_t deltaHi = 0;
      for (std::list<int16_t>::iterator it = list.begin ();
              it != list.end ();
              it++)
      {
        int16_t tmp = *it - minValue_;
        if (2*TOLERANCE <= tmp && (range - 2*TOLERANCE) >= tmp)
        {
          delta.push_back (tmp);
          if (deltaLo > tmp) deltaLo = tmp;
          if (deltaHi < tmp) deltaHi = tmp;
          std::cout << "\n delta:" << tmp << std::endl;
        }
      }
      for (std::list<int16_t>::iterator it = delta.begin ();
           it != delta.end();
           it++){
             *it = *it/(deltaHi - TOLERANCE);
             std::cout << "\n it: " << *it <<std::endl;
      }
      std::cout << "\n Lo: " << deltaLo << " HI: " << deltaHi << std::endl;
      // jetzt habe wir die delta;
      // jetzt müssen wir die irgendwie auf binär mappen
      // großes Delta, heißt tiefes loch == 1
      // kleines Delta, -> flaches Loch == 0
      uint8_t bincode = 0;
      int binpos = 0;
      std::cout << "\n deltasize: " << delta.size () << std::endl;
      //std::cout << "\n VOR DER DELTA.SIZE GEDoeNSTE" << std::endl;
      switch (delta.size ())
      {
        case(0):
          processedPuk->profile = FLAT;
        std::cout << "Puktype FLAT" << std::endl;
        break;
        case(1):
        case(2):
          processedPuk->profile = DRILLED;

        std::cout << "Puktype DRILLED" << std::endl;
        break;
        default:
        	 std::cout << "Puktype DD" << std::endl;
          for (std::list<int16_t>::iterator it = delta.begin ();
                  it != delta.end ();
                  it++)
          {
           bincode += (*it << binpos);
           binpos++;
          }
          while (binpos > 2)
          {
            std::cout << "shit bincode is too large" << static_cast<int>(bincode)<< std::endl;
            bincode = bincode & 0b111;
            binpos--;
          }
          bincode = bincode & 0b111;
          switch (bincode)
          {
            case(0):
              processedPuk->profile = BITCODE_0;
            std::cout << "Puktype 0" << std::endl;
              break;
            case(1):
              processedPuk->profile = BITCODE_1;
            std::cout << "Puktype 1" << std::endl;
              break;
            case(2):
              processedPuk->profile = BITCODE_2;
            std::cout << "Puktype 2" << std::endl;
              break;
            case(3):
              processedPuk->profile = BITCODE_3;
            std::cout << "Puktype 3" << std::endl;
              break;
            case(4):
              processedPuk->profile = BITCODE_4;
            std::cout << "Puktype 4" << std::endl;
              break;
            case(5):
              processedPuk->profile = BITCODE_5;
            std::cout << "Puktype 5" << std::endl;
              break;
            default:
              processedPuk->profile = UNKNOWN_PROFILE;
              std::cout << "Puktype u" << std::endl;
          }
          break;
      }
      bucketList_.clear();
      Pulse_t pout;
      pout.code= INCOMMING_CODE;
      pout.value.i = PROFILE_DETECTED;
      mclMasterTrans_.push (pout);
      break;
    }
  }
}
