/*
 * Key.h
 *
 *  Created on: 2024��1��24��
 *      Author: A
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_

// �궨��
#define Key1  P22_0
#define Key2  P22_1
#define Key3  P22_2
#define Key4  P22_3

// ȫ�ֱ�������
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;;

// ��������
/* УĦ����ѧ������
// extern int key_set2(gpio_pin_enum key);
// extern uint32 duty;
*/
void Key_init(void);
void Key_scan(void);

#endif /* CODE_KEY_H_ */
