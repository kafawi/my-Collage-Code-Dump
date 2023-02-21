/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/* 
 * @file  lock.h
 * 
 * Wrapping some Mutexte and creating a Semaphore
 * @author kafa
 *
 * Created on May 22, 2017, 2:04 AM
 */

#ifndef _LOCK_H
#define _LOCK_H

#include <mutex>
#include <condition_variable>
#include <cstddef>
/**
 * @class 
 *   Interface of the Lock class to guarantee
 *   Threadsaftyness in critical section
 */
class Lock 
{
  // --------------------------------------------------------------- methods ---
  public:
    /**
     * Desructor
     */
    virtual ~Lock(){};
    /**
     * block critical section
     */
    virtual void acquire() = 0;
    /**
     * free critical section
     */
    virtual void release() = 0;
    
    void lock(){
        acquire();
    }
    
    void unlock(){
        release();
    }
};

/**
 * @class Mutexwrapper
 *
 *
 */
class Mutex : public Lock {
  // --------------------------------------------------------------- methods ---
  public:
      
    /**
     * Constructor
     */
    Mutex()
    {   
    }
    /**
     * Destructor
     */
    virtual ~Mutex(){
    }
    
    /**
     * block critical section
     */
    virtual void acquire(){
        mutex_.lock();
    }

    /**
     * free critical section
     */
    virtual void release(){
        mutex_.unlock();
    }
    /*
    virtual std::mutex
    base(){
      return mutex_;
    }
    */
  // ------------------------------------------------------------ attributes ---
  protected:
    /**
     * mutex from the sdl
     */
    std::mutex mutex_;
};
/*
class ConditionalVariable{
 public:
  ConditionalVariable(){};
  ~ConditionalVariable()
  {
    convar_.~condition_variable();
  };
  
  void wait();
  
  void notiefy_one();
  
  void notiefy_all();
 private:
  std::condition_variable convar_;
};
*/

/**
 * @class Semaphore, if its count is 0 it blocks  
 * @param count 
 *   initial count
 */
class Semaphore : public Lock{
public:
    Semaphore(const size_t count = 0)
        : count_(count)
        , condition_()
        , mtx_()
    {}
    
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;
    Semaphore(Semaphore&&) = delete;
    Semaphore& operator=(Semaphore&&) = delete;
    
    /**
     * Semaphore watched region is needed
     */
    inline void post(void) {
        std::lock_guard<std::mutex> lock(mtx_);
        count_++;
        condition_.notify_one();
    }
    
    /**
     * Semaphore watched region is freed
     */
    inline void wait(void) {
        std::unique_lock<std::mutex> lock(mtx_);
        condition_.wait(lock, [&]{return count_>0;});
        count_--;
    }

    /**
     * block critical section
     */
    virtual void acquire(){
        wait();
    }
    /**
     * free critical section
     */
    virtual void release(){
        post();
    }

    inline bool try_wait(void) {
        std::unique_lock<std::mutex> lock(mtx_);
        if(count_ > 0) {
            count_--;
            return true;
        }
        return false;
    }
    
    inline size_t get_value() const 
    {
      return count_; 
    }
    
    /**
     * free all blocking threads
     */
    void destroy(){
      condition_.notify_all(); 
    }
    
    

private:
    size_t count_; /**< indicater for the blocking Semaphore */
    std::condition_variable condition_; /**< Thing to get a Q for blocked */
    std::mutex mtx_; /**< needet by con var */
};

#endif /* _LOCK_H */
// ----------------------------------------------------------------------- EOF -

