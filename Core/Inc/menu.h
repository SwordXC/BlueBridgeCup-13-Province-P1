#ifndef _MENU_H_
#define _MENU_H_
#include "main.h"

typedef enum
{
	no_key,
	key1_on,
	key2_on,
	key3_on,
	key4_on
}key;
extern uint16_t Password;
void menu_init(void);
void menu_first(void);
void menu_second(void);
void PasswordInput(void);
void PasswordEnter(void);
void LED1(void);
void LED2(void);
void PWM_duty(void);
key key_scan();
#endif
