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

void CoordinatorMac::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        this->processSelfMsg(msg);
    }
}

void CoordinatorMac::initialize(void) {
    DeviceMac::initialize();
    this->numSuperframeSlots = par("numSperframeSlots");
    this->syncInterval = par("syncInterval");

    if (syncInterval > aMaxSyncInterval) {
        EV_ERROR << "syncInterval is greater than aMaxSyncInterval\n";
    }

    this->syncCounter = syncInterval;
    this->currentSlot = 0;
    this->currentSuperframe = 0;
}


void CoordinatorMac::processSelfMsg(cMessage *packet) {
    if (packet == this->timerSlot) {
        currentSlot++;
        if (currentSlot == numSuperframeSlots) {
            currentSlot = 0;
            currentSuperframe++;
            if (currentSuperframe == 0xffff) {
                currentSuperframe = 0;
            }
        }

        syncCounter--;
        if (syncCounter == 0) {
            syncCounter = syncInterval;
            // TODO transmit sync element.
        }
    }
}

void CoordinatorMac::fsmSuperframe(void) {

}
