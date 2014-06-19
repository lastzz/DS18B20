


#include "stc12.h"
#include "delay.h"
#include "def.h"
#include "ds18b20.h"
#include "gui.h"

//uint    c,d,e,f,g,h,i,l,c1,d1,e1,f1,g1,h1,i1,l1;
//uchar   tmp[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46}; //����0-9,A-F��ASCII��

uchar data table[8];
uchar tempL,tempH;   

//uchar sn[8];
//uchar code table[]={"0123456789ABCDEF"};                                      
									  //�����¶�ֵ��λ�͵�λ 

//uchar x,c;
//uchar  flag_get;    //�¶� ��־λ����
sbit DQ=P1^1;       //ds18b20 �˿�



// ****************DS18B20��λ����************************/
void ow_reset(void)
{

 
    DQ=1;//�Ӹ�������
    delay(200);
    DQ=0;
    delay(1000);           //550 us
    DQ=1;
    delay(1000);            //��ʱ500 us  ����DQӦ��Ϊ0 ˵����λ�ɹ� ����û������ѭ���ж� �¸���ʱ��


    DQ=1;                   //���ߵ�ƽ
}


//**********************************************************************
 // ack_ds18b20:  �ȴ�DS18B20Ӧ��
 //��     ��  ----�ȴ�DS18B20Ӧ��
 //��ڲ���:  ----��
 //���ڲ���:  ----0: û��DS18B20������������λʧ��
 //              1: ����DS18B20����
 //**********************************************************************
//unsigned char ack_ds18b20(void) 
//{ 
//	unsigned char Value=1;
//	DQ=1;; /*�ͷ����ߵȵ�����������*/
//	while(DQ==1); 
//	while(DQ==0)Value=0; 
//	/*���յ�Ӧ���ź�*/
 
//	delay(33); 
	
//	if (Value) return 0;
//	return 1;
//} 


/****************DS18B20д�����************************/
//��1-WIRE ������д1���ֽ�
void write_byte(uchar val)
{
  uchar i;
  for(i=8;i>0;i--)
  {
   DQ=1;                 //�Ӹ�������
   DQ=0;                  //5 us
   DQ=val&0x01;                           //���λ�Ƴ�
   delay(100);                              //66 us
   val=val/2;                             //����1λ 
   }
   DQ=1;
   delay(1);
}
//
/****************DS18B20��1�ֽں���************************/
//��������ȡ1���ֽ�

uchar read_byte(void)
{
    int i=0;
	unsigned int u=0;
	for (i=0;i<8;i++)
	{   
//		DQ_LOW();
        DQ=0;
//		delay2us();/*�Ӹ������͵�ƽ,������ʱ��϶,2us*/
		delay(10);
		u>>=1;
//		DQ_HIGH();
 		DQ=1;
//		delay2us();/*����ʱ����Ҫ�ӣ��������ڸ�����Ϊ���룬�źŲ��ȶ�����������ʱ���Ǵ���ֵ*/
//		delay2us();
//		delay1us();
		delay(10);
		if(DQ) u|=0x80;/*����λ*/
		delay(100);
		}
//		delay8((FOSC/1000000*56-18)/10);//56us

/*uchar i;
uchar value=0;
for(i=8;i>0;i--)
{
  DQ=1;
  value>>=1;   //value=value>>1
  DQ=0;                                           //4 us
  DQ=1;                                         //4 us
  if(DQ)value|=0x8000;
  delay(100);                                     //66 us
}
DQ=1;
*/
return(u);
}
//
/****************�����¶Ⱥ���************************/
//
uint read_temp()
{
 unsigned char a=0;
 unsigned char b=0;
//  uint tp;
    uint t;
  ow_reset();                  //���߸�λ
//  ack_ds18b20();//�ӻ�Ӧ��
//  delay(500);
  write_byte(0xcc);            //������
//  write_byte(0x44);            //��ת������
//  ow_reset();
//  delay(100);
//  write_byte(0xcc);            //������
  write_byte(0xbe);
  delay(300);    

  a=read_byte();    //���¶�ֵ�ĵ��ֽ�
  b=read_byte();    //���¶�ֵ�ĸ��ֽ�
  t=b;
 
  t <<=8;       // ��λ��0 ��0x00
  t =t |a;      // ���ֽںϳ�һ�����ͱ�����


//  tp=read_byte();

  /*-----------------------------------*/         
	if(t>0x07ff)
//	if(t>0x0fff) /*�ж��Ƿ�Ϊ���£����Ǹ��£�ȡ����һ����6.25*/
	{      
		t=~t;
		t++;
		t=(unsigned int)(t*6.25);
		t|=0xC000;
	}
	else
//		tp=tp&0x07ff
		t=(unsigned int)(t*6.25);/*������*/
	
  ow_reset();                  //���߸�λ
//  ack_ds18b20();//�ӻ�Ӧ��
 // delay(500);
  write_byte(0xcc);            //������
  write_byte(0x44);	
  return (t);
}

/*  void ReadROM(void)
{
        uint i;
        ow_reset();
        delay(100);       
        write_byte(0x33);
        delay(100);
   for(i=0;i<8;i++)
      {
	     sn[i]=readbyte();
	  } 

}

*/
 void ReadROM(void)                                                          //��ROM
{
        uint i;
        ow_reset();
        delay(100);       
        write_byte(0x33);
        delay(100);
        for(i=0;i<=7;i++)
        {
            delay(100);
                table[i]=read_byte();              
        }
}
    



/*	 void display00(void)
{
          unsigned char i,h,l;
		  unsigned char c=1;
		  for(i=0;i<8;i++)
		  {
		  l=(sn[i]&0xf0)>>4;
		  h=sn[i]&0x0f;
//		  GUI_sprintf_chartohex(20,200,(table[l]),0xf800,0);
		  GUI_sprintf_char(20,c,(table[l]),0xf800,0);
		  GUI_sprintf_char(20,c,(table[l]),0xf800,0);
		  c++;c++;
          }
}
/*	 void display00(void)
{
          unsigned char i,h,l;
		  for(i=0;i<8;i++)
		  {
		  l=ID[i]&0x0f;
		  h=ID[i]&0xf0;
		  h>>4;
		  if((h>=0x00)&&(h<=0x09))
		  	 GUI_sprintf_chartohex(20,200,(h+0x30),0xf800,0);
		  else
		     GUI_sprintf_chartohex(20,200,(h+0x37),0xf800,0);
		  if((l>=0x00)&&(l<=0x09))
		     GUI_sprintf_chartohex(60,200,(l+0x30),0xf800,0);
		  else
		   	 GUI_sprintf_chartohex(60,200,(l+0x37),0xf800,0); 
		  }



}	     


/*   void display00(void)
{
        char date1,date2;

        date1=((t&0xF0)>>4);     //ȡ���ֽڸ�4λ
        date2=t&0x0F;		     //ȡ���ֽڵ�4wei  

        if((date1>=0x00)&&(date1<=0x09))
			GUI_sprintf_chartohex(20,200,(date1+0x30),0xf800,0);
        else 					                
			GUI_sprintf_chartohex(20,200,(date1+0x37),0xf800,0);
        if((date2>=0x00)&&(date2<=0x09))
			GUI_sprintf_chartohex(20,200,(date2+0x30),0xf800,0);
        else 
	 		GUI_sprintf_chartohex(20,200,(date2+0x37),0xf800,0);	
}
*/     
 void display00(void)                                                   //��ʾ����
{
/*        uint num,tableH,tableL,i;
        uchar table0[16];
        num=0;
        while(num<16)
        {
                for(i=0;i<8;i++)
                {       
                        tableL=table[i]&0x0f;                                        //����λ
                        tableH=table[i]>>4;
                        tableH&=0x0f;                                                           //����λ
                        if((tableH<=0x09)&&(tableH>=0x00))                                                                //С�ڵ���9�Ļ�����ʾ���֣�+0x30
                        {
                                table0[num]=tableH+0x30;
                        }
                        else table0[num]=tableH+0x37;
                        num++;
                        if((tableL<=0x09)&&(tableL>=0x00))                                                               
                        {
                                table0[num]=tableL+0x30;
                        }
                        else table0[num]=tableL+0x37;                       
                        num++;
                }
        }
        //Write_com(0x80);
//        for(num=0;num<16;num++)
//        {															  */
                GUI_sprintf_char(30,220,(table[0]),0xf800,0);
				//GUI_sprintf_ZM3216s(30,220,(table[0]),0xf800,0);
				GUI_sprintf_char(40,220,(table[1]),0xf800,0);
				GUI_sprintf_char(50,220,(table[2]),0xf800,0);
				GUI_sprintf_char(60,220,(table[3]),0xf800,0);
				GUI_sprintf_char(70,220,(table[4]),0xf800,0);
				GUI_sprintf_char(80,220,(table[5]),0xf800,0);
				GUI_sprintf_char(90,220,(table[6]),0xf800,0);
				GUI_sprintf_char(100,220,(table[7]),0xf800,0);
/*				GUI_sprintf_char(110,220,(table0[8]),0xf800,0);
				GUI_sprintf_char(120,220,(table0[9]),0xf800,0);
				GUI_sprintf_char(130,220,(table0[10]),0xf800,0);
				GUI_sprintf_char(140,220,(table0[11]),0xf800,0);
				GUI_sprintf_char(150,220,(table0[12]),0xf800,0);
				GUI_sprintf_char(160,220,(table0[13]),0xf800,0);
				GUI_sprintf_char(170,220,(table0[14]),0xf800,0);
				GUI_sprintf_char(180,220,(table0[15]),0xf800,0);    */        
}

/*void get_number()               //��ȡds18b20�����к�
{
  ow_reset();
  write_byte(0x33);            //��ROM,��ds18b20��64λ���к�
  c=read_byte();              //������ȡ8���ֽڣ��ӵ�λ����λ���ζ�ȡ
  d=read_byte();
  e=read_byte();
  f=read_byte();
  g=read_byte();
  h=read_byte();
  i=read_byte();
  l=read_byte();
}

void disnumber() 
{
  char num[16]{
  tmp[(h&0xf0)>>4],
  tmp[(h&0x0f)],
  tmp[(g&0xf0)>>4],
  tmp[(g&0x0f)],
  tmp[(f&0xf0)>>4],
  tmp[(f&0x0f)],
  tmp[(e&0xf0)>>4],
  tmp[(e&0x0f)],
  tmp[(d&0xf0)>>4],
  tmp[(d&0x0f)],
  tmp[(c&0xf0)>>4],
  tmp[(c&0x0f)],
  tmp[(b&0xf0)>>4],
  tmp[(b&0x0f)],
  tmp[(a&0xf0)>>4],
  tmp[(a&0x0f)]
  }
  GUI_sprintf_hzstr16s(100,200,"100S",0x07e0,0);
}
*/



	/*-----------------------------------*/


/*  a=read_byte();    //���¶�ֵ�ĵ��ֽ�
  b=read_byte();    //���¶�ֵ�ĸ��ֽ�
  t=b;
 
  t <<=8;       // ��λ��0 ��0x00
  t =t |a;      // ���ֽںϳ�һ�����ͱ�����
  t=t>>4;       //��λ��1

  m=b;
  m<<=8;
  m=m|a;
  m=m&0x0f;
  
  t=t*10+m;
  return t;
*/
//  }



