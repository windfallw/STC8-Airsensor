#ifndef __LCD_H_
#define __LCD_H_
#include	"STC8.H"
#include <intrins.h>  //加入此头文件后,可使用_nop_库函数
sbit RS=P3^5;     //LCD12864 RS端
sbit RW=P3^4;     //LCD12864 RW端
sbit E =P3^2;     //LCD12864 E 端

extern void Busy();
extern void delay_100us(uint16 t);//100us*t
extern void Write_Data(uint8 k);
extern void Write_Cmd(uint8 cmd);
extern void Disp(uint8 y,uint8 x,uint8 i,uint8 *z);
extern void DispS(uint8 y,uint8 x,uint8 p[]);
extern void Init_Lcd(void);

#endif