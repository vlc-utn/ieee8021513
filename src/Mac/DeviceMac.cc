#include "DeviceMac.h"

void DeviceMac::initialize(void) {
    this->timerLostSync = new cMessage("timer_lost_sync");
}


