#include "LCD.h"

//void Busy()
//{
//  uint8 busy;
//  do
//  {
//      E = 0;           //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
//      RS = 0;          //1Ϊָ��,0Ϊ����
//      RW = 1;          //1Ϊ��,0Ϊд
//      delay_100us(2);
//      E = 1;           //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
//      P2M0=0x00;
//      P2M1=0x00;	     //����P2.0~P2.7Ϊ׼˫���
//      busy=P2;         //��ȡP2״̬
//      delay_100us(2);
//      E = 0;           //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
//  } 
//  while(busy&0x80);  //�ж�BUSYλ�Ƿ���:1Ϊ�ڲ��ڹ���,0Ϊ����״̬
//}

void delay_100us(uint16 t)
{
    uint16 i,j;
    for(i=0; i<t;  i++)
    {
        for(j=0; j<10; j++);
    }
}

void Write_Data(uint8 k)
{
//    Busy();
    E =1;         //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
    RS=1;         //1Ϊָ��,0Ϊ����
    RW=0;         //1Ϊ��,0Ϊд
    P2M1 = 0;	    //����P2.0~P2.7Ϊ�������
    P2M0 = 0xff;	//����P2.0~P2.7Ϊ�������
    P2=k;         //��������K��DATA
    delay_100us(2);
    E =0;         //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
    delay_100us(2);
}

void Write_Cmd(uint8 cmd)
{
//    Busy();
    E=1;          //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
    RS=0;         //1Ϊָ��,0Ϊ����
    RW=0;         //1Ϊ��,0Ϊд
    P2M1 = 0;	    //����P2.0~P2.7Ϊ�������
    P2M0 = 0xff;	//����P2.0~P2.7Ϊ�������
    P2=cmd;       //��������cmd��DATA
    delay_100us(2);
    E=0;          //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�
    delay_100us(2);
}

void Disp(uint8 y,uint8 x,uint8 i,uint8 *z)
{
    uint8 Address;
    if(y==1)
    {
        Address=0x80+x;
    }
    //Y�жϵڼ���,X�жϵڼ���,0x80ΪҺ���г�ʼ��ַ
    if(y==2) {
        Address=0x90+x;
    }
    if(y==3) {
        Address=0x88+x;
    }
    if(y==4) {
        Address=0x98+x;
    }
    Write_Cmd(Address);           //д���ַ���LCD12864
    while(i)                      //д����ʾ���ݵĴ�С
    {
        Write_Data(*(z++));         //д����ʾ���ݵ�LCD12864
        i--;
    }
}

void DispS(uint8 y,uint8 x,uint8 p[])
{
    uint8 Address;
    if(y==1)
    {
        Address=0x80+x;
    }
    if(y==2)
    {
        Address=0x90+x;
    }
    if(y==3)
    {
        Address=0x88+x;
    }
    if(y==4)
    {
        Address=0x98+x;
    }
    Write_Cmd(Address);
    while(*p != '\0')
    {
        Write_Data(*p);
        p++;
    }
}

void Init_Lcd(void)
{
    Write_Cmd(0x30);   //����ָ�
    Write_Cmd(0x02);   // ��ַ��λ
    Write_Cmd(0x0c);   //������ʾ��,�α�ر�
    Write_Cmd(0x06);   //�α�����
    Write_Cmd(0x80);   //�趨��ʾ����ʼ��ַ
    Write_Cmd(0x01);   //�����ʾ
}