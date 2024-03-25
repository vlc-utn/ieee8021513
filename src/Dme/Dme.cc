#include "Dme.h"

void Dme::md_data_request(uint64_t destinationAddress, uint64_t sourceAddress, uint16_t msduLengthType, uint8_t* msdu, uint8_t priority, bool acknowledged) {
    MdDataRequest *msg = new MdDataRequest();

    msg->setDestinationAddress(destinationAddress);
    msg->setSourceAddress(sourceAddress);
    msg->setMsduLengthType(msduLengthType);

    msg->setMsduArraySize(msduLengthType);
    for (uint16_t i=0; i < msduLengthType; i++) {
        msg->setMsdu(i, msdu[i]);
    }

    msg->setPriority(priority);
    msg->setAcknowledged(acknowledged);

    send(msg, "requestOut");
}


void Dme::mlme_associate_request(uint64_t owpanID) {
    MlmeAssociateRequest *msg = new MlmeAssociateRequest();

    msg->setOwpanID(owpanID);

    msg->setKind(MsgKind_t::MLME_ASSOCIATE_REQUEST);
    send(msg, "requestOut");
}

void Dme::mlme_disassociate_request(uint64_t owpanID, uint64_t deviceAddress, DisassociationReason_t reason) {
    MlmeDisassociateRequest *msg = new MlmeDisassociateRequest();

    msg->setOwpanID(owpanID);
    msg->setDeviceAddress(deviceAddress);
    msg->setReason(reason);

    msg->setKind(MsgKind_t::MLME_DISASSOCIATE_REQUEST);
    send(msg, "requestOut");
}

void Dme::mlme_get_request(PibAttribute_t attribute) {
    MlmeGetRequest *msg = new MlmeGetRequest();

    msg->setAttribute(attribute);

    msg->setKind(MsgKind_t::MLME_GET_REQUEST);
    send(msg, "requestOut");
}

void Dme::mlme_set_request(PibAttribute_t attribute, uint64_t attributeValue) {
    MlmeSetRequest *msg = new MlmeSetRequest();

    msg->setAttribute(attribute);
    msg->setAttributeValue(attributeValue); // Note, owpan Name can't be set, so the maximum size is 48 bits.

    msg->setKind(MsgKind_t::MLME_SET_REQUEST);
    send(msg, "requestOut");
}

void Dme::mlme_scan_request(uint16_t scanDuration) {
    MlmeScanRequest *msg = new MlmeScanRequest();

    msg->setScanDuration(scanDuration);

    msg->setKind(MsgKind_t::MLME_SCAN_REQUEST);
    send(msg, "requestOut");
}

void Dme::mlme_start_request(void) {
    MlmeStartRequest *msg = new MlmeStartRequest();

    msg->setKind(MsgKind_t::MLME_START_REQUEST);
    send(msg, "requestOut");
}

void Dme::mlme_stop_request(uint16_t timeout, bool force) {
    MlmeStopRequest *msg = new MlmeStopRequest();

    msg->setTimeout(timeout);
    msg->setForce(force);

    msg->setKind(MsgKind_t::MLME_STOP_REQUEST);
    send(msg, "requestOut");
}


//////////////////////////////

void mlme_associate_confirm(cMessage *msg) {
    MlmeAssociateConfirm *xMsg = check_and_cast<MlmeAssociateConfirm *>(msg);

    delete xMsg;
}

void mlme_disassociate_confirm(cMessage * msg) {
    MlmeDisassociateConfirm *xMsg = check_and_cast<MlmeDisassociateConfirm *>(msg);

    delete xMsg;
}

void mlme_get_confirm(cMessage * msg) {
    MlmeGetConfirm *xMsg = check_and_cast<MlmeGetConfirm *>(msg);


    delete xMsg;
}

void mlme_set_confirm(cMessage * msg) {
    MlmeSetConfirm *xMsg = check_and_cast<MlmeSetConfirm *>(msg);

    delete xMsg;
}

void mlme_scan_confirm(cMessage * msg) {
    MlmeScanConfirm *xMsg = check_and_cast<MlmeScanConfirm *>(msg);

    delete xMsg;
}

void mlme_start_confirm(cMessage * msg) {
    MlmeStartConfirm *xMsg = check_and_cast<MlmeStartConfirm *>(msg);

    delete xMsg;
}

void mlme_stop_confirm(cMessage * msg) {
    MlmeStopConfirm *xMsg = check_and_cast<MlmeStopConfirm *>(msg);

    delete xMsg;
}
