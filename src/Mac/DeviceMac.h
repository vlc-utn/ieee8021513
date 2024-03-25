#ifndef DEVICEMAC_H_
#define DEVICEMAC_H_

#include "../msgs/mac_primitives_m.h"
#include "../msg_kind.h"
#include <omnetpp.h>



using namespace omnetpp;

class DeviceMac : public cSimpleModule {

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

public:
    static const uint8_t aMaxAnnouncementInterval = 1; // [seconds]
    static const uint8_t aMaxSyncInterval = 1; // [seconds]
    static const uint8_t aSuperframeSlotDuration = 1; // [us]
    static const uint32_t aMacSuperframeLookahead = 8192; // [superframes]
    static const uint8_t aInitialRtsCw = 1;
    static const uint32_t aClockAccuracy = 20; // ppm
    static const uint8_t aMinFragmentSize = 64;
    static const uint16_t aAckWindow = 1024;

    uint64_t macMacAddress;
    uint8_t macOwpanName[32];
    uint64_t macOwpanID;
    uint16_t macAssociationTimeout;
    uint8_t macAssociationMaxRetries;
    uint16_t macAssociationIdentifier;
    uint16_t macDeviceTimeout;

    uint8_t macQueueReportTimeout;
    uint8_t macMaxRtsCw;
    uint32_t macRetransmitTimeout;
    uint8_t macMaxFrameRetries;
    uint16_t macMaxReassemblyTimeout;

    PhyType_t phyImplementedPhy;

    bool capExplicitMimoEstimation;
    bool capFullDuplex;
    bool capBlockAcknowledgement;
    bool capInterferenceDetection;
    bool capMcsrequest;
    bool capRelayedDevice;
    bool capRelayDevice;

    void mlme_associate_request(cMessage *msg);
    void mlme_disassociate_request(cMessage *msg);
    void mlme_get_request(cMessage *msg);
    void mlme_set_request(cMessage *msg);
    void mlme_scan_request(cMessage *msg);
    void mlme_start_request(cMessage *msg);
    void mlme_stop_request(cMessage *msg);

    void mlme_associate_confirm(uint64_t owpanID, uint16_t AID, AssociationResult_t associationResult, AssociationStatus_t status);
    void mlme_disassociate_confirm(uint64_t owpanID, uint64_t deviceAddress, DisassociationReason_t reason, DisassociationStatus_t status);
    void mlme_get_confirm(PibAttribute_t attribute, uint64_t* attributeValue, GetStatus_t status);
    void mlme_set_confirm(PibAttribute_t attribute, uint64_t attributeValue, SetStatus_t status);
    void mlme_scan_confirm(uint8_t* resultList, ScanStatus_t status); // TODO
    void mlme_start_confirm(StartStatus_t status);
    void mlme_stop_confirm(StopStatus_t status);

};

#endif /* DEVICEMAC_H_ */
