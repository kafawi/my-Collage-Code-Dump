//
// Created by lennart on 08.12.17.
//
#include <iostream>
#include "Data.h"
#include <cstdlib>
#include <cstring>


Data::Data(){
    this->str="leer";
}

Data::~Data(){
}

bool Data::setData(std::string str){
    this->str=str;
    this->changed=3;
    return true;
}

std::string Data::getData(){
    return this->str;
}

Data* Data::getMem(){
    return (Data*) malloc(sizeof(Data));
}
