#ifndef PROFILEDETECTIONCONTROLLER_H
#define PROFILEDETECTIONCONTROLLER_H
#include "Data.h"
#include "Puk.h"
#include "thread.h"
#include "channel.h"
#include <list>
#include <vector>

#define TOLERANCE  10
#define MIN_N      12

class Bucket{
public:
  Bucket():x(0),n(0){
  };
  Bucket(int xx, int nn):x(xx),n(nn){
  };
  Bucket( const Bucket &b): x(b.x), n(b.n){};
  ~Bucket(){};
  int16_t x;   /** value   */
  int16_t n;   /** number */
};

class ProfileDetectionController : public Stoppable
{
 public:
  ProfileDetectionController(Data *data);
  virtual ~ProfileDetectionController();
  void requestDetection();
  void stopDetection();
  void step();
 protected:

 private:
  PulseReceiver sensorIn_;
  PulseTransmitter sensorOut_;
  PulseTransmitter mclMasterTrans_;
  Data *data;
  Puk *processedPuk;
  std::list<Bucket> bucketList_;
  Thread *th_;
  Worker * worker_;
  //todo: Channel *sensorOutChannel;
  // Channel * sensorInChannel
  // Channel *dispatcherInputChannel
  // Thread *worker
};

#endif // PROFILEDETECTIONCONTROLLER_H
