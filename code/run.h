#ifndef CODE_RUN_H_
#define CODE_RUN_H_

// 全局变量
extern int gyro_lpf;
extern float Tdudy;
extern float gyro_pid[4];
extern pid_param_t AX;

void CH0_LOOP(void); //定时器1

#endif /* CODE_RUN_H_ */
