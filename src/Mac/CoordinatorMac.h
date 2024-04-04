#ifndef COORDINATORMAC_H_
#define COORDINATORMAC_H_

#include "DeviceMac.h"

#include <omnetpp.h>

using namespace omnetpp;


class CoordinatorMac : public DeviceMac {

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    virtual void processMsgFromHigherLayer(cMessage *packet);
    virtual void processMsgFromLowerLayer(cMessage *packet);
    virtual void processSelfMsg(cMessage *packet);

    cMessage* timerSlot;
    cMessage* timerSuperframe;

    /*** Determined by the OWPAN coordinator, arbitrary value ****/
    uint16_t numSuperframeSlots;    // Amount of slots in a superframe
    uint32_t syncInterval;          // Amount of slots in between sync elements, including the sync element itself.


    /*** Internal variables, required by the standard ****/
    uint16_t currentSlot;       // Current slot [0; numSuperframeSlots]
    uint16_t currentSuperframe; // Current superframe [0; 0xffff]
    uint32_t syncCounter;       // This value counts from "(syncInterval / aSuperframeSlotDuration)" to "0". When it reaches 0, a sync element is to be transmitted.

    void fsmSuperframe(void);

public:


};

#endif /* COORDINATORMAC_H_ */
