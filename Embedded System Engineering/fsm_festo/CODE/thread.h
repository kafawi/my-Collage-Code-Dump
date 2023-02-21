/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/**
 * @file thread.h
 * @brief this wrapped the std::thread and defines some Interfaces threadish
 *   
 * The thread is Wrapped in the class Thread, 
 * Also the Worker class is definde, to pass this to an Thread, that he can 
 * execute a Strategy, the Worker holds.
 * 
 * The Strategies are:
 *  Runnable for a one time run
 *  Loopable for a many times run
 *  Stoppable for a many times rum with the ability to get stopped.
 *  
 * @author kafa
 *
 * Created on May 22, 2017, 1:36 AM
 */
#ifndef _THREAD_H
#define _THREAD_H

#include <thread>
#include <chrono>
#include <condition_variable>
#include "lock.h"

/**
 * Wrapper of the std::thread
 */
class Thread {
 public:
 
  using Id = std::thread::id;

  using NativeHandleType = std::thread::native_handle_type;
    
  Thread();
  Thread (Thread &)=delete;
  Thread (const Thread &)=delete;
  Thread (const Thread &&)=delete;
  Thread (Thread &&__t) noexcept;
    
  template<typename _Callable , typename... _Args>
  Thread(_Callable &&__f, _Args &&... __args):
    thread_(std::forward<_Callable>(__f), std::forward<_Args>(__args)...),
    id_(thread_.get_id())
    {}
    
  Thread & operator= (const Thread &)=delete;
    
  Thread & operator= (Thread &&__t) noexcept;
    
  void
  swap(Thread& __t) noexcept;
    
  virtual ~Thread();
    
  static uint32_t hardwareConcurrency() noexcept;
    
  Id getId();
  void detach();
    
  void join();
  bool joinable();
  NativeHandleType native_handle();
    
 private:
  std::thread thread_;   
  Id id_;
};

/**
 * @class A Interface for a Runnable, a Worker class needs as a Strategy  
 */
class Runnable{
 public:
  Runnable();
  virtual ~Runnable();
  /**
   * Function to override. Will be executed by a Worker in a over a thread.
   */
  virtual void run()=0;
};

/**
 * Interface for a Task, that is executed in a loop by a Thread over a Worker
 */
class Loopable: public Runnable{
 public:
  Loopable();
  virtual ~Loopable();
  /**
   * here is the loop nested
   */
  virtual void run();
  /**
   * to stop the loop, if you have other stop conditions inside, please
   * override this as well
   */
  virtual void terminate();
  /**
   * this will set the global isRunning to false to terminate all Loopable 
   */
  static void globalTerminate();
 protected:
  /**
   * repetitiv task, you have to implement 
   */
  virtual void loop()=0;
  /**
   * Returns the boolean value, if the loop is executed 
   * @return true if this is not terminated
   */
  virtual bool isRunning();
  bool isRunning_;  /**< local Condition, to execute the loop*/
 private:
  static bool isRunningGlobal_; /**< global condition to execute loop */
};

/**
 * @class Inferface for an Strategyclass for the Worker Object
 * @param isStopped 
 *   if true, then the is stopped befor is execute the tast in step
 */
class Stoppable: public Loopable{
 public:
  Stoppable(bool isStopped);
  Stoppable();
  /**
   *  this method will be executed by Worker
   */
  virtual void run();
  virtual ~Stoppable();
  /**
   * to Stop the loop 
   * let him sleep an an cond_var
   */
  virtual void stop();
  /**
   * continue the stopped Workerthread
   */
  virtual void conti();
  /**
   * terminate the Workerthread
   */
  virtual void terminate();
 protected:
  /**
   * step is here embedded
   */
  virtual void loop();
  /**
   * is the step is Stopped?
   */
  virtual bool isStopped();
  /**
   * Task you have to do implement, What should your Worker do
   */
  virtual void step() = 0;
 private:
  std::condition_variable convar_; /**< the thread will wait on it*/
  std::mutex mtx_;                 /**< is needed by cond_var */
 protected:
  bool isStopped_;                 /**< indicates to set on stopp */
};

/**
 * @class Workerthread as Functor
 *  that needs an Runnable (stoppable) to do something.
 * This Worker is passed to the Constructor of a Thread to run. 
 */
class Worker{
 public:
  /**
   * Functor
   */
  void operator()();
  /**
   * CTOR
   * @param runner  
   *    Strategy for Worker
   */
  Worker(Runnable &runner);
  /**
   * Dtor
   */
  virtual ~Worker();
 private:
  Runnable *runner_; /**< Strategy */
};

//Worker::operator()(){};
#endif /* _THREAD_H */

