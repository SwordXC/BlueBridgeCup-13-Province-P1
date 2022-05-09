#include "menu.h"
#include "lcd.h"
#include "gpio.h"
#include "tim.h"
int8_t B1=-1,B2=-1,B3=-1;
int8_t ErrorTimes=0;
uint16_t Password=123;
int duty;
key key_v=no_key;

void menu_init()
{
	menu_first();	

	while(1)
	{
			key_v=key_scan();
			if(key_v==key1_on)
			{
				
				B1++;
				if(B1>9) B1=0;
				LCD_DispDecAt(Line4,Column7,B1,1);
				
			}
			if(key_v==key2_on)
			{
				B2++;
				if(B2>9) B2=0;
				LCD_DispDecAt(Line5,Column7,B2,1);
				
			}
			if(key_v==key3_on)
			{
				B3++;
				if(B3>9) B3=0;
				LCD_DispDecAt(Line6,Column7,B3,1);
				
			}
			if(key_v==key4_on)
			{
				PasswordEnter();
			}
	}
}
void PasswordInput()
{
	if(B1>9) B1=0;
	if(B2>9) B2=0;
	if(B3>9) B3=0;
	LCD_DispDecAt(Line4,Column7,B1,1);
	LCD_DispDecAt(Line5,Column7,B2,1);
	LCD_DispDecAt(Line6,Column7,B3,1);
}	
void PasswordEnter()
{
	uint16_t PasswordPut;
	PasswordPut=(B1)*100+(B2)*10+B3;
	LCD_DispDecAt(Line8,Column0,PasswordPut,4);
	LCD_DispDecAt(Line9,Column0,Password,4);
	if(PasswordPut==Password)
	{
		menu_second();
		led_on(1);
		htim17.Init.Period= 500;//2KHz
		PWM17_duty(50);//10%
		HAL_Delay(5000);
		led_off(1);
		htim17.Init.Period=1000;//1Khz
		PWM17_duty(500);//50%
		menu_first();
		B1=-1;
		B2=-1;
		B3=-1;
	}
	else
	{
		menu_first();
		B1=-1;
		B2=-1;
		B3=-1;
		ErrorTimes++;
		if(ErrorTimes>=3)
		{
			LED2();
		}

	}
}
void menu_first()
{
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line2,Column7,"PSD");
	LCD_DisplayStringLine(Line4,Column4,"B1:");
	LCD_DisplayStringLine(Line5,Column4,"B2:");
	LCD_DisplayStringLine(Line6,Column4,"B3:");
	LCD_DisplayStringLine(Line4,Column7,"@");
	LCD_DisplayStringLine(Line5,Column7,"@");
	LCD_DisplayStringLine(Line6,Column7,"@");
}
void menu_second()
{
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	LCD_DisplayStringLine(Line2,Column7,"STA");
	LCD_DisplayStringLine(Line4,Column4,"F:2000");
	LCD_DisplayStringLine(Line4,Column10,"Hz");
	LCD_DisplayStringLine(Line5,Column4,"D:10%");
}
void LED1()
{
	led_on(1);
	HAL_Delay(5000);
	led_off(1);
}
void LED2()
{
	int i;
	for(i=1;i<=25;i++)
	{
		led_on(2);
		HAL_Delay(100);
		led_off(2);
		HAL_Delay(100);
	}
}
void PWM_duty()
{
	htim17.Init.Period= 500;//2KHz
	PWM17_duty(50);//10%
	HAL_Delay(5000);
	htim17.Init.Period=1000;//1Khz
	PWM17_duty(500);//50%
}
key key_scan()
{
	key key_value;
	if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET)||
		(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET))
	{
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET))
		{
			key_value=key1_on;
			while((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET));
			return key_value;
		}
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET))
		{
			key_value=key2_on;
			while((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==GPIO_PIN_RESET));
			return key_value;
		}
		if((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==GPIO_PIN_RESET))
		{
			key_value=key3_on;
			while((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==GPIO_PIN_RESET));
			return key_value;
		}
		if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET))
		{
			key_value=key4_on;
			while((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_RESET));
			return key_value;
		}
	}
	return no_key;
}
