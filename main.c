#include "Uart.c"
#include "LCD.c"
#include "main.h"

void deal_data()//GPSRMC数据长度72
{
    uchar i=0,j=0,k=0;//i循环用 j计算有几个‘,’ k为赋值用下标
    uint s=0;
    for(i=0; i<72; i++)
    {
        if(GPSRMC[i]==',')
        {
            i++;
            j++;
        }
        switch(j)
        {
        case 1://UTC_time
            if(k<10)
            {
                if(k<2)
                {
                    hour[k]=GPSRMC[i];
                }
                else if(k<4)
                {
                    minute[k-2]=GPSRMC[i];
                }
                else sec[k-4]=GPSRMC[i];
//                UTC_time[k]=GPSRMC[i];
                k++;
            }
            break;
        case 2://A有效定位 V无效定位
            k=0;
            valid=GPSRMC[i];
            break;
        case 3://纬度
            if(k<9)
            {
                if(k<2)latitude_d[k]=GPSRMC[i];
                else latitude_m[k-2]=GPSRMC[i];
//                latitude[k]=GPSRMC[i];
                k++;
            }
            break;
        case 4://N or S
//            latitude[k]=GPSRMC[i];
            NS=GPSRMC[i];
            k=0;
            break;
        case 5://经度
            if(k<10)
            {
                if(k<3)longitude_d[k]=GPSRMC[i];
                else longitude_m[k-3]=GPSRMC[i];
//                longitude[k]=GPSRMC[i];
                k++;
            }
            break;
        case 6://E or W
//            longitude[k]=GPSRMC[i];
            WE=GPSRMC[i];
            k=0;
            break;
        case 9://UTC_date
            if(k<6)
            {
                if(k<2)day[k]=GPSRMC[i];
                else if(k<4)month[k-2]=GPSRMC[i];
                else year[k-2]=GPSRMC[i];
//                UTC_date[k]=GPSRMC[i];
                k++;
            }
            break;
        default:
            break;
        }
    }
    sscanf(hour,"%u",&s);
    s+=8;
    sprintf(hour,"%u",s);
}

void SendAirQuality()
{
    sendData("--------------AirQuality--------------\r\n");
    sendData("Checksum:");
    sendData(cChecksum);
    sendData("  ==  ");
    sendData("CalChecksum:");
    sendData(cCalChecksum);
    SendEndl();
    sendData("FrameLen:");
    sendData(cFrameLen);
    SendEndl();
    sendData("PM1_0CF1:");
    sendData(cPM1_0CF1);
    SendEndl();
    sendData("PM2_5CF1:");
    sendData(cPM2_5CF1);
    SendEndl();
    sendData("PM10CF1:");
    sendData(cPM10CF1);
    SendEndl();
    sendData("PM1_0AE:");
    sendData(cPM1_0AE);
    SendEndl();
    sendData("PM2_5AE:");
    sendData(cPM2_5AE);
    SendEndl();
    sendData("PM10AE:");
    sendData(cPM10AE);
    SendEndl();
    sendData("Gt0_3um:");
    sendData(cGt0_3um);
    SendEndl();
    sendData("Gt0_5um:");
    sendData(cGt0_5um);
    SendEndl();
    sendData("Gt1_0um:");
    sendData(cGt1_0um);
    SendEndl();
    sendData("Gt2_5um:");
    sendData(cGt2_5um);
    SendEndl();
    sendData("Gt5_0um:");
    sendData(cGt5_0um);
    SendEndl();
    sendData("Gt10um:");
    sendData(cGt10um);
    SendEndl();
    sendData("Version:");
    SendChar1(Version+'0');
    SendEndl();
    sendData("ErrorCode:");
    SendChar1(ErrorCode+'0');
    SendEndl();
    sendData("-------------------END-------------------\r\n");
}

void ESP_SendGPS()
{
    sprintf(ESP_UP_DATA,GPS_data1,year,month,day);
    sprintf(ESP_UP_DATA,GPS_data2,ESP_UP_DATA,latitude_d,latitude_m);
    sprintf(ESP_UP_DATA,GPS_data3,ESP_UP_DATA,longitude_d,longitude_m);
    sprintf(ESP_UP_DATA,GPS_data4,ESP_UP_DATA,hour,minute);
    sprintf(ESP_UP_DATA,GPS_data5,ESP_UP_DATA,sec,"gps");
    sendData4(ESP_UP_DATA);
//    sendData(ESP_UP_DATA);
    ESP8266=2;
}

void ESP_SendAIR()
{
    sprintf(ESP_UP_DATA,Air_data1,"pms7003",cPM1_0CF1,cPM2_5CF1);
    sprintf(ESP_UP_DATA,Air_data2,ESP_UP_DATA,cPM10CF1,cPM1_0AE);
    sprintf(ESP_UP_DATA,Air_data3,ESP_UP_DATA,cPM2_5AE,cPM10AE);
    sprintf(ESP_UP_DATA,Air_data4,ESP_UP_DATA,cGt0_3um,cGt0_5um);
    sprintf(ESP_UP_DATA,Air_data5,ESP_UP_DATA,cGt1_0um,cGt2_5um);
    sprintf(ESP_UP_DATA,Air_data6,ESP_UP_DATA,cGt5_0um,cGt10um);
    sendData4(ESP_UP_DATA);
//    sendData(ESP_UP_DATA);
    ESP8266=3;
}

void DisPlay_LCD()
{
    switch(Touch)
    {
    case -1:
        return;
        break;

    case 0:
        DispS(1,0,"****设备状况****");

        if(ATK_GPS==3)DispS(2,0,"ATK_GPS:Normal  ");
        else if(ATK_GPS==2)DispS(2,0,"ATK_GPS:Error   ");
        else if(ATK_GPS==1)DispS(2,0,"ATK_GPS:Wait    ");
        else DispS(2,0,"ATK_GPS:未接入  ");

        if(Pms7003==3)DispS(3,0,"Pms7003:Normal  ");
        else if(Pms7003==2)DispS(3,0,"Pms7003:Error   ");
        else if(Pms7003==1)DispS(3,0,"Pms7003:Wait    ");
        else DispS(3,0,"Pms7003:未接入  ");

        if(ESP8266==1)DispS(4,0,"ESP8266:已接入  ");
        else if(ESP8266==2)DispS(4,0,"ESP8266:SendGPS ");
        else if(ESP8266==3)DispS(4,0,"ESP8266:SendAir ");
        else (4,0,"ESP8266:Wait    ");

        break;
    case 1:
        DispS(1,0,"ug/m3 ATEN  CF=1");
        DispS(2,0,"PM1.0:");
        sprintf(strTemp, "%-4.4s%2s%4.4s",cPM1_0AE,"//",cPM1_0CF1);
        DispS(2,3,strTemp);
        DispS(3,0,"PM2.5:");
        sprintf(strTemp, "%-4.4s%2s%4.4s",cPM2_5AE,"//",cPM2_5CF1);
        DispS(3,3,strTemp);
        DispS(4,0,"PM10 :");
        sprintf(strTemp, "%-4.4s%2s%4.4s",cPM10AE,"//",cPM10CF1);
        DispS(4,3,strTemp);
        break;
    case 2:
        DispS(1,0,"**um in 0.1L Air");
        sprintf(strTemp, "%5s%-5.5s%4s","G0.3:",cGt0_3um,"G10:");
        sprintf(strTemp, "%s%-2.2s",strTemp,cGt10um);
        DispS(2,0,strTemp);
        sprintf(strTemp, "%5s%-5.5s%3s","G0.5:",cGt0_5um,"G5:");
        sprintf(strTemp, "%s%-3.3s",strTemp,cGt5_0um);
        DispS(3,0,strTemp);
        sprintf(strTemp, "%5s%-4.4s%3s","G2.5:",cGt2_5um,"G1:");
        sprintf(strTemp, "%s%-4.4s",strTemp,cGt1_0um);
        DispS(4,0,strTemp);
        break;
    case 3:
        sprintf(strTemp,"%4.4s年%2.2s月%2.2s日",year,month,day);
        sprintf(strTemp,"%14.14s %c",strTemp,valid);
        DispS(1,0,strTemp);
        sprintf(strTemp,"U+8 %2.2s:%2.2s:%6.6s",hour,minute,sec);
        DispS(2,0,strTemp);
        sprintf(strTemp,"%4s%2s%7.7s",latitude_d,"°",latitude_m);
        sprintf(strTemp,"%13.13s%1s %c",strTemp,"'",NS);
        DispS(3,0,strTemp);
        sprintf(strTemp,"%4s%2s%7.7s",longitude_d,"°",longitude_m);
        sprintf(strTemp,"%13.13s%1s %c",strTemp,"'",WE);
        DispS(4,0,strTemp);
        break;
    default:
        break;
    }

}

//void TM0() interrupt 1
//{
//    cnt++;        //5ms进入1次中断
//    if(cnt == 200)      //200次中断被响应后，正好1000ms
//    {
//      led = ~led;       //将指示灯取反更换亮灭状态
//      cnt = 0;
//    }
//    //进入中断时会将定时器中断溢出标志位硬件清零，因此下面一句可以不加的
//    TF0 = 0;             //清除T0中断溢出标志位
//}

void INT1() interrupt 2
{
    if(Touch==-1)Touch=0;
    else 
    {
      Touch=-1;
      DispS(1,0,"****************");
      DispS(2,0,"**LCD12864关闭**");
      DispS(3,0,"**    INT1    **");
      DispS(4,0,"****************");
    }
}

void INT3() interrupt 11
{
    if(Touch==-1)return;
    else if(Touch==3)Touch=0;
    else Touch++;
    DisPlay_LCD();
//    SendChar1(Touch+'0');
}

void main()
{
    UartInit1();
    UartInit2();
    UartInit3();
    UartInit4();
//    Timer0Init();
    Init_Lcd();
    IE1  = 0;	     //将INT1中断请求标志位清"0"
    EX1 = 1;	     //使能INT1中断允许位
    IT1 = 1;		   //选择INT1为下降沿触发方式
    INTCLKO |= 0x20;   //使能INT3中断允许位 P3.7 下降沿中断方式
    while(1)
    {


    }
    
}

void Uart1() interrupt 4 using 1
{
    //strncpy函数字符串截取(原函数,截取的函数,多少)
    //WifiAPMode
    static uchar i=0;
    uchar temp;
    if (RI)                       //串行接收到停止位的中间时刻时，该位置1
    {
        RI = 0;                   //清除RI位 （该位必须软件清零）
        temp=SBUF;
        Rec[i] = temp;
//        if(Com1==1)SendChar1(temp);
        i++;
        if(i>5)
        {
            i=0;
        }
        if(temp=='\n')
        {
            Cmd[0]=Rec[0];
            Cmd[1]=Rec[1];
            Cmd[2]=Rec[2];
            if(strcmp(Cmd,"M01")==0)
            {
                if(Com1!=1)
                {
                    Com1=1;
                    SendString1("COM1-ON\r\n",9);
                }
                else
                {
                    Com1=0;
                    SendString1("COM1-OFF\r\n",10);
                }
            }
            else if(strcmp(Cmd,"M02")==0)
            {
                if(Com2!=1)
                {
                    Com2=1;
                    SendString1("COM2-ON\r\n",9);
                }
                else
                {
                    Com2=0;
                    SendString1("COM2-OFF\r\n",10);
                }
            }
            else if(strcmp(Cmd,"M03")==0)
            {
                if(Com3!=1)
                {
                    Com3=1;
                    SendString1("COM3-ON\r\n",9);
                }
                else
                {
                    Com3=0;
                    SendString1("COM3-OFF\r\n",10);
                }
            }
            else if(strcmp(Cmd,"M04")==0)
            {
                if(Com4!=1)
                {
                    Com4=1;
                    SendString1("COM4-ON\r\n",9);
                }
                else
                {
                    Com4=0;
                    SendString1("COM4-OFF\r\n",10);
                }
            }
            else if(strcmp(Cmd,"M05")==0)
            {
                if(Com2!=2)
                {
                    Com2=2;
                    sendData("GPS-ON\r\n");
                }
                else
                {
                    Com2=0;
                    sendData("GPS-OFF\r\n");
                }
            }
            else if(strcmp(Cmd,"M06")==0)
            {
                if(Com3!=2)
                {
                    Com3=2;
                    sendData("AirQuality-ON\r\n");
                }
                else
                {
                    Com3=0;
                    sendData("AirQuality-OFF\r\n");
                }
            }
            else if(strcmp(Cmd,"M07")==0)
            {
                if(Touch==-1)
                {
                    Touch=0;
                    sendData("LCD-ON\r\n");
                }
                else
                {
                    Touch=-1;
                    DispS(1,0,"****************");
                    DispS(2,0,"**LCD12864关闭**");
                    DispS(3,0,"**发送 M07开启**");
                    DispS(4,0,"****************");
                    sendData("LCD-OFF\r\n");
                }
            }
            else
            {
                sendData("Error\r\n");
                sendData(Cmd);
                SendEndl();
            }
            i=0;
        }

    }
}

void Uart2() interrupt 8 using 1
{
    static uchar m=0;
    uchar temp;
    if (S2CON & S2RI)                //串行接收到停止位的中间时刻时，该位置1
    {
        S2CON &= ~S2RI;              //清除S2CON寄存器对应S2RI位（该位必须软件清零）
        temp=S2BUF;
        if(m==0&&temp=='$')
        {

            GPSRMC[m]=temp;
            Calsum=0;
            m++;
        }
        else if(temp=='\r'&&m!=70)
        {
            m=0;
            Calsum=0;
        }
        else if(temp=='\n'&&m!=71)
        {
            m=0;
            Calsum=0;
        }
        else if(m<67)
        {
            GPSRMC[m]=temp;
            Calsum^=temp;
            m++;
        }
        else if(m==68||m==69)
        {
            GPSRMC[m]=temp;
            Chesum[m-68]=GPSRMC[m];
            m++;
        }
        else
        {
            GPSRMC[m]=temp;
            m++;
        }

        if(m>=72)
        {
            m=0;
            if(Com2==1)sendData(GPSRMC);
            sprintf(cCalsum,"%X",Calsum);
            if(strcmp(Chesum,cCalsum)==0)
            {
                if(Com2==2)sendData(GPSRMC);
                deal_data();
                ESP_SendGPS();
                ATK_GPS=3;
            }
            else
            {
                ATK_GPS=2;
                sendData("GPSERROR\r\n");
                sendData(Chesum);
                SendEndl();
                sendData(cCalsum);
                SendEndl();
            }
            DisPlay_LCD();
            ESP8266=0;
            ATK_GPS=1;
            Calsum=0;
        }

    }
}

void Uart3() interrupt 17 using 1
{
    static uint j=0;
    uint val;
    uint temp;
    if (S3CON & S3RI)                          //串行接收到停止位的中间时刻时，该位置1
    {
        S3CON &= ~S3RI;                        //清除S3CON寄存器对应S3RI位（该位必须软件清零）
        temp=S3BUF;
        if(Com3==1)SendChar1(temp);
        if(j==0)
        {
            if(temp==0x42)
            {
                AirSensor[j]=temp;
                CalChecksum = 0x42;
                j++;

            }
            else j=0;
        }
        else if(j==1)
        {
            if(temp==0x4d)
            {
                AirSensor[j]=temp;
                CalChecksum += 0x4d;
                j++;

            }
            else j=0;
        }
        else if(j>=2)
        {
            AirSensor[j]=temp;
            if(j<30)CalChecksum+=temp;
            j++;
            val=AirSensor[j-1]+(AirSensor[j-2]<<8);
            switch(j)
            {
            case 4:
                FrameLen= val+j;
                sprintf(cFrameLen, "%u",FrameLen);
                break;
            case 6:
                PM1_0CF1 = val;
                sprintf(cPM1_0CF1, "%u",PM1_0CF1);
                break;
            case 8:
                PM2_5CF1 = val;
                sprintf(cPM2_5CF1, "%u",PM2_5CF1);
                break;
            case 10:
                PM10CF1 = val;
                sprintf(cPM10CF1, "%u",PM10CF1);
                break;
            case 12:
                PM1_0AE = val;
                sprintf(cPM1_0AE, "%u",PM1_0AE);
                break;
            case 14:
                PM2_5AE = val;
                sprintf(cPM2_5AE, "%u",PM2_5AE);
                break;
            case 16:
                PM10AE = val;
                sprintf(cPM10AE, "%u",PM10AE);
                break;
            case 18:
                Gt0_3um = val;
                sprintf(cGt0_3um, "%u",Gt0_3um);
                break;
            case 20:
                Gt0_5um = val;
                sprintf(cGt0_5um, "%u",Gt0_5um);
                break;
            case 22:
                Gt1_0um = val;
                sprintf(cGt1_0um, "%u",Gt1_0um);
                break;
            case 24:
                Gt2_5um = val;
                sprintf(cGt2_5um, "%u",Gt2_5um);
                break;
            case 26:
                Gt5_0um = val;
                sprintf(cGt5_0um, "%u",Gt5_0um);
                break;
            case 28:
                Gt10um = val;
                sprintf(cGt10um, "%u",Gt10um);
                break;
            case 29:
                val= AirSensor[j-1];
                Version = val;
                break;
            case 30:
                val= AirSensor[j-1];
                ErrorCode = val;
                break;
            case 32:
                j=0;
                Checksum = val;
                sprintf(cChecksum, "%u",Checksum);
                sprintf(cCalChecksum, "%u",CalChecksum);
                if(Checksum==CalChecksum)
                {
                    if(Com3==2)SendAirQuality();
                    ESP_SendAIR();
                    Pms7003=3;
                }
                else
                {
                    Pms7003=2;
                    sendData("AirERROR\r\n");
                    sendData(cChecksum);
                    SendEndl();
                    sendData(cCalChecksum);
                    SendEndl();
                }
                DisPlay_LCD();
                ESP8266=0;
                Pms7003=1;
                break;
            default:
                break;
            }
        }
        else j=0;
    }
}

void Uart4() interrupt 18 using 1
{
    static uchar n=0;
    uchar temp;
    if(S4CON & S4RI)           //串行接收到停止位的中间时刻时，该位置1
    {
        S4CON &= ~S4RI;	         //清除S4CON寄存器对应S4RI位（该位必须软件清零）
        temp=S4BUF;
//        ESP[n]=temp;
        ESP8266=1;
        n++;
        if(Com4==1)SendChar1(temp);
//        if(temp=='\n'||n>=100)
//        {
//
//            n=0;
//        }


    }
}