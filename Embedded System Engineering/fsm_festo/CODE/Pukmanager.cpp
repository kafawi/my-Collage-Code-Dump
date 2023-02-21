/**
 * @brief puk manager
 * @author Nils Eggebrecht, Lennart Hartmann
 */
#include "Data.h"
#include "Pukmanager.h"
#include "HDI_Manager.h"
#include "serialController.h"
#include <iostream>
//#include "ButtonLightController.h"

using namespace std;
Pukmanager::Pukmanager (Data *data)
: data (data)
, minPuks (0)
, length (0)
, entryList_ ()
, middleList_ ()
, exitList_ ()
, isAlreadyInMiddle_ (false)
{
  if (data->isReceivingEnd)
  {
    cout
            << "------------------- new Pukmanager() - receiver ----------------------------"
            << endl;
  }
  else
  {
    cout
            << "------------------- new Pukmanager() - provider ----------------------------"
            << endl;
  }
}
Pukmanager::~Pukmanager () { }
list<Puk*> puksInEntry;
list<Puk*>::iterator entryIter; // Iterator definieren
list<Puk*> puksInProfileDetection;
list<Puk*>::iterator profileDetectionIter; // Iterator definieren
list<Puk*> puksInGate;
list<Puk*>::iterator gateIter; // Iterator definieren
list<Puk*> puksInExit;
list<Puk*>::iterator exitIter; // Iterator definieren
void
Pukmanager::printPuk (Puk* puk)
{
  string prof;
  switch (puk->profile)
  {
    case(FLAT):
      prof = "FLAT";
      break;
    case(DRILLED):
      prof = "DRILLED";
      break;
    case(BITCODE_0):
      prof = "BC0";
      break;
    case(BITCODE_1):
      prof = "BC1";
      break;
    case(BITCODE_2):
      prof = "BC2";
      break;
    case(BITCODE_3):
      prof = "BC3";
      break;
    case(BITCODE_4):
      prof = "BC4";
      break;
    case(BITCODE_5):
      prof = "BC5";
      break;
    case(UNKNOWN_PROFILE):
      prof = "UNKNOWN";
      break;
  }
  cout << "    id:" << puk->ID
          << " metal:" << puk->containsMetal
          << " h1-2:" << puk->height1 << "-" << puk->height1
          << " profile:" << prof
          << " eject:" << puk->sceduledForEjection
          << " unknown:" << puk->unknownType
          << endl;
}
void
Pukmanager::showItems ()
{
  list<Puk*>::iterator it;
  cout << "new Puklists" << endl;
  cout << "  entryList_:" << endl;
  for (it = entryList_.begin (); it != entryList_.end (); it++)
  {
    printPuk (*it);
  }
  cout << "  middleList_:" << endl;
  for (it = middleList_.begin (); it != middleList_.end (); it++)
  {
    printPuk (*it);
  }
  cout << "  exitList_:" << endl;
  for (it = exitList_.begin (); it != exitList_.end (); it++)
  {
    printPuk (*it);
  }
  /*
  cout << "old Puklists" << endl;
  cout << "puksInEntry: " << endl;
  for (entryIter = puksInEntry.begin (); entryIter != puksInEntry.end ();
          ++entryIter)
  {
    printPuk(*entryIter);
    //    puksInEntry.front()->ID
  }
  cout << "puksInProfileDetection: " << endl;
  for (profileDetectionIter = puksInProfileDetection.begin ();
          profileDetectionIter != puksInProfileDetection.end ();
          ++profileDetectionIter)
  {
    printPuk(*profileDetectionIter);
  }
  cout << "puksInGate: " << endl;
  for (gateIter = puksInGate.begin (); gateIter != puksInGate.end ();
          ++gateIter)
  {
    printPuk(*gateIter);
  }
  cout << "puksInExit: " << endl;
  for (exitIter = puksInExit.begin (); exitIter != puksInExit.end ();
          ++exitIter)
  {
    printPuk(*exitIter);
  }
   */
}
Puk *
Pukmanager::getPuk ()
{
  Timer *min = data->timerCtrl->getTimer ();
  Timer *max = data->timerCtrl->getTimer ();
  Puk *puk = new Puk (min, max);
  return puk;
}
// INSERT NEWPUK
void
Pukmanager::trackNewPuk ()
{
  Puk *puk = getPuk ();
  entryList_.push_front (puk);
  //puksInEntry.push_front (puk);
  data->pukInEntry = getPukInEntry (); // waum?
  length++;
  cout << "Adding new Puk in puksInEntry" << endl;
  cout << length << " puks remaining" << endl;
}

// EXTRA LADIDA
void
Pukmanager::insertPukInProfileDetection ()
{
  Puk *puk = getPuk ();
  middleList_.push_front (puk);
  //puksInProfileDetection.push_front (puk);
  data->pukInProfileDetection = getPukInProfileDetection ();
  length++;
  cout << "Adding new Puk in puksInProfileDetection" << endl;
  cout << length << " puks remaining" << endl;
}
void
Pukmanager::insertPukInGate ()
{
  Puk *puk = getPuk ();
  exitList_.push_front (puk);
  //puksInGate.push_front (puk);
  data->pukInMetalDetection = getPukInGate ();
  length++;
  cout << "Adding new Puk in puksInGate" << endl;
  cout << length << " puks remaining" << endl;
}
void
Pukmanager::insertPukInExit ()
{
  Puk *puk = getPuk ();
  exitList_.push_back (puk);
  //puksInExit.push_front (puk);
  data->pukInExit = getPukInExit ();
  length++;
  cout << "Adding new Puk in puksInExit" << endl;
  cout << length << " puks remaining" << endl;
}
/**
 * removes the tail Puk* in puksInEntry.
 *
 */
void
Pukmanager::removePukInProfileDetection ()
{
  // referesch is excecuted when lightbarriers ar blocked
  // this will happend befor, so wie need to remove the 
  // puk at the end / back of the preveous list
  if (entryList_.empty ())
  {
    cout << "removePukInProfileDetection() failed: There is no Puk in Exit" << endl;
  }
  else
  {
    Puk * puk = entryList_.back ();
    if (puk != nullptr)
    {
      delete (puk);
    }
    length--;
    entryList_.pop_back ();
  }
  /*
  if (puksInEntry.size () <= minPuks)
  {
    cout << "removePukInProfileDetection() failed: " << puksInEntry.size ()
            << " Puks in puksInEntry" << endl;
  }
  else
  {
    delete puksInEntry.back ();
    puksInEntry.pop_back ();
    length--;
    cout << "pukBeforeProfileDetection removed" << endl;
    cout << length << " puks remaining" << endl;
  }
   */
}
void
Pukmanager::removePukInGate ()
{ // referesch is excecuted when lightbarriers ar blocked
  // this will happend befor, so wie need to remove the 
  // puk at the end / back of the preveous list

  if (middleList_.empty ())
  {
    cout << "removePukInGate() failed: There is no Puk in Exit" << endl;
  }
  else
  {
    Puk * puk = middleList_.back ();
    if (puk != nullptr)
    {
      delete (puk);
    }
    length--;
    middleList_.pop_back ();
  }
  /*
  if (puksInProfileDetection.size () <= minPuks)
  {
    cout << "removePukInGate() failed: " << puksInProfileDetection.size ()
            << " Puks in puksInProfileDetection" << endl;
  }
  else
  {
    delete puksInProfileDetection.back ();
    puksInProfileDetection.pop_back ();
    length--;
    cout << "pukBeforeGate removed" << endl;
    cout << length << " puks remaining" << endl;
  }
   */
}
void
Pukmanager::removePukInExit ()
{
  // referesch is excecuted when lightbarriers ar blocked
  // this will happend befor, so wie need to remove the 
  // puk at the end / back of the preveous list but that is
  // here not nessessary, because Exit puk is back of list;

  if (exitList_.empty ())
  {
    cout << "removePukInExit() failed: There is no Puk in Exit" << endl;
  }
  else
  {
    Puk * puk = getPukInExit ();
    if (puk != nullptr)
    {
      delete (puk);
    }
    length--;
    exitList_.pop_back ();
    // is this nessessary, but better it is
    data->pukInExit = getPukInExit ();
  }
  /*
  if (puksInGate.size () <= minPuks)
  {
    cout << "removePukInExit() failed: " << puksInGate.size ()
            << " Puks in puksInGate" << endl;
  }
  else
  {
    delete puksInGate.back ();
    puksInGate.pop_back ();
    length--;
    cout << "pukBeforeExit removed" << endl;
    cout << length << " puks remaining" << endl;
  }
   */
}
void
Pukmanager::refreshNextPukInProfileDetection ()
{
  Puk *puk = nullptr;
  if (entryList_.empty ())
  {
    cout << "Warning: no Puk to refresh into ProfileDetection -> nullptr" << endl;
  }
  else
  {
    puk = entryList_.back ();
    middleList_.push_front (puk);
    entryList_.pop_back ();
  }
  //data->pukInMetalDetection = puk;
  data->pukInMetalDetection = getPukInProfileDetection ();
  /*
  if (puksInEntry.size () <= minPuks)
  {
    cout << "refreshNextPukInProfileDetection() failed: "
            << puksInEntry.size () << " Puks in Entry" << endl;
    data->pukInProfileDetection = nullptr;
  }
  else
  {
    list<Puk*>::iterator it = puksInEntry.begin ();
    for (unsigned int i = 1; i < puksInEntry.size (); i++)
    {
      it++;
    }
    puksInProfileDetection.splice (puksInProfileDetection.begin (),
                                   puksInEntry, it);
    data->pukInProfileDetection = getPukInProfileDetection ();
    cout << "fetched next Puk for profile Detection" << endl;
  }
   */
}
void
Pukmanager::refreshNextPukInGate ()
{
  Puk *puk = nullptr;
  if (middleList_.empty ())
  {
    cout << "Warning: no Puk to refresh into Gate -> nullptr" << endl;
  }
  else
  {
    puk = middleList_.back ();
    exitList_.push_front (puk);
    middleList_.pop_back ();
  }
  //data->pukInMetalDetection = puk;
  data->pukInMetalDetection = getPukInGate ();
  /*
  if (puksInProfileDetection.size () <= minPuks)
  {
    //        cout << "refreshNextPukInGate() failed: " << puksInProfileDetection.size() << " Puks in ProfileDetection" << endl;
    data->pukInMetalDetection = nullptr;
  }
  else
  {
    list<Puk*>::iterator it = puksInProfileDetection.begin ();
    for (unsigned int i = 1; i < puksInProfileDetection.size (); i++)
    {
      it++;
    }
    puksInGate.splice (puksInGate.begin (), puksInProfileDetection, it);
    data->pukInMetalDetection = getPukInGate ();
    cout << "fetched next Puk for metal detection/sorting" << endl;
  }
   */
}
void
Pukmanager::refreshNextPukInExit ()
{
  Puk *puk = getPukInExit ();
  if (puk == nullptr)
  {
    cout << "refreshNextPukInExit() failed: No Puk in ExitLine" << endl;
  }
  data->pukInExit = puk;
}
bool
Pukmanager::isEmpty ()
{
  if (length > 0)
    return false;
  return true;
}
Puk*
Pukmanager::getPukInEntry ()
{
  Puk *puk;
  if (entryList_.empty ())
  {
    cout << "WARNING: NULLPTR: getPukInEntry() failed: No Puks in Entry" << endl;
    puk = nullptr;
  }
  else
  {
    puk = entryList_.front ();
  }
  data->pukInEntry = puk;
  return puk;
  /*
  if (puksInEntry.size () <= minPuks)
  {
    cout << "getPukInEntry() failed: " << puksInEntry.size ()
            << " Puks in Entry" << endl;
    return nullptr;

  }
  else
  {
    cout << "pukInEntry= " << puksInEntry.front ()->ID << endl;
    return (Puk*)puksInEntry.front ();
  }
   */
}
Puk*
Pukmanager::getPukInProfileDetection ()
{
  Puk *puk;
  if (middleList_.empty ())
  {
    cout << "WARNING: NULLPTR: getPukInProfileDetection() failed: No Puks in Middle" << endl;
    puk = nullptr;
  }
  else
  {
    puk = middleList_.front ();
  }
  data->pukInProfileDetection = puk;
  return puk;

  /*
  if (puksInProfileDetection.size () <= minPuks)
  {
    cout << "getPukInProfileDetection() failed: "
            << puksInProfileDetection.size () << " Puks in ProfileDetection"
            << endl;
    return nullptr;
  }
  else
  {
    cout << "pukInProfileDetection= " << puksInProfileDetection.front ()->ID
            << endl;
    return (Puk*)puksInProfileDetection.front ();
  }
   */
}
Puk*
Pukmanager::getPukInGate ()
{
  Puk *puk;
  if (exitList_.empty ())
  {
    cout << "WARNING: NULLPTR: getPukInGate() failed: No Puks in Middle" << endl;
    puk = nullptr;
  }
  else
  {
    puk = exitList_.front ();
  }
  data->pukInMetalDetection = puk;
  return puk;
  /*
  if (puksInGate.size () <= minPuks)
  {
    cout << "getPukInGate() failed: " << puksInGate.size ()
            << " Puks in Gate" << endl;
    return nullptr;
  }
  else
  {
    cout << "pukInGate= " << puksInGate.front ()->ID << endl;
    return (Puk*)puksInGate.front ();
  }
   */
}
Puk*
Pukmanager::getPukInExit ()
{
  Puk *puk;
  if (exitList_.empty ())
  {
    cout << "WARNING: NULLPTR: getPukInExit() failed: No Puks in Middle" << endl;
    puk = nullptr;
  }
  else
  {
    puk = exitList_.back ();
  }
  data->pukInExit = puk;
  return puk;
}
void
Pukmanager::transferPuk ()
{
  Puk * puk = getPukInExit ();
  if (puk != nullptr)
  {
    if (data->isReceivingEnd)
    {
      // wenn doch beide ausgeben sollen muss noch implementiert werden
      //data->serialMsgMan->transferSuccessPuk (data->pukInExit);
      data->hdiMngr->printPukdata (data->pukInExit);
    }
    else
    {
      data->serialMsgMan->transferPuk (data->pukInExit);
    }
    deletePukInExit ();
   // length--;
  }
  else
  {
    cout << "transferPuk() failed: transferPuk is nullptr" << endl;
  }
}
void
Pukmanager::receivePuk (Puk *incomingPuk)
{
  if (incomingPuk != nullptr)
  {
    entryList_.push_front (incomingPuk);
    length++;
    data->pukInEntry = getPukInEntry ();
  }
  else
  {
    cout << "receivePuk failed: incomingPuk is nullptr. " << endl;
  }
  /*
  puksInEntry.push_front(incomingPuk);
  //puksInEntry.push_front (data->serialMsgMan->getReceivedPuk ());
  length++;
  data->pukInEntry = getPukInEntry ();
  cout << "receive Puk in puksInEntry" << endl;
  cout << length << " puks remaining" << endl;
   */
}
void
Pukmanager::receivePuk ()
{
  std::cout << "Pukmanager::receivePuk " << endl;
  Puk * incomingPuk = data->serialMsgMan->getReceivedPuk ();
  if (incomingPuk != nullptr)
  {
    entryList_.push_front (incomingPuk);
    length++;
    data->pukInEntry = getPukInEntry ();
  }
  else
  {
    cout << "receivePuk failed: receivedPuk in serialCtrl is nullptr. " << endl;
  }
  /*
  puksInEntry.push_front (data->serialMsgMan->getReceivedPuk ());
  length++;
  data->pukInEntry = getPukInEntry ();
  cout << "receive Puk in puksInEntry" << endl;
  cout << length << " puks remaining" << endl;
   */
}
void
Pukmanager::deletePukInGate ()
{
  Puk *puk = getPukInGate ();
  if (puk != nullptr)
  {
    delete(puk);
    exitList_.pop_front ();
    length--;
    if (!exitList_.empty ())
    {
      data->pukInExit = getPukInGate ();
    }
    else
    {
      data->pukInExit = nullptr;
    }
  }
  else
  {
    cout << "deletePukInGate() failed because of nullptr" << endl;
  }
  /*
  if (puksInGate.size () <= minPuks)
  {
    cout << "deletePukInGate() failed: " << puksInGate.size ()
            << " Puks in puksInGate" << endl;
  }
  else
  {
    delete puksInGate.front ();
    puksInGate.pop_front ();
    data->pukInMetalDetection = getPukInGate ();
    length--;
    
    cout << "pukInExit deleted" << endl;
    cout << length << " puks remaining" << endl;
   
  }
   */
}
void
Pukmanager::deletePukInExit ()
{
  Puk *puk = getPukInExit ();
  if (puk != nullptr)
  {
	if (!data->isReceivingEnd) delete (puk);
    exitList_.pop_back ();
    length--;
    if (!exitList_.empty ())
    {
      data->pukInExit = getPukInExit ();
    }
    else
    {
      data->pukInExit = nullptr;
    }
  }
  else
  {
    cout << "deletePukInExit() failed because of nullptr" << endl;
  }
  /*
  if (puksInExit.size () <= minPuks)
  {
    cout << "deletePukInExit() failed: " << puksInExit.size ()
            << " Puks in puksInExit" << endl;
  }
  else
  {
    //delete puksInExit.front();
    puksInExit.pop_front ();
    data->pukInExit = getPukInExit ();
    length--;
    cout << "pukInExit deleted" << endl;
    cout << length << " puks remaining" << endl;
  }
   */
}

/**
 Puk *SerialController::getReceivedPuk ()
 {
 Puk *puk = nullptr;
 puk = receivedPuk_.front ();
 receivedPuk_.pop ();
 return puk;
 }
 */
