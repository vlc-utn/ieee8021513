#include "DeviceMac.h"

void DeviceMac::initialize(void) {
    this->timerLostSync = new cMessage("timer_lost_sync");

    this->slotsSinceLastSync = 0;


}

void DeviceMac::handleMessage(cMessage *msg) {

}

void DeviceMac::superframeScheduler(void) {
    if (isSynchronized) {
        currentSlot++;
        if (currentSlot == numSuperframeSlots) {
            currentSlot = 0;
            currentSuperframe++;
            if (currentSuperframe == 0xffff) {
                currentSuperframe = 0;
            }
        }

        slotsSinceLastSync++;
        if (slotsSinceLastSync == 2*aMaxSyncIntervalInSlots) {
            this->isSynchronized = false;
        }

        scheduleAfter(aSuperframeSlotDuration, this->timerSlot);
    }
}


void DeviceMac::rxSync(uint8_t *payload, uint16_t length) {
    this->currentSuperframe = (payload[1] << 8) | (payload[0] << 0);
    this->numSuperframeSlots = (payload[3] << 8) | (payload[2] << 0);
    this->currentSlot = (payload[5] << 8) | (payload[4] << 0);

    this->slotsSinceLastSync = 0;
    this->isSynchronized = true;

    // TODO resyncronize clock with the start of the PPDU preamble.

    cancelEvent(timerSlot);
    scheduleAfter(aSuperframeSlotDuration, timerSlot);
}


