

#include  "stc12.h"
#include  "gui.h"
#include  "delay.h"
#include  "tft.h"
#include  "def.h"	    		  //宏定义 常用函数
#include  "ds18b20.h"
//#include  "crastal.h"



//此数组 用于显示数字0-9    数字来着于 字符 zifu8x16.h
uint asc[10]={48,49,50,51,52,53,54,55,56,57}; 

 unsigned int t=0;

main()
{  		
	 unsigned int x,y ;
	
	Lcd_Init();   //tft初始化
	LCD_CS =0;  //打开片选使能	
 //GUI_Clear(0xffff);	//清屏	

/*==============人机界面绘制=================*/
   	GUI_Clear(0);//清屏

	GUI_box(0,0,239,15,0x001f);

//	GUI_sprintf_HZ(16, 0, 0x07ff,0x001f);//显示预定义汉字字符串	
    GUI_sprintf_hzstr16s(16,0,"新疆工程学院温度采集程序",Black,Cyan);


/*===========================================*/
TMOD=0x01;/*设置定时器0为工作方式1*/

	TH0=0x4c;/*T0重新置初值(25mS)*/
	TL0=0;

	ET0=1;/*开定时器0中断*/
	EA=1;/*开总中断*/
	TR0=1;/*启动定时器0*/
	
ReadROM();
Delay5ms();
AT24C04_WritePage();
Delay5ms();
AT24C04_ReadPage();
Delay5ms();
display00();
while(1);
}


/*---中断服务程序---*/
void Timer0_Routine(void) interrupt 1
{
    int tp;/*寄存器定义*/
	unsigned int y;
	unsigned char a;
//	unsigned int tp,y;/*寄存器定义*/
//	unsigned char x;

//	unsigned char a;
	TH0=0x4c;/*T0重新置初值(25mS)*/
	TL0=0;
	a++;
	if (a==40)/*已经发生40次中断了吗？*/
	{
		a=0;/*是，1S时间到*/
		
		GUI_sprintf_chartodec(189,302,t,0xf800,0);/* 无符号字符型数以十进制形式显示*/
		tp=read_temp();/*调用温度转换函数*/
 		if(tp>0x3fff) /*判断是否为负温，若是负温，前面显示负号*/
 		{      
 			GUI_sprintf_char(60,302, '-', 0xf800,0);/*是负温，前面显示负号*/
 			GUI_wrlval(107,302, tp&0x3fff,4,2,0xf800,0);/*写入要显示的长变量*/
 			tp=1000-tp&0x3fff;/*得到从负10度为起点的相对温度值*/
 		}
 		else
 		{      
 			GUI_sprintf_char(60,302, '+', 0xf800,0);/*是正温，前面显示正号*/
 			GUI_wrlval(107,302, tp&0x3fff,4,2,0xf800,0);/*写入要显示的长变量*/
 			tp=1000+tp&0x3fff;/*得到从负10度为起点的相对温度值*/
 		}
 		y=275-tp/20;/*计算打点位置*/



//		x=28+t;
//		GUI_Point(x, y, 0xffff);




		/*第一次测量是不准确的，不予显示*/
		if (tp<5000)
		{
			GUI_Point(t+28, y, 0xffff);//画点
			t=t+1;
			while(t==201);/*测量结束*/
		}
		 
	}
}











/*
GUI_sprintf_hzstr16s(20,50,"温度采集程序",Black,Cyan);
GUI_sprintf_hzstr16s(20,66,"当前温度值",Black,White);
GUI_sprintf_hzstr16s(101,66,":  . c",Black,White);
 while(1)
 {
 delayms(800);
  temperature=read_temp();				  //读取当前温度值 到temperature

	 GUI_sprintf_char(109,66,asc[temperature%1000/100],Red,White);	   //显示当前温度值
	 GUI_sprintf_char(117,66,asc[temperature%100/10],Red,White);
	 GUI_sprintf_char(133,66,asc[temperature%10],Red,White);
 
 }
 	
   	
}	  
*/



