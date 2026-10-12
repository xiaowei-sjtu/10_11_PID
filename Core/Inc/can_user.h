
#ifndef _CAN_USER_H
#define _CAN_USER_H
#include "can.h"

extern CAN_RxHeaderTypeDef rx_header;
extern CAN_TxHeaderTypeDef tx_header;
extern uint32_t can_tx_mailbox;
extern CAN_FilterTypeDef can_filter_config;
void CAN_User_settxHeader( uint32_t std_id, uint8_t dlc);

#endif
