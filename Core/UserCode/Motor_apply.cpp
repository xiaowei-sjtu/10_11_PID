#include "Motor_apply.h"

#include "stm32f4xx_hal.h"

Motor motor1(36.0f);
extern "C" void motor1_Init()
{
    motor1.setMotorId(1);
    motor1.setTargetAngleDeg(0.0f);
    motor1.setk_frontfeedback(1.16f);
}
extern "C" void motor1_Handle()
{
    motor1.motor_handle();
}
