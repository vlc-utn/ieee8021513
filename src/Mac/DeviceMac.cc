#include "DeviceMac.h"

void DeviceMac::mlme_associate_confirm(uint64_t owpanID, uint16_t AID, AssociationResult_t associationResult, AssociationStatus_t status) {
    MlmeAssociateConfirm *msg = new MlmeAssociateConfirm();

    msg->setKind(MsgKind_t::MLME_ASSOCIATE_CONFIRM);
    send(msg, "confirmOut");
}

void DeviceMac::mlme_disassociate_confirm(uint64_t owpanID, uint64_t deviceAddress, DisassociationReason_t reason, DisassociationStatus_t status) {
    MlmeDisassociateConfirm *msg = new MlmeDisassociateConfirm();

    msg->setKind(MsgKind_t::MLME_DISASSOCIATE_CONFIRM);
    send(msg, "confirmOut");
}

void DeviceMac::mlme_get_confirm(PibAttribute_t attribute, uint64_t* attributeValue, GetStatus_t status) {
    MlmeGetConfirm *msg = new MlmeGetConfirm();

    msg->setAttribute(attribute);

    if (attribute == PibAttribute_t::MAC_OWPAN_NAME) {
        msg->appendAttributeValue(attributeValue[0]);
        msg->appendAttributeValue(attributeValue[1]);
        msg->appendAttributeValue(attributeValue[2]);
        msg->appendAttributeValue(attributeValue[3]);
    } else {
        msg->appendAttributeValue(*attributeValue);
    }

    msg->setStatus(status);

    msg->setKind(MsgKind_t::MLME_GET_CONFIRM);
    send(msg, "confirmOut");
}

void DeviceMac::mlme_set_confirm(PibAttribute_t attribute, uint64_t attributeValue, SetStatus_t status) {
    MlmeSetConfirm *msg = new MlmeSetConfirm();

    msg->setAttribute(attribute);
    msg->setAttributeValue(attributeValue);
    msg->setStatus(status);

    msg->setKind(MsgKind_t::MLME_SET_CONFIRM);
    send(msg, "confirmOut");
}

// TODO
void DeviceMac::mlme_scan_confirm(uint8_t* resultList, ScanStatus_t status) {
    MlmeScanConfirm *msg = new MlmeScanConfirm();

    msg->setKind(MsgKind_t::MLME_SCAN_CONFIRM);
    send(msg, "confirmOut");
}

void DeviceMac::mlme_start_confirm(StartStatus_t status) {
    MlmeStartConfirm *msg = new MlmeStartConfirm();

    msg->setKind(MsgKind_t::MLME_START_CONFIRM);
    send(msg, "confirmOut");
}

void DeviceMac::mlme_stop_confirm(StopStatus_t status) {
    MlmeStopConfirm *msg = new MlmeStopConfirm();

    msg->setKind(MsgKind_t::MLME_STOP_CONFIRM);
    send(msg, "confirmOut");
}

////////////////////////////////////////////////////

void DeviceMac::mlme_associate_request(cMessage *msg) {
    MlmeAssociateRequest *xMsg = check_and_cast<MlmeAssociateRequest *>(msg);

    delete xMsg;
}

void DeviceMac::mlme_disassociate_request(cMessage *msg) {
    MlmeDisassociateRequest *xMsg = check_and_cast<MlmeDisassociateRequest *>(msg);

    delete xMsg;

}

void DeviceMac::mlme_get_request(cMessage *msg) {
    MlmeGetRequest *xMsg = check_and_cast<MlmeGetRequest *>(msg);

    GetStatus_t status = GetStatus_t::GET_STATUS_SUCCESS;
    uint64_t* attributeValue = new uint64_t;


    switch (xMsg->getAttribute()) {
        case PibAttribute_t::MAC_MAC_ADDRESS: {
            *attributeValue = this->macMacAddress;
            break;
        }

        case PibAttribute_t::MAC_OWPAN_NAME: {
            delete attributeValue;
            attributeValue = new uint64_t(4);
            for (uint8_t i = 0; i < 4; i++) {
                attributeValue[i] = 0;
                for (uint8_t j = 0; j < 8; j++) {
                    attributeValue[i] |= this->macOwpanName[i+j] << j*8;
                }
            }
            break;
        }

        case PibAttribute_t::MAC_OWPAN_ID: {
            *attributeValue = this->macOwpanID;
            break;
        }

        case PibAttribute_t::MAC_ASSOCIATION_TIMEOUT: {
            *attributeValue = this->macAssociationTimeout;
            break;
        }

        case PibAttribute_t::MAC_ASSOCIATION_MAX_RETRIES: {
            *attributeValue = this->macAssociationMaxRetries;
            break;
        }

        case PibAttribute_t::MAC_ASSOCIATION_IDENTIFIER: {
            *attributeValue = this->macAssociationIdentifier;
            break;
        }

        case PibAttribute_t::MAC_DEVICE_TIMEOUT: {
            *attributeValue = this->macDeviceTimeout;
            break;
        }

        case PibAttribute_t::MAC_QUEUE_REPORT_TIMEOUT: {
            *attributeValue = this->macQueueReportTimeout;
            break;
        }

        case PibAttribute_t::MAC_MAX_RTS_CW: {
            *attributeValue = this->macMaxRtsCw;
            break;
        }

        case PibAttribute_t::MAC_RETRANSMIT_TIMEOUT: {
            *attributeValue = this->macRetransmitTimeout;
            break;
        }

        case PibAttribute_t::MAC_MAX_FRAME_RETRIES: {
            *attributeValue = this->macMaxFrameRetries;
            break;
        }

        case PibAttribute_t::MAC_MAX_REASSEMBLY_TIMEOUT: {
            *attributeValue = this->macMaxReassemblyTimeout;
            break;
        }

        case PibAttribute_t::PHY_IMPLEMENTED_PHY: {
            *attributeValue = this->phyImplementedPhy;
            break;
        }

        default: {
            status = GetStatus_t::GET_STATUS_FAIL_NON_EXISTENT;
            break;
        }
    }

    this->mlme_get_confirm(xMsg->getAttribute(), attributeValue, status);
    delete attributeValue;

    delete xMsg;
}

void DeviceMac::mlme_set_request(cMessage *msg) {
    MlmeSetRequest *xMsg = check_and_cast<MlmeSetRequest *>(msg);

    SetStatus_t status = SetStatus_t::SET_STATUS_SUCCESS;

    switch (xMsg->getAttribute()) {
            case PibAttribute_t::MAC_MAC_ADDRESS: {
                status = SetStatus_t::SET_STATUS_FAIL_READ_ONLY;
                break;
            }

            case PibAttribute_t::MAC_OWPAN_NAME: {
                status = SetStatus_t::SET_STATUS_FAIL_READ_ONLY;
                break;
            }

            case PibAttribute_t::MAC_OWPAN_ID: {
                status = SetStatus_t::SET_STATUS_FAIL_READ_ONLY;
                break;
            }

            case PibAttribute_t::MAC_ASSOCIATION_TIMEOUT: {
                this->macAssociationTimeout = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::MAC_ASSOCIATION_MAX_RETRIES: {
                this->macAssociationMaxRetries = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::MAC_ASSOCIATION_IDENTIFIER: {
                status = SetStatus_t::SET_STATUS_FAIL_READ_ONLY;
                break;
            }

            case PibAttribute_t::MAC_DEVICE_TIMEOUT: {
                this->macDeviceTimeout = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::MAC_QUEUE_REPORT_TIMEOUT: {
                this->macQueueReportTimeout = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::MAC_MAX_RTS_CW: {
                this->macMaxRtsCw = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::MAC_RETRANSMIT_TIMEOUT: {
                status = SetStatus_t::SET_STATUS_FAIL_READ_ONLY;
                break;
            }

            case PibAttribute_t::MAC_MAX_FRAME_RETRIES: {
                this->macMaxFrameRetries = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::MAC_MAX_REASSEMBLY_TIMEOUT: {
                this->macMaxReassemblyTimeout = xMsg->getAttributeValue();
                break;
            }

            case PibAttribute_t::PHY_IMPLEMENTED_PHY: {
                status = SetStatus_t::SET_STATUS_FAIL_READ_ONLY;
                break;
            }

            default: {
                status = SetStatus_t::SET_STATUS_FAIL_NON_EXISTENT;
                break;
            }
        }

    this->mlme_set_confirm(xMsg->getAttribute(), xMsg->getAttributeValue(), status);

    delete xMsg;
}

void DeviceMac::mlme_scan_request(cMessage *msg) {
    MlmeScanRequest *xMsg = check_and_cast<MlmeScanRequest *>(msg);

    delete xMsg;
}

void DeviceMac::mlme_start_request(cMessage *msg) {
    MlmeStartRequest *xMsg = check_and_cast<MlmeStartRequest *>(msg);

    delete xMsg;
}

void DeviceMac::mlme_stop_request(cMessage *msg) {
    MlmeStopRequest *xMsg = check_and_cast<MlmeStopRequest *>(msg);

    delete xMsg;
}
