#ifndef CODE_RUN_H_
#define CODE_RUN_H_

// ȫ�ֱ���
extern int gyro_lpf;
extern float Tdudy;
extern float gyro_pid[4];
extern pid_param_t AX;

void CH0_LOOP(void); //��ʱ��1

#endif /* CODE_RUN_H_ */
