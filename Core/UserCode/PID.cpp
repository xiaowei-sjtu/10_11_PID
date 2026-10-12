//
// Created by 18504 on 2026/10/11.
//

#include "PID.h"

PID::PID(float Kp, float Ki, float Kd, float i_max, float out_max, float d_filter_k,float p_filter_k)
{
    kp_ = Kp;
    ki_ = Ki;
    kd_ = Kd;
    out_max_ = out_max;
    d_filter_k_ = d_filter_k;
    p_filter_k_ = p_filter_k;
    i_max_ = i_max;
}
void PID::PID_reset()
{
    err_ = 0;
    err_sum_ = 0;
    prev_err_ = 0;
    pout_ = 0;
    dout_ = 0;
    iout_ = 0;
    output = 0;
}

float PID::calc(float ref, float fdb)
{
    prev_err_ = err_;
    err_ = ref - fdb;
    err_sum_ += err_;

    pout_ = p_filter_k_ * kp_ * err_ + ( 1 - p_filter_k_ ) * pout_ ;

    if (err_sum_ > i_max_) err_sum_ = i_max_;
    if (err_sum_ < -i_max_) err_sum_ = -i_max_;
    iout_ = ki_ * err_sum_;

    float tempt_d = kd_ * (err_ - prev_err_);
    dout_ = d_filter_k_ * tempt_d + ( 1 - d_filter_k_ ) * dout_;

    output = pout_ + dout_ + iout_;
    if (output > out_max_) output = out_max_;
    if (output < -out_max_) output = -out_max_;
    return output;
}

