//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "CoordinatorMac.h"


//    void transmitElement(MacFrameType_t type, bool fragmentedFrame,
//        bool relayedFrame, uint64_t receiverAddress, ElementID_t payloadElementID,
//        bool ackRequest, uint8_t fragmentNumber, uint8_t lastFragment,
//        uint64_t relayAddress, uint8_t* payload, uint16_t payloadSize);

void CoordinatorMac::txNull(uint64_t receiverAddress, bool ackRequest) {
    transmitElement(MANAGEMENT_FRAME, false, false, receiverAddress, NULL_ELEMENT, ackRequest, 0, 0, 0, nullptr, 0);
}


void CoordinatorMac::txSync(void) {
    uint8_t payload[6];
    payload[0] = (currentSuperframe >> 0);
    payload[1] = (currentSuperframe >> 8);
    payload[2] = (numSuperframeSlots >> 0);
    payload[3] = (numSuperframeSlots >> 8);
    payload[4] = (currentSlot >> 0);
    payload[5] = (currentSlot >> 8);
    transmitElement(CONTROL_FRAME, false, false, BROADCAST_ADDRESS, SYNC_ELEMENT, false, 0, 0, 0, payload, 6);
}













void CoordinatorMac::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        this->processSelfMsg(msg);
    } else if (msg->arrivedOn("responseIn")) {
        this->processMsgFromLowerLayer(msg);
    } else {
        this->processMsgFromHigherLayer(msg);
    }
}

void CoordinatorMac::initialize(void) {
    Mac::initialize();
    this->numSuperframeSlots = par("numSperframeSlots");
    this->syncInterval = par("syncInterval");

    if (syncInterval == 0) {
        EV_ERROR << "syncInterval can't be zero";
    }

    if (syncInterval > aMaxSyncIntervalInSlots) {
        EV_ERROR << "syncInterval is greater than aMaxSyncInterval\n";
    }

    this->syncCounter = 0;
    this->currentSlot = 0;
    this->currentSuperframe = 0;
    this->slotState = new uint8_t(numSuperframeSlots);
    this->sequenceNumber = 0;
}

void CoordinatorMac::finish(void) {
    delete slotState;
}


void CoordinatorMac::processSelfMsg(cMessage *packet) {
    if (packet == this->timerSlot) {
        this->superframeScheduler();
    }
}

void CoordinatorMac::processMsgFromHigherLayer(cMessage *msg) {

}

void CoordinatorMac::processMsgFromLowerLayer(cMessage *msg) {
    // TODO hacer un switch case con todos los tipos de mensajes recibidos, y llamar a la función de
    // recepción correspondiente.
}


/// @brief: For every slot in a superframe, this function updates all relevant
/// variables regarding the superframe.
void CoordinatorMac::superframeScheduler(void) {
    currentSlot++;
    if (currentSlot == numSuperframeSlots) {
        currentSlot = 0;
        currentSuperframe++;
        if (currentSuperframe == 0xffff) {
            currentSuperframe = 0;
        }
    }

    syncCounter++;
    if (syncCounter == syncInterval) {
        syncCounter = 0;
        //this->transmitSyncSlot();
    }

    scheduleAfter(aSuperframeSlotDuration, this->timerSlot);
}

void CoordinatorMac::fsmSuperframe(void) {

}

void CoordinatorMac::transmitElement(MacFrameType_t type, bool fragmentedFrame,
        bool relayedFrame, uint64_t receiverAddress, ElementID_t payloadElementID,
        bool ackRequest, uint8_t fragmentNumber, uint8_t lastFragment,
        uint64_t relayAddress, uint8_t* payload, uint16_t payloadSize) {
    Mpdu *mpdu = new Mpdu();
    MacHeader header;

    header.setFrameVersion(0);
    header.setType(type);
    header.setFragmentedFrame(fragmentedFrame);
    header.setRelayedFrame(relayedFrame);

    header.setTransmitterAddress(this->macMacAddress);
    header.setReceiverAddress(receiverAddress);

    header.setPayloadElementID(payloadElementID);

    header.setSequenceNumber(this->sequenceNumber);
    sequenceNumber++;
    if (sequenceNumber == 0x1000) {
        sequenceNumber = 0;
    }
    header.setAckRequest(ackRequest);

    header.setFragmentNumber(fragmentNumber);
    header.setLastFragment(lastFragment);

    header.setRelayAddress(relayAddress);

    mpdu->setHeader(header);
    mpdu->setPayloadArraySize(payloadSize);
    for (uint16_t i = 0; i < payloadSize; i++) {
        mpdu->setPayload(i, payload[i]);
    }
    mpdu->setFcs(0);

    send(mpdu, "indicationOut");
}
