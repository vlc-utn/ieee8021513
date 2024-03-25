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

enum DisassociationReason_t {
    OTHER = 1;
    DISCONNECTING = 2;
    HANDOVER = 3;
    LACK_OF_RESOURCES = 4;
    POOR_CHANNEL = 5;
    UNRELIABLE_CONNECTION = 6;
    TIMEOUT = 7;
};

enum PibAttribute_t {
    MAC_MAC_ADDRESS = 0;
    MAC_OWPAN_NAME = 1;
    MAC_OWPAN_ID = 2;
    MAC_ASSOCIATION_TIMEOUT = 3;
    MAC_ASSOCIATION_MAX_RETRIES = 4;
    MAC_ASSOCIATION_IDENTIFIER = 5;
    MAC_DEVICE_TIMEOUT = 6;
    MAC_QUEUE_REPORT_TIMEOUT = 7;
    MAC_MAX_RTS_CW = 8;
    MAC_RETRANSMIT_TIMEOUT = 9;
    MAC_MAX_FRAME_RETRIES = 10;
    MAC_MAX_REASSEMBLY_TIMEOUT = 11;
    PHY_IMPLEMENTED_PHY = 12;
};

enum PhyType_t {
    PM_PHY = 0;
    HB_PHY = 1;
};

enum AssociationResult_t {
	ASSOC_RESULT_DENIED = 1;
	ASSOC_RESULT_SUCCESS = 2;
};

enum AssociationStatus_t {
    ASSOC_STATUS_SUCCESS = 0;
    ASSOC_STATUS_NO_RESPONSE = 1;
};

enum DisassociationStatus_t {
    DISASSOC_STATUS_SUCCESS = 0;
    DISASSOC_STATUS_NOT_ASSOCIATED = 1;
};

enum GetStatus_t {
    GET_STATUS_SUCCESS = 0;
    GET_STATUS_FAIL_NON_EXISTENT = 1;
    GET_STATUS_FAIL_OTHER = 2;
};

enum SetStatus_t {
    SET_STATUS_SUCCESS = 0;
    SET_STATUS_FAIL_READ_ONLY = 1;
    SET_STATUS_FAIL_NON_EXISTENT = 2;
    SET_STATUS_FAIL_OTHER = 3;
};

enum ScanStatus_t {
  	SCAN_STATUS_SUCCESS = 0;
  	SCAN_STATUS_FAIL_SCAN_IN_PROGRESS = 1;
  	SCAN_STATUS_FAIL_OTHER = 2;  
};

enum StartStatus_t {
  	START_STATUS_SUCCESS = 0;
  	START_STATUS_FAIL_INVALID_CONFIGURATION = 1;
  	START_STATUS_FAIL_OTHER_NETWORK_FOUND = 2;
  	START_STATUS_FAIL_OTHER = 3;  
};

enum StopStatus_t {
    STOP_STATUS_SUCCESS = 0;
    STOP_STATUS_FAIL_TIMEOUT = 1;
    STOP_STATUS_FAIL_OTHER = 2;
};

message MdDataRequest {
    uint64_t destinationAddress;
    uint64_t sourceAddress;
    uint16_t msduLengthType;	// As defined in EtherType
    uint8_t msdu[];
    uint8_t priority;
    bool acknowledged;
};

message MlmeAssociateRequest {
	uint64_t owpanID;
};

message MlmeDisassociateRequest {
    uint64_t owpanID;
    uint64_t deviceAddress;
    DisassociationReason_t reason;
};

message MlmeGetRequest {
    PibAttribute_t attribute;
};

message MlmeSetRequest {
    PibAttribute_t attribute;
    uint64_t attributeValue;
};

message MlmeScanRequest {
 	uint16_t scanDuration;  
};

message MlmeStartRequest {
  	// Nothing  
};

message MlmeStopRequest {
	uint16_t timeout;
	bool force;
};

////////////////////////////////////////////////////

message MlmeAssociateConfirm {
	uint64_t owpanID;
	uint16_t AID;
	AssociationResult_t associationResult;
	AssociationStatus_t status;
};

message MlmeDisassociateConfirm {
    uint64_t owpanID;
    uint64_t deviceAddress;
    DisassociationReason_t reason;
    DisassociationStatus_t status;
};

message MlmeGetConfirm {
    PibAttribute_t attribute;
    uint64_t attributeValue[];
    GetStatus_t status;
};

message MlmeSetConfirm {
    PibAttribute_t attribute;
    uint64_t attributeValue;
    SetStatus_t status;
};

message MlmeScanConfirm {
    uint8_t resultList[];
    ScanStatus_t status;
};

message MlmeStartConfirm {
    StartStatus_t status;
};

message MlmeStopConfirm {
    StopStatus_t status;
};







