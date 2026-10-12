//
// Created by 18504 on 2026/10/11.
//

#ifndef CLANG_FORMAT_PID_H
#define CLANG_FORMAT_PID_H


class PID
{
public:
    PID(float Kp, float Ki, float Kd, float i_max, float out_max, float d_filter_k, float p_filter_k);
    void PID_reset();
    float calc(float ref, float fdb);

private:
    float kp_, ki_, kd_;
    float out_max_ = 0;
    float d_filter_k_ = 0;
    float err_sum_ = 0;
    float iout_ = 0;
    float pout_ = 0;
    float dout_ = 0;
    float prev_err_ = 0;
    float i_max_ = 0;
    float err_ = 0;
    float p_filter_k_ = 0;
    float output = 0;

};



#endif //CLANG_FORMAT_PID_H
