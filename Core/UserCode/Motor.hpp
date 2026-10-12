#ifndef MOTOR_HPP
#define MOTOR_HPP
#include <cstdint>
#include "PID.h"

class Motor
{
public:
    explicit Motor(float ratio);

    void canRxMsgCallback(const uint8_t rx_data[8]);

    float angle() const;
    float speedRpm() const;
    bool hasFeedback() const;
    float setTargetcurrentA(float amperes) ;
    void setTxCurrent( float amperes, uint8_t motor_id );
    uint8_t* getTxData();
    void Handle();
    void setTargetAngleDeg(float angle);
    void setTargetSpeed(float speed);
    void motor_handle();
    void setMotorId(uint8_t motor_id);
private:
    const float ratio_;
    float ecd_angle_ = 0;
    float speedRpm_ = 0;
    float angle_ = 0;
    float last_ecd = 0;
    bool received_ = false;
    uint8_t tx_data_[8] = {};
    float NormalizeDelta(float delta);
    float Ecd_to_dig( float raw_ecd_angle);
    static constexpr uint16_t kEncoderRange = 8192;

    PID pPID;
    PID sPID;
    float targetAngle_ = 0;
    float targetSpeed_ = 0;
    float outCurrentA_ = 0;
    float speed_frontfeedback_ = 0;
    float current_frontfeedback_ = 0;
    void setSpeed_ffb(float speed_ffb);
    void setCurrent_ffb(float current_ffb);
    uint8_t motor_id_ = 1;
};
#endif
