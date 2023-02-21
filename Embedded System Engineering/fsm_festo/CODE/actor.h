/** @file actor.h
 *  @brief defines var behave to react
 *
 *  @author kafawi
 *
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
 
#ifndef ACTOR_H_
#define ACTOR_H_

class DigitalPortStrat;
/**
 * @class shares behave of Actors
 */
class Actor
{
 public:
  void set();

  void turnOn( int port, uint8_t mask);
  void turnOff( int port ,uint8_t mask);
  
 protected:
  DigitalPortStrat& digiStr_;

  Actor(DigitalPortStrat& digiStr):digiStr_(digiStr){};
  virtual ~Actor(){};
};

#endif /* HW_ACTOR_BEHAVE_H_ */
