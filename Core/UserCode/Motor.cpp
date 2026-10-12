#include "Motor.hpp"

Motor::Motor(float ratio): ratio_(ratio),
pPID(0.0f, 0.0f,0.0f, 100.0f, 500.0f, 0.1f, 0.1f ),
sPID(0.038f, 0.0f,0.02f, 100.0f, 500.0f, 0.1f, 0.1f )
{};
void Motor::canRxMsgCallback(const uint8_t rx_data[8])
{
    uint16_t raw_ecd = (uint16_t)(rx_data[0] << 8) | rx_data[1];
    int16_t raw_speed =(int16_t)(rx_data[2] << 8) | rx_data[3];
    ecd_angle_ = (float) raw_ecd;
    speedRpm_ = (float) raw_speed;

    if (!received_)
    {
        last_ecd = ecd_angle_;
        received_ = true;
        angle_ = Ecd_to_dig( last_ecd );
    }

    float delta =  NormalizeDelta(ecd_angle_ - last_ecd);
    angle_ += Ecd_to_dig(delta) / ratio_;

    last_ecd = ecd_angle_;
}

float Motor::NormalizeDelta(float delta)
{
    if (delta > kEncoderRange / 2.0f )
    {
        delta -= kEncoderRange;
    }
    else if (delta < -kEncoderRange / 2.0f )
    {
        delta += kEncoderRange;
    }
    return delta;
}

float Motor::Ecd_to_dig(float raw_ecd_angle)
{
   return raw_ecd_angle * 360.0f / 8192.0f;
}

float Motor::angle() const{ return angle_; }
float Motor::speedRpm() const{ return speedRpm_; }
bool Motor::hasFeedback() const {return received_ ;}

void Motor::setTxCurrent(float amperes, uint8_t motor_id)
{
    if (motor_id < 1 || motor_id > 8) return;
    int16_t rawA = (int16_t)( amperes * 10000.0f / 10.0f);
    if (rawA > 10000) rawA = 10000;
    if (rawA < -10000) rawA = -10000;

    uint8_t pos = 0;
    if (motor_id >= 1 && motor_id <= 4)
    {
        pos = (motor_id - 1) * 2;
    }else if (motor_id >= 5 && motor_id <= 8){
        pos = (motor_id - 5) * 2;
    }

    tx_data_[pos] = (uint8_t)(rawA >> 8);
    tx_data_[pos + 1] = (uint8_t)(rawA & 0xFF);
}

uint8_t* Motor::getTxData()
{
    motor_handle();
    return tx_data_;
}

void Motor::setTargetAngleDeg(float angle)
{
    targetAngle_ = angle;
}

void Motor::setTargetSpeed(float speed)
{
    targetSpeed_ = speed;
}

void Motor::setCurrent_ffb(float current_ffb)
{
    current_frontfeedback_ = current_ffb;
}

void Motor::setSpeed_ffb(float speed_ffb)
{
    speed_frontfeedback_ = speed_ffb;
}

void Motor::motor_handle()
{
    if (!received_) return;

    float pos_out = pPID.calc(targetAngle_,angle_);

    float spd_ref = pos_out + speed_frontfeedback_;

    float spd_out = sPID.calc(spd_ref,speedRpm_);

    outCurrentA_ = spd_out + current_frontfeedback_;

    setTxCurrent(outCurrentA_, motor_id_);
}

void Motor::setMotorId(uint8_t motor_id)
{
    motor_id_ = motor_id;
}
