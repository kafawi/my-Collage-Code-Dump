#include <iostream>
#include "Data.h"
#include "InputMultiplexer.h"

using namespace std;

int serialtest(){
    Data *data = new Data(false);
    cout << "InputMultiplexer v2.1\n" << endl;
    // Data *data = new Data(true);
    InputMultiplexer *im = new InputMultiplexer(data);
    cout << "/////////////// instanciation done /////////////////" << endl;



//////////////////////////////////////////////////////////
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);


//    im->processCode(ENTRY_OCCUPIED);
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);
//    im->processCode(ENTRY_CLEAR);
//    im->processCode(REACHED_EXIT);
//    im->processCode(LEAVING_EXIT);

//
//    im->processCode(E_STOP_PRESSED);
//    im->processCode(ERROR_CLEARED_ACK);
//    im->processCode(ERROR_CLEARED_NO_ACK);
//    im->processCode(ERROR_PENDING_ACK);
//    im->processCode(ERROR_PENDING_NO_ACK);
/////////////////////////////////////////////////////////////
//
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(START_BTN);
//    im->processCode(E_STOP_PRESSED);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(E_STOP_RELEASED);
//    im->processCode(STOP_BTN);
//    im->processCode(RESET_BTN);
//
//    im->processCode(STOP_BTN);

    cout << "testing entry\n" << endl;
    im->processCode(NEWPUK);
    im->processCode(LEAVING_ENTRY);
//    im->processCode(START_BTN);
    im->processCode(NEWPUK);
    im->processCode(LEAVING_ENTRY);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(NEWPUK);
//    im->processCode(LEAVING_ENTRY);
//    im->processCode(LEAVING_ENTRY);

    cout << "\ntesting unknown profile" << endl;
    im->processCode(ENTER_PROFILE_DETECTION);
    im->processCode(LEAVING_PROFILE_DETECTION);
    cout << "\testing valid profile" << endl;
    im->processCode(ENTER_PROFILE_DETECTION);
    im->processCode(REGULAR);
    im->processCode(LEAVING_PROFILE_DETECTION);

    cout << "\ntesting puk without metal core" << endl;
    im->processCode(ENTER_METAL_DETECTION);
    im->processCode(LEAVING_METAL_DETECTION);
    cout << "\ntesting puk with metal core" << endl;
    im->processCode(ENTER_METAL_DETECTION);
    im->processCode(METAL_DETECTED);
    im->processCode(LEAVING_METAL_DETECTION);

    cout << "\ntesting outlet" << endl;
    im->processCode(REACHED_EXIT);
    im->processCode(LEAVING_EXIT);
    im->processCode(REACHED_EXIT);
    im->processCode(LEAVING_EXIT);
    //////////////////////////////////////
    cout << "\ntesting RECEIVED_PUK" << endl;
    im->processCode(RECEIVED_PUK);

}
