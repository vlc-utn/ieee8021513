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

enum MacFrameType_t {
    DATA_FRAME = 0;
    CONTROL_FRAME = 1;
    MANAGEMENT_FRAME = 2;
};

enum ElementID_t {
    NULL_ELEMENT = 0;
    MANAGEMENT_PROCEDURE_CONTAINER_ELEMENT = 1;
    MULTIPLE_ELEMENT_CONTAINER_ELEMENT = 2;
    MULTIPLE_DEVICE_ELEMENT_CONTAINER = 3;
    VENDOR_SPECIFIC_ELEMENT = 4;
    SYNC_ELEMENT = 5;
    RTS_DESCRIPTOR_ELEMENT = 6;
    GTS_DESCRIPTOR_LIST_ELEMENT = 7;
    GTS_DESCRIPTOR_ELEMENT = 8;
    QUEUE_REPORT_ELEMENT = 9;
    RANDOM_ACCESS_ELEMENT = 10;
    RANDOM_ACCESS_RESPONSE_ELEMENT = 11;
    POLL_ELEMENT = 12;
    POLL_RESPONSE_ELEMENT = 13;
    ANNOUNCEMNT_ELEMENT = 14;
    ASSOCIATION_REQUEST_ELEMENT = 15;
    ASSOCIATION_RESPONSE_ELEMENT = 16;
    DISASSOCIATION_NOTIFICATION_ELEMENT = 17;
    CAPABILITY_LIST_ELEMENT = 18;
    SUPPORTED_MCS_ELEMENT = 19;
    PM_PHY_MCS_LIST_ELEMENT = 20;
    HB_PHY_MCS_LIST_ELEMENT = 21;
    MCS_REQUEST_ELEMENT = 22;
    PM_PHY_MCS_ELEMENT = 23;
    HB_PHY_MCS_ELEMENT = 24;
    ATTRIBUTE_CHANGE_REQUEST_ELEMENT = 25;
    ATTRIBUTE_CHANGE_RESPONSE_ELEMENT = 26;
    INTERFERENCE_NOTIFICATION_ELEMENT = 27;
    EXPLICIT_MIMO_FEEDBACK_ELEMENT = 28;
    SINGLE_MSDU_ELEMENT = 29;
    SINGLE_ADDRESS_AGGREGATED_MSDU_ELEMENT = 30;
    MULTIPLE_ADDRESS_AGGREGATED_MSDU_ELEMENT = 31;
    SINGLE_ACK_ELEMENT = 32;
    BLOCK_ACK_REQUEST_ELEMENT = 33;
    BLOCK_ACK_ELEMENT = 34;
    REACHABLE_ADDRESS_ELEMENT = 35;
    RELAY_DEVICE_CONFIGURATION = 36;
    RELAY_DEVICE_CONFIGURATION_RESPONSE_ELEMENT = 37;
    RELAYED_DEVICE_CONFIGURATION_REQUEST_ELEMENT = 38;
    RELAYED_DEVICE_CONFIGURATION_RESPONSE_ELEMENT = 39;
}


packet MacHeader {
    // Frame Control
    uint8_t frameVersion = 0;	// 2 bits, always 0b00
    MacFrameType_t type;		// 2 bits
	bool fragmentedFrame;
	bool relayedFrame;
    // RESERVED 10 bits
    
    uint64_t receiverAddress;		// 48 bit
    uint64_t transmitterAddress;	// 48 bit
    
    ElementID_t payloadElementID;
    
    // Sequence Control (optional, for data and management frames)
    uint16_t sequenceNumber;		// 12 bit
    bool ackRequest;
    // RESERVED 3 bits
    
    // Fragmentation control field (optional, if "fragmenetedFrame")
    uint8_t fragmentNumber;			// 4 bit
    uint8_t lastFragment;			// 4 bit
    // RESERVED 8 bits
    
    // Relay Control Field (optional, if "relayedFrame")
    uint64_t relayAddress;			// 48 bit
    // RESERVED 16 bits 
};


packet Mpdu {
    MacHeader header;
    uint8_t payload[];
    uint32_t fcs;
};

