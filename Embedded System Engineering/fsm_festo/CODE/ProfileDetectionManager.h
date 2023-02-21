#ifndef PROFILEDETECTIONMANAGER_H
#define PROFILEDETECTIONMANAGER_H

#include "Data.h"
#include <iostream>
#include <string>

using namespace std;

class ProfileDetectionManager
{
 private:

  struct State
  {//top-level state
    virtual string getName();
    virtual void reportEnterProfileDetection();
    virtual void reportLeavingProfileDetection();
    virtual void reportMintimerToProfileDetectionExpired();
    virtual void reportMaxtimerToProfileDetectionExpired();
    virtual void reportProfileDetectionTimeout();
    virtual void ignoreTiming();

    Data* data; // pointer to data, which physically resides inside the context class (contextdata)
  } *statePtr; // a pointer to current state. Used for polymorphism.

  struct Idle : public State
  {
    virtual string getName();
    virtual void reportEnterProfileDetection();
    virtual void reportMintimerToProfileDetectionExpired();
  };

  struct UntrackedWorkpiece : public State
  {
    virtual string getName();
    virtual void ignoreTiming();
  };

  struct MissingWorkpiece : public State
  {
    virtual string getName();
    virtual void ignoreTiming();
  };

  struct Ready : public State
  {
    virtual string getName();
    virtual void reportEnterProfileDetection();
    virtual void reportMaxtimerToProfileDetectionExpired();
  };

  struct Processing : public State
  {
    virtual string getName();
    virtual void reportLeavingProfileDetection();
  };

  //stateMember;//The memory for the state is part of context object
  Idle stateMember; //The memory for the state is part of context object
  Data *contextdata; //Data is also kept inside the context object

 public:// assigning start state
  ProfileDetectionManager();
  ProfileDetectionManager(Data *data);
  ~ProfileDetectionManager();

  string getName();
  void reportEnterProfileDetection();
  void reportLeavingProfileDetection();
  void reportMintimerToProfileDetectionExpired();
  void reportMaxtimerToProfileDetectionExpired();
  void ignoreTiming();
  void reportPuktype();
  void reportProfileDetectionTimeout();
};
#endif // PROFILEDETECTIONMANAGER_H
