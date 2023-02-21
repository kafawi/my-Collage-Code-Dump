#include <cstdlib>
#include "Manager.h"


int main() {
    std::cout << "start" << std::endl;
    Manager man;
    man.set("hi");
    short* sPtr = (short*)malloc(sizeof(short));
    int* iPtr = (int*)sPtr;
    int i= *iPtr;
    std::cout << "val:" << i << std::endl;
    return EXIT_SUCCESS;
}
