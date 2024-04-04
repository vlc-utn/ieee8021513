#ifndef COORDINATORMAC_H_
#define COORDINATORMAC_H_

#include "DeviceMac.h"

#include <omnetpp.h>

#define BROADCAST_ADDRESS 0xffffffffffff

using namespace omnetpp;


class CoordinatorMac : public DeviceMac {

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;


    virtual void processMsgFromHigherLayer(cMessage *packet);
    virtual void processMsgFromLowerLayer(cMessage *packet);
    virtual void processSelfMsg(cMessage *packet);


    void superframeScheduler(void);

    cMessage* timerSlot;
    cMessage* timerSuperframe;

    /*** Determined by the OWPAN coordinator, arbitrary value ****/
    uint16_t numSuperframeSlots;    // Amount of slots in a superframe
    uint32_t syncInterval;          // Amount of slots in between sync elements, including the sync element itself.


    /*****************************************************/
    /*** Internal variables, required by the standard ****/
    /*****************************************************/

    /****** Used by the superframe scheduler  *********/
    uint16_t currentSlot;       // Current slot [0; numSuperframeSlots]
    uint16_t currentSuperframe; // Current superframe [0; 0xffff]
    uint8_t* slotState;


    uint32_t syncCounter;       // This value counts from "(syncInterval / aSuperframeSlotDuration)" to "0". When it reaches 0, a sync element is to be transmitted.


    /***********Used for transmision and reception********/
    uint16_t sequenceNumber;

    void fsmSuperframe(void);

    void transmitElement(MacFrameType_t type, bool fragmentedFrame,
        bool relayedFrame, uint64_t receiverAddress, ElementID_t payloadElementID,
        bool ackRequest, uint8_t fragmentNumber, uint8_t lastFragment,
        uint64_t relayAddress, uint8_t* payload, uint16_t payloadSize);


    void txNull(uint64_t receiverAddress, bool ackRequest);
    void txSync(void);

public:


};

#endif /* COORDINATORMAC_H_ */
