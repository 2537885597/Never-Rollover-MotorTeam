/*
 * Key.h
 *
 *  Created on: 2024年1月24日
 *      Author: A
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_

// 宏定义
#define Key1  P22_0
#define Key2  P22_1
#define Key3  P22_2
#define Key4  P22_3

// 全局变量声明
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;;

// 函数声明
/* 校摩托组学长代码
// extern int key_set2(gpio_pin_enum key);
// extern uint32 duty;
*/
void Key_init(void);
void Key_scan(void);

#endif /* CODE_KEY_H_ */
