#ifndef GATEMANAGER_H
#define GATEMANAGER_H
#include "Data.h"
#include <iostream>
#include <string>

using namespace std;

class GateManager{

private:
	struct State {//top-level state
        virtual string getName();
		virtual void reportEnterMetalDetection();
        virtual void reportLeavingMetalDetection();
        virtual void reportMintimerToMetalDetectionExpired();
        virtual void reportMaxtimerToMetalDetectionExpired();
        virtual void reportMetalDetectionTimeout();
        virtual void ignoreTiming();
        virtual void rampBlocked();
        virtual void rampFreed();
        virtual void reportRampObstructionCleared();

		Data* data;// pointer to data, which physically resides inside the context class (contextdata)
	} *statePtr;   // a pointer to current state. Used for polymorphism.


	struct Idle : public State {
		virtual string getName();
		virtual void reportEnterMetalDetection();
		virtual void reportMintimerToMetalDetectionExpired();
	};

	struct UntrackedWorkpiece : public State {
        virtual string getName();
        virtual void ignoreTiming();
	};

    struct MissingWorkpiece : public State {
        virtual string getName();
        virtual void ignoreTiming();
	};

	struct Ready : public State {
		virtual string getName();
		virtual void reportEnterMetalDetection();
		virtual void reportMaxtimerToMetalDetectionExpired();
	};

	struct Processing : public State {
		virtual string getName();
        virtual void reportMetalDetectionTimeout();
	};

    struct Done : public State {
        virtual string getName();
		virtual void reportLeavingMetalDetection();
	};

	struct Ejecting : public State {
        virtual string getName();
        virtual void rampBlocked();
	};

	struct RampError : public State {
        virtual string getName();
		virtual void rampFreed();
		virtual void ignoreTiming();
		virtual void reportRampObstructionCleared();
	};

	struct Achnoledged : public State {
        virtual string getName();
        virtual void rampFreed();
        virtual void reportRampObstructionCleared();
	};

	Idle stateMember;//The memory for the state is part of context object
	Data *contextdata;  //Data is also kept inside the context object

public:// assigning start state
    GateManager();
    GateManager(Data *data);
    //events handled by FSM
    virtual string getName();
    virtual void reportEnterMetalDetection();
    virtual void reportLeavingMetalDetection();
    virtual void reportMintimerToMetalDetectionExpired();       //TO_METAL_DETECTION_MIN,
    virtual void reportMaxtimerToMetalDetectionExpired();       //TO_METAL_DETECTION_MAX,
    virtual void reportMetalDetectionTimeout();                 //METAL_DETECTION_TIMER
    virtual void ignoreTiming();
    //events handled independently
    void reportMetalDetected();
    void reportGateTimeout();                           //GATE_TIMER
    void reportRampTimeout();
    void rampBlocked();                                 //RAMP_BLOCKED
    void rampFreed();                                   //RAMP_FREED
    void reportRampObstructionCleared();
};
#endif // GATEMANAGER_H
