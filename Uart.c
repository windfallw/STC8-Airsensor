#include "uart.h"

void Timer0Init(void)
{
	AUXR |= 0x80;                   //��ʱ��0Ϊ1Tģʽ
	//AUXR &= 0x7F;                   //��ʱ��0Ϊ12Tģʽ
	TMOD &= 0xF8;                   //��ʱ��0����Ϊ��ʱ��ʽ������ģʽΪ16λ�Զ���װģʽ
	TMOD &= 0xF7;                   //��ʱ��0�ſ�λGATE����Ϊ0
	//TMOD |= 0x08;                   //��ʱ��0�ſ�λGATE����Ϊ1
	TL0 = (65536-T1TMS);            //1Tģʽ�³�ʼװ��ֵ       
	TH0 = (65536-T1TMS) >> 8;       //1Tģʽ�³�ʼװ��ֵ  
	//TL0 = (65536-T12TMS);            //12Tģʽ�³�ʼװ��ֵ       
	//TH0 = (65536-T12TMS) >> 8;       //12Tģʽ�³�ʼװ��ֵ  
	TR0 = 1;                        //��ʱ��0��ʼ��ʱ
	ET0 = 1;                        //ʹ�ܶ�ʱ��0������ж�����λ
}

void UartInit1(void)//115200bps@11.0592MHz
{
    SCON = 0x50;		//8λ����,�ɱ䲨����
    AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
    AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
    T2L = 0xE8;		//�趨��ʱ��ֵ
    T2H = 0xFF;		//�趨��ʱ��ֵ
    AUXR |= 0x10;		//������ʱ��2

    ES = 1;     // ����1�жϴ�
    IE2 |= 0x01;// ����2�жϴ�
    IE2 |= 0x08;// ����3�жϴ�
    IE2 |= 0x10;// ����4�жϴ�
    EA = 1;     // ���жϴ�
}

void UartInit2(void)//115200bps@11.0592MHz
{
//  P_SW2 = 0x00; // RXD3/P0.0, TXD3/P0.1
//  P_SW2 = 0x01;   //RXD2_2/P4.0, TXD2_2/P4.2
    S2CON = 0x50;		//8λ����,�ɱ䲨����
}

void UartInit3(void)//9600bps@11.0592MHz
{
    S3CON = 0x10;		//8λ����,�ɱ䲨����
    S3CON |= 0x40;		//����3ѡ��ʱ��3Ϊ�����ʷ�����
    T4T3M |= 0x02;		//��ʱ��3ʱ��ΪFosc,��1T
    T3L = 0xE0;		//�趨��ʱ��ֵ
    T3H = 0xFE;		//�趨��ʱ��ֵ
    T4T3M |= 0x08;		//������ʱ��3
}

void UartInit4(void)//115200bps@11.0592MHz
{
    S4CON = 0x10;		//8λ����,�ɱ䲨����
    S4CON &= 0xBF;		//����4ѡ��ʱ��2Ϊ�����ʷ�����
}

void SendChar1(uint8 dat)
{
    SBUF = dat;                 //д���ݵ�UART���ݼĴ���
    while(TI == 0);             //��ֹͣλû�з���ʱ��TIΪ0��һֱ�ȴ�
    TI = 0;                     //���TIλ����λ����������㣩
}

void SendString1(uint8 p[],uint8 len)
{
    uint8 i;
    for(i=0; i<len; i++)
    {
        SendChar1(p[i]);
    }
}

void SendChar2(uint8 dat)
{
    S2BUF = dat;                 //д���ݵ�UART���ݼĴ���
    while(!(S2CON&S2TI));        //��ֹͣλû�з���ʱ��S2TIΪ0��һֱ�ȴ�
    S2CON&=~S2TI;                //���S2CON�Ĵ�����ӦS2TIλ����λ����������㣩
}

void SendString2(uint8 p[],uint8 len)
{
    uint8 i;
//    IE2 &= 0xFE; 			          // ����2�жϹر�
    for(i=0; i<len; i++)
    {
        SendChar2(p[i]);
    }
//    IE2 |= 0x01;                // ����2�жϴ�
}

void SendChar3(uint8 dat)
{
    S3BUF = dat;                 //д���ݵ�UART���ݼĴ���
    while(!(S3CON&S3TI));        //��ֹͣλû�з���ʱ��S3TIΪ0��һֱ�ȴ�
    S3CON&=~S3TI;                //���S3CON�Ĵ�����ӦS3TIλ����λ����������㣩
}

void SendString3(uint8 p[],uint8 len)
{
    uint8 i;
//    IE2 &= 0xF7; 			               // ����3�жϹر�
    for(i=0; i<len; i++)
    {
        SendChar3(p[i]);
    }
//    IE2 |= 0x08;                     // ����3�жϴ�
}


void SendChar4(uint8 dat)
{
    S4BUF = dat;                 //д���ݵ�UART���ݼĴ���
    while(!(S4CON&S4TI));        //��ֹͣλû�з���ʱ��S4TIΪ0��һֱ�ȴ�
    S4CON&=~S4TI;                //���S4CON�Ĵ�����ӦS4TIλ����λ����������㣩
}

void SendString4(uint8 p[],uint8 len)
{
    uint8 i;
//    IE2 &= 0xEF; 			               //����4�жϹر�
    for(i=0; i<len; i++)
    {
        SendChar4(p[i]);
    }
//    IE2 |= 0x10;                     //����4�жϴ�
}

void sendData(uint8 p[])
{
    while(*p != '\0')
    {
        SBUF = *p;							//���͵�һ���ַ�
        while(!TI);							//�������ݷ�������ж�
        p++;										//��һ���ַ�
        TI = 0;									//���ͱ�־λ����
    }

}

void sendData4(uint8 p[])
{
//    IE2 &= 0xEF; 			               //����4�жϹر�
    while(*p != '\0')
    {
        S4BUF = *p;							//���͵�һ���ַ�
        while(!(S4CON&S4TI));	  //�������ݷ�������ж�
        p++;										//��һ���ַ�
        S4CON&=~S4TI;           //���S4CON�Ĵ�����ӦS4TIλ����λ����������㣩
    }
//    IE2 |= 0x10;                     //����4�жϴ�    
}


void SendEndl()
{
    SendChar1('\r');
    SendChar1('\n');
}
