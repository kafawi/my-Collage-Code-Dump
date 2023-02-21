/**
 * @brief keeps track the desired puk sequence
 * @author Lennart Hartmann, Nils Eggebrecht
 * @version 27.06.2017
 */
#include "PukSequenceTracker.h"
#include <iostream>
#include <iostream>
//#define SEQ_SIZE 3
#define SEQ_SIZE 1
#include "Puk.h"
using namespace std;
PukSequenceTracker::PukSequenceTracker(Data *data) :
    data(data), index(0)
{
    seq[0] = TYPE_DRILLED;
    seq[1] = TYPE_DRILLED;
    seq[2] = TYPE_DRILLED_METAL;
}

PukSequenceTracker::~PukSequenceTracker()
{
}

bool PukSequenceTracker::getExpected(Puk *processedPuk)
{

    //if band2
    if (data->isReceivingEnd)
    {
        //if sequence is okay
        if (processedPuk->getType() == seq[index])
        {
            cout << "sequence ok => update sequence" << endl;
            index = (index + 1) % SEQ_SIZE;
            return true;
        }
        else
        {
            cout << "wrong sequence" << endl;
            //if ramp2 obstructed
            if(data->rampObstructed == true)
            {
                cout << "Ramp is obstructed" << endl;
            }
            return false;
        }
    }
    //if band1
    else
    {
        // if ramp1 obstructed and rump2 is NOT obstructed
        if (data->rampObstructed == true && data->otherRampObstructed == false)
        {
            cout << "Puk is on the way to band2, because ramp1 is blocked"
                 << endl;
            return true;

        }
        // if ramp2 is obstructed
        else if (data->otherRampObstructed == true)
        {
            cout << "Ramp2 is obstructed, sort out TYPE_2 and TYPE_4 at Band1 " << endl;
            //if type is drilled or drilled metal sort out at band 2
            if(processedPuk->getType() == TYPE_DRILLED || processedPuk->getType() == TYPE_DRILLED_METAL)
            {
                cout << "Puk is on the way to band2" << endl;
                return true;
            }

            //else sort out at band1
            else
            {
                cout << "sort out the puk at band1" << endl;
                return false;
            }
        }
        // if both ramps are NOT obstructed
        //sort out drilled, drilled metal and type 2 / 4 at band2
        else if (processedPuk->getType() == TYPE_DRILLED
                 || processedPuk->getType() == TYPE_DRILLED_METAL
                 || processedPuk->getType() == TYPE_2
                 || processedPuk->getType() == TYPE_4)
        {
            cout << "Puk is on the way to band2" << endl;
            return true;
        }
        // sort out other puks at band1
        else
        {
            cout << "sort out the puk at band1" << endl;
            return false;
        }
    }
}
