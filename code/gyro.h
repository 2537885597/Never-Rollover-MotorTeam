/*
 * gyro.h
 *
 *  Created on: 2024年1月25日
 *      Author: A
 */

#ifndef CODE_GYRO_H_
#define CODE_GYRO_H_

// 全局变量
extern int16 gyro1;
extern int16 gyro2;
extern int16 gyro3;

extern int16 acc1;
extern int16 acc2;
extern int16 acc3;

// 函数声明
void gyro_init(void);
void gyro_getangv(void);


#endif /* CODE_GYRO_H_ */
