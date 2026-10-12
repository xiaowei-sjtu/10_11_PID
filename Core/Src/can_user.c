#include "can_user.h"

CAN_RxHeaderTypeDef rx_header;

CAN_TxHeaderTypeDef tx_header ={
    .StdId = 0x200,
    .ExtId = 0x0,
    .IDE = CAN_ID_STD,
    .TransmitGlobalTime =  DISABLE,
    .DLC = 8,
    .RTR = CAN_RTR_DATA,
};

uint32_t can_tx_mailbox;

CAN_FilterTypeDef can_filter_config ={
    .FilterBank = 0,
    .FilterMode = CAN_FILTERMODE_IDMASK,
    .FilterScale = CAN_FILTERSCALE_32BIT,
    .FilterIdHigh = 0x0000,
    .FilterMaskIdHigh = 0x0000,
    .FilterMaskIdLow = 0x0000,
    .FilterActivation = ENABLE,
    .SlaveStartFilterBank = 14,
    .FilterFIFOAssignment = CAN_RX_FIFO0,
    .FilterIdLow = 0X0000,

};

void CAN_User_settxHeader( uint32_t std_id, uint8_t dlc)
{
    tx_header.StdId = std_id;
    tx_header.DLC = dlc;
}
