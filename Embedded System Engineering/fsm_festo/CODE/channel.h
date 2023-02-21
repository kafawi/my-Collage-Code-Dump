/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/* 
 * @file   channel.h
 * @brief Channel for asynchron communication
 *     
 * @author kafa
 *
 * Created on May 22, 2017, 3:30 AM
 */

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "lock.h"
#include "sPulse.h"

#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#endif

#include <chrono>
#include <queue>
#include <iostream>
#include <cerrno>  

/**
 * @class TemplateInterface for a Channel (FiFo)
 * 
 */
template <typename Type_>
class Channel{
  public:
   /**
    * read out of the channel
    * @return 
    *   The vale the channel is stored 
    */
    virtual inline Type_ dequeue(void)= 0;

    /**
     * write into the channel
     * @param element
     *   Object, that will be stored in the channel
     */
    virtual inline void enqueue(const Type_ element) = 0;

    virtual inline ~Channel(){};
};

/**
 * Simple blocking Software Channel with fixed capacity
 *
 */
template <typename Type_>
class SWChannel : public Channel<Type_>{
  public:
    explicit SWChannel(const size_t capacity)
    : sem_free_space_(capacity)
    , sem_size_()
    , queue_()
    , mtx_()
    {}
    virtual inline ~SWChannel(){};
    size_t 
    size(void) const 
    {
      return sem_size_.get_value();
    }

    size_t
    max_size(void) const 
    {
      return sem_free_space_.get_value() + sem_size_.get_value();
    }
    
    virtual inline Type_ dequeue(void) {
      sem_size_.wait();
      mtx_.lock();
      auto returnData = queue_.front();
      queue_.pop();
      mtx_.unlock();
      sem_free_space_.post();
      return returnData;
    }

    virtual inline void enqueue(const Type_ element) {
      sem_free_space_.wait();
      mtx_.lock();
      queue_.push(element);
      mtx_.unlock();
      sem_size_.post();
    }
    
    void 
    operator<<(const Type_ element) {
      enqueue(element);
    }

    Type_ friend 
    operator<<(Type_& target, SWChannel<Type_>& source) {
      return target = source.dequeue();
    }

    void friend 
    operator<<(SWChannel<Type_>& target,
                          SWChannel<Type_>& source)
    {
      target.enqueue(source.dequeue());
    }
    void 
    destroy() {
      sem_free_space_.destroy();
      sem_size_.destroy();
    }
  private:
    Semaphore sem_free_space_;
    Semaphore sem_size_;
    std::queue<Type_> queue_;
    Mutex mtx_;
};


/**
 * A Channel like the QNX's Pulse channel (in QNX a Wrapper)
 * Non blocking for write into
 */
class PulseChannel: public Channel<Pulse_t>{
 public:
  PulseChannel();
  
  ~PulseChannel();
  
  /**
   * get a Pulse message out of the channel
   * @return 
   *   next (first) pulse
   */
  virtual inline Pulse_t dequeue(void){
#if defined(__QNXNTO__)
    struct _pulse pulse;
    int res = MsgReceivePulse(cid_, &pulse, sizeof (pulse), NULL);
    if (res < 0 ){
      std::perror("ERROR: MsgReceivePulse failed");
    }
    Pulse_t retPulse;
    retPulse.code = pulse.code;
    retPulse.value.i = pulse.value.sival_int;
    return retPulse;
#else
    sem_size_.wait();
    mtx_.lock();
    Pulse_t returnData = queue_.front();
    queue_.pop();
    mtx_.unlock();
    return returnData;
#endif    
  };
  /**
   *  pushes an Pulse Element into the queue
   * 
   * @param element
   *   Pulse message, you want to send
   */
  virtual inline void enqueue(const Pulse_t p){
#if defined(__QNXNTO__)
    int res = MsgSendPulse(con_,-1, static_cast<int>(p.code), static_cast<int>(p.value.i));
    if (res < 0 ){
      std::perror("ERROR: MsgSendPulse failed");
    }
#else
    mtx_.lock(); 
    queue_.push(p);
    mtx_.unlock();
    sem_size_.post();
#endif
  };
  
  virtual inline void enqueue2(const int code, const int value){
  #if defined(__QNXNTO__)
      int res = MsgSendPulse(con_,-1 ,code, value);
      if (res < 0 ){
        std::perror("ERROR: MsgSendPulse failed");
      }
  #else
      mtx_.lock();
      Pulse_t out;
      out.code = code;
      out.value.i = value;
      queue_.push(out);
      mtx_.unlock();
      sem_size_.post();
  #endif
    };

  //extraFunktionen
#if defined(__QNXNTO__)
  int cid_;                 /**< create id  */
  int con_;                 /**< attach id */
  int id_;                    /**< id to connect to channels */
  /**
   * getting the channelId to connect in QNX
   * @return id of channel
   */
  int getId(void);            
#endif
  
  //----------------------------------------------------------------- Attribute
 private:
#if defined(__QNXNTO__)

#else
  Semaphore sem_size_;        /**< semaphor for block reading */
  std::queue<Pulse_t> queue_; /**< queue to store data */
  std::mutex mtx_;            /**< mutex for queue */
#endif
  
};
// ----------------------------------------------------------------- RECEIVER
/**
 * Guarantee the correct use of a channel to read (pull)
 * @param ch
 *   Channel to connect
 */
class PulseReceiver{
 public:
  PulseReceiver(PulseChannel &ch);
  
  /**
   * read and remove out of the channel
   * @return 
   *   value, you want to have
   */
  Pulse_t pull();
  /**
   *  connect to an channel
   * @param ch
   *   reference of the channel to connect to
   */
  void connect(PulseChannel & ch);
  /**
   * removes the reference (pointer) to the channel
   */
  void disconnect();
  
  /**
   * get a pointer of the Channel
   * @return 
   *   pointer of channel 
   */
  PulseChannel * getChannel();
 private:
  PulseChannel *chin_;  /**< Channel to read from*/
};
// --------------------------------------------------------------- Transmitter
/**
 * Guarantee the correct use of a channel to write (push)
 * @param ch
 *   Channel to connect
 */
class PulseTransmitter{
 public:
  PulseTransmitter(PulseChannel &ch);
  /**
   * write into the Channel
   * @param element
   */
  void push(Pulse_t element);
  
  /**
   * connects to a Channel
   * @param ch
   */
  void connect(PulseChannel & ch);
  
  /**
   * removes connection
   */
  void disconnect();
  
  /**
   * Get the Channel
   * @return 
   *   pointer of Channel
   */
  PulseChannel * getChannel();
 private:
  PulseChannel *chout_; /**< Channel to write into */
};

#endif /* _CHANNEL_H */

