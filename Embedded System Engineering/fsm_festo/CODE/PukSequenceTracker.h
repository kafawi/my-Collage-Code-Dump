/**
 * @brief keeps track the desired puk sequence
 * @author Lennart Hartmann
 * @version 31.05.2017
 */
#ifndef PUKSEQUENCETRACKER_H
#define PUKSEQUENCETRACKER_H
#include "Data.h"

class PukSequenceTracker {
public:
	PukSequenceTracker(Data *data);
	virtual ~PukSequenceTracker();

	/**
	 * gives whether the current is supposed to pass the gate
	 * @return metal core expected
	 */
	bool getExpected(Puk *processedPuk);
protected:
private:
	Data *data;
	int index;
	int *seq = new int[3];
};

#endif // PUKSEQUENCETRACKER_H
