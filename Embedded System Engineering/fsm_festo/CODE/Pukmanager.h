/**
 * @brief  puk manager
 * @author Lennart Hartmann, Nils Eggebrecht
 * @version 17.06.2017
 */
#ifndef PUKMANAGER_H
#define PUKMANAGER_H
class Data;

//#include "serialController.h"
#include "Puk.h"
#include <list>
#include "timerController.h"

class Pukmanager
{
 public:
  Pukmanager(Data *data);
  virtual ~Pukmanager();
  void showItems();
  /**
   * add new Puk to List, since puk detected in Entyr
   */
  void trackNewPuk();
  /**
   * remove puk from list / delete, since no longer needed
   */
  void transferPuk();
  /**
   * add specified puk
   */
  void receivePuk(Puk* incomingPuk);
  void receivePuk();
  bool isEmpty();
  Puk* getPukInEntry();
  Puk* getPukInProfileDetection();
  Puk* getPukInGate();
  Puk* getPukInExit();
  void insertPukInProfileDetection();
  void insertPukInGate();
  void insertPukInExit();
  void removePukInProfileDetection();
  void removePukInGate();
  void removePukInExit();
  void refreshNextPukInProfileDetection();
  void refreshNextPukInGate();
  void refreshNextPukInExit();
  void deletePukInGate();
  void deletePukInExit();

 protected:

 private:
  Data *data;
  uint minPuks;
  uint length;
  std::list<Puk*> entryList_;
  std::list<Puk*> middleList_;
  std::list<Puk*> exitList_;
  bool isAlreadyInMiddle_;
  Puk * getPuk();
  void printPuk(Puk* puk);
};

#endif // PUKMANAGER_H
