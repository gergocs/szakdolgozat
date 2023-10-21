//
// Created by csger on 2023-10-17.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>

class Controller {
public:
    virtual uint8_t calculate(uint8_t input) = 0;

    virtual void setTarget(uint8_t target) = 0;


protected:
    uint8_t target = 0;
     uint8_t current = 0;
};


#endif //CONTROLLER_H
