/*
 * Mac.h
 *
 *  Created on: Apr 4, 2024
 *      Author: cotti
 */

#ifndef MAC_H_
#define MAC_H_

#include "../msgs/mac_primitives_m.h"
#include "../msg_kind.h"
#include "../msgs/mpdu_m.h"
#include <omnetpp.h>

#define BROADCAST_ADDRESS 0xffffffffffff

using namespace omnetpp;

class Mac : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

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





public:
    static constexpr double aMaxAnnouncementInterval = 1;       // [s]
    static constexpr uint32_t aMaxSyncInterval = 1;             // [s]
    static constexpr double aSuperframeSlotDuration = 1e-6;     // [s]
    static constexpr uint32_t aMacSuperframeLookahead = 8192;   // [superframes]
    static constexpr uint8_t aInitialRtsCw = 1;                 // [RANDOPs]
    static constexpr uint32_t aClockAccuracy = 20;              // [ppm]
    static constexpr uint8_t aMinFragmentSize = 64;             // [octets]
    static constexpr uint16_t aAckWindow = 1024;                // [MPDUs]

    static constexpr uint16_t aPhyMaxPsduSize = 2044;           // [octets]
    static constexpr double aPhyMifsDuration = 3e-6;            // [seconds]
    static constexpr double aPhyTuraroundTime = 10e-6;          // [seconds]
    static constexpr double aPhyClockAccuracy = 10e-6;          // [ppm]
    static constexpr double aPhyOfeSyncAccuracy = 640e-9;       // [seconds]

    /// Custom constants
    static constexpr uint32_t aMaxAnnouncementIntervalInSlots = aMaxAnnouncementInterval / aSuperframeSlotDuration; // [slots]
    static constexpr uint32_t aMaxSyncIntervalInSlots = aMaxSyncInterval / aSuperframeSlotDuration;                 // [slots]

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


    /// Variables used by both coordinator and device.
    uint16_t numSuperframeSlots;    // Amount of slots in a superframe
    uint16_t currentSlot;       // Current slot [0; numSuperframeSlots]
    uint16_t currentSuperframe; // Current superframe [0; 0xffff]
    cMessage* timerSlot;
};



#endif /* MAC_H_ */
