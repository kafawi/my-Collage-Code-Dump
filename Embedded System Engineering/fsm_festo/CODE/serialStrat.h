/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serialStrat.h
 * Author: kafa
 *
 * Created on June 21, 2017, 11:09 AM
 */

#ifndef SERIALSTRAT_H
#define SERIALSTRAT_H

#include <stdint.h>
#include <unistd.h>

#define DEVOUT "/dev/ser1"
#define DEVIN  "/dev/ser2"
#define ACKTIME      10   // 10 = one second bcaouse time = 0.1 s
#define FOREVERTIME  0
#define PKG_ACK     22


class SerialStrat
{
 public:
  SerialStrat();
  virtual ~SerialStrat();
  void config(int &fdesc, const char *dev);
  int sendPkg(int const &fdesc, void *pkg, size_t size);
  int recvPkg(int const &fdesc, void *pkg, size_t size, int maxWaitTime);
 private:
};

#endif /* SERIALSTRAT_H */

