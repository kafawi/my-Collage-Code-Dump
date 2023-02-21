#include "HDI_Manager.h"
#include <iostream>

using namespace std;
/**
 * Prints the Puk Data and deletes the Puk after printing.
 */
void HDI_Manager::printPukdata(Puk* puk) {
//	int pukID = puk->ID;
//	uint16_t height1 = puk->height1;
//	uint16_t height2 = puk->height2;
//
//	if (puk->unknownType) {
//		cout << "==============PUK Data==============\n" << "Object with ID: "
//				<< pukID << " has an unknown Type!" << endl << "Puk hight1: "
//				<< height1 << endl << "Puk hight2: " << height2 << endl;
//	} else if (puk->containsMetal) {
//		cout << "==============PUK Data==============\n" << "Puk ID: " << pukID
//				<< endl << "Puk contains metal." << endl << "Puk hight1: "
//				<< height1 << endl << "Puk hight2: " << height2 << endl;
//	} else {
//		cout << "==============PUK Data==============\n" << "Puk ID: " << pukID
//				<< endl << "Puk " << endl << "Puk hight1: "
//				<< height1 << endl << "Puk hight2: " << height2 << endl;
//	}

	cout << "==============PUK Data==============" << endl << "Puk ID: "
			<< puk->ID << endl;

	if (puk->getType() == TYPE_DRILLED) {
		cout << "Puk is drilled and consists of plastic." << endl;

	} else if (puk->getType() == TYPE_DRILLED_METAL) {
		cout << "Puk is drilled and contains metal." << endl;
	}

	cout << "Puk hight1: " << puk->height1 << endl << "Puk hight2: "
			<< puk->height2 << endl;

	//delete puk; // da hängt der sich auf
	delete puk;
	std::cout << "PENIUS " << std::endl;
	//free(puk);
}

void HDI_Manager::printError(ErrorType errtype) {
	std::cout << "ERROR: " << errMessages[errtype] << std::endl;
}

HDI_Manager::HDI_Manager() {
	std::cout << "----------------- new HDI_Mananger() ----------------------"
			<< std::endl;
	errMessages[MISSING_WORKPIECE_IN_PROFILE_DETECTION] =
			"missing workpiece in profile detection";
	errMessages[UNEXPECTED_OBJECT_IN_PROFILE_DETECTION] =
			"unexpected object in profile detection";
	errMessages[MISSING_WORKPIECE_IN_METAL_DETECTION] =
			"missing workpiece in metal detection";
	errMessages[UNEXPECTED_OBJECT_IN_METAL_DETECTION] =
			"unexpected object in metal detection";
	errMessages[MISSING_WORKPIECE_IN_OUTLET] = "missing workpiece in outlet";
	errMessages[UNEXPECTED_OBJECT_IN_OUTLET] = "unexpected object in outlet";
	errMessages[BOTH_SLIDES_FULL] = "both slides full";
}

HDI_Manager::~HDI_Manager() {
}
