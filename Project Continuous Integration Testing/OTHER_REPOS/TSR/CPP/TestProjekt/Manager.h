//
// Created by lennart on 08.12.17.
//


#ifndef TESSA_MANAGER_H
#define TESSA_MANAGER_H
#include <iostream>
#include "Data.h"

class Manager {
public:
    Manager();
    virtual ~Manager();
    bool set(std::string);
    std::string get();
    Data* getMem();
    void f(int a);
    void test(int *p);
    void tausch(int& min, int& max);
private: Data data;
};


#endif //TESSA_MANAGER_H
