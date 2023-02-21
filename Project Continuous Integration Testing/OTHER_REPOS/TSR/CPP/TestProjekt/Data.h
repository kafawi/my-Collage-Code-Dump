//
// Created by lennart on 08.12.17.
//

#ifndef TESSA_DATA_H
#define TESSA_DATA_H
//#include <cstring>


class Data {
public:
    Data();
    virtual ~Data();
    bool setData(std::string str);
    std::string getData();
    static Data* getMem();
private:
    std::string str;
    bool changed;
};


#endif //TESSA_DATA_H
