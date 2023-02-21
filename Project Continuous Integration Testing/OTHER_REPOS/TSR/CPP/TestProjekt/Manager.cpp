//
// Created by lennart on 08.12.17.
//

#include <iostream>
#include <cstring>
#include "Manager.h"
#include "Data.h"

#define ZERO 0

Manager::Manager() {
    std::cout << "Mananger erzeugt" << std::endl;
    double d = 0.101;
    int i=d/ZERO;

    int a=1;
    int b=2;
    int c=-1;

    //Fehlerhafter Vergleich
    if(a=b){
        c=3;
    }

    //wirkungslose Vergleich
    if(a==b);
    {
        c=-3;
    }

    //Informationsverlust durch ungewollten cast
    int pi = 3.14; //int pi = {3.14};

    //möglicher buffer overflow
    this->f(30);

    //garantierter Buffer overflow
    const char* name = "Georg Christoph Lichtenberg";
    char buf[10];
    std::strcpy(buf,name);
    //memory leak
    //while(1<2) Data::getMem();
}


Manager::~Manager() {
}

/**
 * gewährleistet Gefahr eines Buffer Overflows
 */
void Manager::f(int a){
    char buf[] = "Buffer-Overflow?";
    char c = buf[a];
}

/**
 * Fwhlerhafter Check auf null
 */
void Manager::test(int *p){
    if(p)
        return;
    int x = p[0];
}

/**
 * Fehlerhafte Tauschaktion
 */
void Manager::tausch(int& min, int& max){
    int hilf;
    if(min>max){
        max=hilf;
        max=min;
        hilf=min;
    }
}

bool Manager::set(std::string str){
    //this->data.setData(str);
    this->data.setData(str);
}


std::string Manager::get(){
    std::string str = this->data.getData();
    std::cout << "data: " << str << std::endl;
    return str;
}
