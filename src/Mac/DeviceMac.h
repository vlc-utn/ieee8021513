#ifndef DEVICEMAC_H_
#define DEVICEMAC_H_


#include <omnetpp.h>
#include "Mac.h"



using namespace omnetpp;

class DeviceMac : public Mac {

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    cMessage *timerLostSync;


    uint32_t slotsSinceLastSync;
    bool isSynchronized;

    void rxSync(uint8_t *payload, uint16_t length);
    void superframeScheduler(void);

public:


};

#endif /* DEVICEMAC_H_ */
