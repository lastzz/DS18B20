/**************************************
AT24C04读写函数
主芯片  : STC12C5A60S2 (1T)
工作频率: 12.000MHz
**************************************/
#include "INTRINS.H"
#include "STC12.h"
#include "DS18B20.H"
//#include "ds18b20.c"

typedef unsigned char BYTE;
typedef unsigned short WORD;
extern unsigned char data table[8];



sbit SCL = P1^3;                //AT24C04的时钟
sbit SDA = P1^4;                //AT24C04的数据
//sbit STATUS=P4^6;
//P4M0=0x00;
//P4M1=0x00;
//P4M1=0x00;//P4.1 P4.4 P4.5 P4.6推挽
//P4M0=0x72;	
//P4SW=0x70;//P4.4=I/O P4.5=I/O P4.6=I/O	


BYTE BUF[8];                   //数据缓存区

/*BYTE code TESTDATA[] =
{
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
};
*/
void Delay5us();
void Delay5ms();
void AT24C04_Start();
void AT24C04_Stop();
void AT24C04_SendACK(bit ack);
bit AT24C04_RecvACK();
void AT24C04_SendByte(BYTE dat);
BYTE AT24C04_RecvByte();
void AT24C04_ReadPage();
void AT24C04_WritePage();


/**************************************
向AT24C04写1页(8字节)数据
将TESTDATA开始的16个测试数据写如设备的00~0F地址中
**************************************/
void AT24C04_WritePage()
{
    BYTE i;

    AT24C04_Start();            //起始信号
    AT24C04_SendByte(0xa0);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);     //发送存储单元地址
    for (i=0; i<8; i++)
    {
        AT24C04_SendByte(table[i]);
    }
    AT24C04_Stop();             //停止信号
}

/**************************************
从AT24C04读取1页(8字节)数据
将设备的00~0F地址中的数据读出存放在DATA区的BUF中
**************************************/
void AT24C04_ReadPage()
{
    BYTE i;

    AT24C04_Start();            //起始信号
    AT24C04_SendByte(0xa0);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);     //发送存储单元地址
    AT24C04_Start();            //起始信号
    AT24C04_SendByte(0xa1);     //发送设备地址+读信号
    for (i=0; i<8; i++)
    {
        BUF[i] = AT24C04_RecvByte();
        if (i == 7)
        {
            AT24C04_SendACK(1); //最后一个数据需要会NAK
        }
        else
        {
            AT24C04_SendACK(0); //回应ACK
        }
    }
    AT24C04_Stop();             //停止信号
}

/**************************************
延时5微秒(STC12C5A60S2@12M)
不同的工作环境,需要调整此函数
此延时函数是使用1T的指令周期进行计算,与传统的12T的MCU不同
**************************************/
void Delay5us()
{
    BYTE n = 4;

    while (n--)
    {
        _nop_();
        _nop_();
    }
}

/**************************************
延时5毫秒(STC12C5A60S2@12M)
不同的工作环境,需要调整此函数
此延时函数是使用1T的指令周期进行计算,与传统的12T的MCU不同
**************************************/
void Delay5ms()
{
    WORD n = 2500;

    while (n--)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

/**************************************
起始信号
**************************************/
void AT24C04_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void AT24C04_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit AT24C04_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void AT24C04_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    AT24C04_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE AT24C04_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }

    return dat;
}
