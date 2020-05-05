#ifndef __LCD_H_
#define __LCD_H_
#include	"STC8.H"
sbit RS=P3^5;     //LCD12864 RS¶Ë
sbit RW=P3^4;     //LCD12864 RW¶Ë
sbit E =P3^2;     //LCD12864 E ¶Ë

extern void Busy();
extern void delay_100us(uint16 t);//100us*t
extern void Write_Data(uint8 k);
extern void Write_Cmd(uint8 cmd);
extern void Disp(uint8 y,uint8 x,uint8 i,uint8 *z);
extern void DispS(uint8 y,uint8 x,uint8 p[]);
extern void Init_Lcd(void);

#endif