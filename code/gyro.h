/*
 * gyro.h
 *
 *  Created on: 2024��1��25��
 *      Author: A
 */

#ifndef CODE_GYRO_H_
#define CODE_GYRO_H_

// ȫ�ֱ���
extern int16 gyro1;
extern int16 gyro2;
extern int16 gyro3;

extern int16 acc1;
extern int16 acc2;
extern int16 acc3;

// ��������
void gyro_init(void);
void gyro_getangv(void);


#endif /* CODE_GYRO_H_ */
