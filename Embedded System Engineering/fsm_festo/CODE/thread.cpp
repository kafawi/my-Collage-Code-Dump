/**
 *  Embedded System Engineering SoSe 2017
 *  Copyright (c) 2017  LANKE devs
 *  This software is licensed by MIT License.
 *  See LICENSE.txt for details.
 */
/* 
 * File:   thread.cpp
 * Author: kafa
 * 
 * Created on May 22, 2017, 1:36 AM
 */
#if defined(__QNXNTO__)
#include <sys/neutrino.h>
#include <hw/inout.h>
#endif


#include "thread.h"
#include "lock.h"
#include <iostream>
Thread::Thread () :
thread_{}
{
};
Thread::Thread (Thread &&__t) noexcept
{
  thread_ = std::move (__t.thread_);
}
Thread::~Thread () { }
Thread&
        Thread::operator= (Thread &&__t) noexcept
{
  thread_ = std::move (__t.thread_);
  return *this;

}
void
Thread::swap (Thread& __t) noexcept
{
  std::swap (id_, __t.id_);
}
uint32_t
Thread::hardwareConcurrency () noexcept
{
  return std::thread::hardware_concurrency ();
}
Thread::Id
Thread::getId ()
{
  return id_;
}
void
Thread::detach ()
{
  thread_.detach ();
}
void
Thread::join ()
{
  thread_.join ();
}
bool
Thread::joinable ()
{
  return thread_.joinable ();
}
Thread::NativeHandleType
Thread::native_handle ()
{
  return thread_.native_handle ();
}

// ------------------------------------------------------------------ Runnable -
Runnable::Runnable () { };
Runnable::~Runnable () { };

// ------------------------------------------------------------------ Loopable -
bool
Loopable::isRunningGlobal_ = true;
Loopable::Loopable () :
isRunning_ (true) { };
Loopable::~Loopable () { };
void
Loopable::globalTerminate ()
{
  isRunningGlobal_ = false;
};
bool
Loopable::isRunning ()
{
  return isRunning_ && isRunningGlobal_;
};
void
Loopable::terminate ()
{
  isRunning_ = false;
};
void
Loopable::run ()
{
  while (isRunning ())
  {
    loop ();
  }
};
// ----------------------------------------------------------------- Stoppable -
void
Stoppable::run ()
{
  std::unique_lock<std::mutex> lock (mtx_);
  while (isStopped ())
  {
    convar_.wait (lock);
  }
  lock.unlock ();
  while (isRunning ())
  {
    loop ();
  }
}
void
Stoppable::stop ()
{
  isStopped_ = true;
}
void
Stoppable::conti ()
{
  isStopped_ = false;
  convar_.notify_one ();
}
Stoppable::Stoppable (bool isStopped) :
convar_ ()
, isStopped_ (isStopped) { };
Stoppable::Stoppable () :
convar_ ()
, isStopped_ (false) { };
Stoppable::~Stoppable ()
{
  convar_.~condition_variable ();
};
void
Stoppable::terminate ()
{
  isRunning_ = false;
  conti ();
};
void
Stoppable::loop ()
{
  std::unique_lock<std::mutex> lock (mtx_);
  step ();
  while (isStopped ())
  {
    convar_.wait (lock);
  }
}
bool
Stoppable::isStopped ()
{
  return isStopped_;
};
// -------------------------------------------------------------------- Worker -
Worker::Worker (Runnable &runner) :
runner_ (&runner) { };
void Worker::operator() ()
{
//  if (ThreadCtl (_NTO_TCTL_IO_PRIV, 0) == -1)
//  {
//    std::cout << "Can't get Hardware access, therefore can't do anything."
//            << std::endl;
//  }
  runner_->run ();
};
Worker::~Worker () { };
