#ifndef DME_H_
#define DME_H_

#include "../msgs/mac_primitives_m.h"
#include "../msg_kind.h"

#include <omnetpp.h>



using namespace omnetpp;


class Dme : public cSimpleModule {

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

public:
    void md_data_request(uint64_t destinationAddress, uint64_t sourceAddress, uint16_t msduLengthType, uint8_t* msdu, uint8_t priority, bool acknowledged);
    void mlme_associate_request(uint64_t owpanID);
    void mlme_disassociate_request(uint64_t owpanID, uint64_t deviceAddress, DisassociationReason_t reason);
    void mlme_get_request(PibAttribute_t attribute);
    void mlme_set_request(PibAttribute_t attribute, uint64_t attributeValue);
    void mlme_scan_request(uint16_t scanDuration);
    void mlme_start_request(void);
    void mlme_stop_request(uint16_t timeout, bool force);

    void mlme_associate_confirm(cMessage *msg);
    void mlme_disassociate_confirm(cMessage * msg);
    void mlme_get_confirm(cMessage * msg);
    void mlme_set_confirm(cMessage * msg);
    void mlme_scan_confirm(cMessage * msg);
    void mlme_start_confirm(cMessage * msg);
    void mlme_stop_confirm(cMessage * msg);
};

#endif /* DME_H_ */
