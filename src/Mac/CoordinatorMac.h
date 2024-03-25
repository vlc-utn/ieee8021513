#ifndef COORDINATORMAC_H_
#define COORDINATORMAC_H_

#include <omnetpp.h>

using namespace omnetpp;


class CoordinatorMac : public cSimpleModule {

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};

#endif /* COORDINATORMAC_H_ */
