#include "can_user.h"
#include "Motor.hpp"
#include "tim.h"
#include "Motor_apply.h"

extern "C" void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t data[8];
    if (hcan != &hcan1) return;

    if (HAL_CAN_GetRxMessage( hcan, CAN_RX_FIFO0, &rx_header, data) != HAL_OK) return;
    motor1.canRxMsgCallback(data);//拉取电机变量
}



extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
        {
            HAL_StatusTypeDef st =HAL_CAN_AddTxMessage( &hcan1, &tx_header, motor1.getTxData(), &can_tx_mailbox);
        }
    }

}