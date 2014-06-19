

#include  "stc12.h"
#include  "gui.h"
#include  "delay.h"
#include  "tft.h"
#include  "def.h"	    		  //�궨�� ���ú���
#include  "ds18b20.h"
//#include  "crastal.h"



//������ ������ʾ����0-9    ���������� �ַ� zifu8x16.h
uint asc[10]={48,49,50,51,52,53,54,55,56,57}; 

 unsigned int t=0;

main()
{  		
	 unsigned int x,y ;
	
	Lcd_Init();   //tft��ʼ��
	LCD_CS =0;  //��Ƭѡʹ��	
 //GUI_Clear(0xffff);	//����	

/*==============�˻��������=================*/
   	GUI_Clear(0);//����

	GUI_box(0,0,239,15,0x001f);

//	GUI_sprintf_HZ(16, 0, 0x07ff,0x001f);//��ʾԤ���庺���ַ���	
    GUI_sprintf_hzstr16s(16,0,"�½�����ѧԺ�¶Ȳɼ�����",Black,Cyan);


/*===========================================*/
TMOD=0x01;/*���ö�ʱ��0Ϊ������ʽ1*/

	TH0=0x4c;/*T0�����ó�ֵ(25mS)*/
	TL0=0;

	ET0=1;/*����ʱ��0�ж�*/
	EA=1;/*�����ж�*/
	TR0=1;/*������ʱ��0*/
	
ReadROM();
Delay5ms();
AT24C04_WritePage();
Delay5ms();
AT24C04_ReadPage();
Delay5ms();
display00();
while(1);
}


/*---�жϷ������---*/
void Timer0_Routine(void) interrupt 1
{
    int tp;/*�Ĵ�������*/
	unsigned int y;
	unsigned char a;
//	unsigned int tp,y;/*�Ĵ�������*/
//	unsigned char x;

//	unsigned char a;
	TH0=0x4c;/*T0�����ó�ֵ(25mS)*/
	TL0=0;
	a++;
	if (a==40)/*�Ѿ�����40���ж�����*/
	{
		a=0;/*�ǣ�1Sʱ�䵽*/
		
		GUI_sprintf_chartodec(189,302,t,0xf800,0);/* �޷����ַ�������ʮ������ʽ��ʾ*/
		tp=read_temp();/*�����¶�ת������*/
 		if(tp>0x3fff) /*�ж��Ƿ�Ϊ���£����Ǹ��£�ǰ����ʾ����*/
 		{      
 			GUI_sprintf_char(60,302, '-', 0xf800,0);/*�Ǹ��£�ǰ����ʾ����*/
 			GUI_wrlval(107,302, tp&0x3fff,4,2,0xf800,0);/*д��Ҫ��ʾ�ĳ�����*/
 			tp=1000-tp&0x3fff;/*�õ��Ӹ�10��Ϊ��������¶�ֵ*/
 		}
 		else
 		{      
 			GUI_sprintf_char(60,302, '+', 0xf800,0);/*�����£�ǰ����ʾ����*/
 			GUI_wrlval(107,302, tp&0x3fff,4,2,0xf800,0);/*д��Ҫ��ʾ�ĳ�����*/
 			tp=1000+tp&0x3fff;/*�õ��Ӹ�10��Ϊ��������¶�ֵ*/
 		}
 		y=275-tp/20;/*������λ��*/



//		x=28+t;
//		GUI_Point(x, y, 0xffff);




		/*��һ�β����ǲ�׼ȷ�ģ�������ʾ*/
		if (tp<5000)
		{
			GUI_Point(t+28, y, 0xffff);//����
			t=t+1;
			while(t==201);/*��������*/
		}
		 
	}
}











/*
GUI_sprintf_hzstr16s(20,50,"�¶Ȳɼ�����",Black,Cyan);
GUI_sprintf_hzstr16s(20,66,"��ǰ�¶�ֵ",Black,White);
GUI_sprintf_hzstr16s(101,66,":  . c",Black,White);
 while(1)
 {
 delayms(800);
  temperature=read_temp();				  //��ȡ��ǰ�¶�ֵ ��temperature

	 GUI_sprintf_char(109,66,asc[temperature%1000/100],Red,White);	   //��ʾ��ǰ�¶�ֵ
	 GUI_sprintf_char(117,66,asc[temperature%100/10],Red,White);
	 GUI_sprintf_char(133,66,asc[temperature%10],Red,White);
 
 }
 	
   	
}	  
*/



