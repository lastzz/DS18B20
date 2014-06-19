


#include "stc12.h"
#include "delay.h"
#include "def.h"
#include "ds18b20.h"
#include "gui.h"

//uint    c,d,e,f,g,h,i,l,c1,d1,e1,f1,g1,h1,i1,l1;
//uchar   tmp[]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46}; //数字0-9,A-F的ASCII码

uchar data table[8];
uchar tempL,tempH;   

//uchar sn[8];
//uchar code table[]={"0123456789ABCDEF"};                                      
									  //设置温度值高位和低位 

//uchar x,c;
//uchar  flag_get;    //温度 标志位函数
sbit DQ=P1^1;       //ds18b20 端口



// ****************DS18B20复位函数************************/
void ow_reset(void)
{

 
    DQ=1;//从高拉倒低
    delay(200);
    DQ=0;
    delay(1000);           //550 us
    DQ=1;
    delay(1000);            //延时500 us  这是DQ应该为0 说明复位成功 这里没有用死循环判断 怕干扰时钟


    DQ=1;                   //拉高电平
}


//**********************************************************************
 // ack_ds18b20:  等待DS18B20应答
 //功     能  ----等待DS18B20应答
 //入口参数:  ----无
 //出口参数:  ----0: 没有DS18B20器件或主机复位失败
 //              1: 发现DS18B20器件
 //**********************************************************************
//unsigned char ack_ds18b20(void) 
//{ 
//	unsigned char Value=1;
//	DQ=1;; /*释放总线等电阻拉高总线*/
//	while(DQ==1); 
//	while(DQ==0)Value=0; 
//	/*接收到应答信号*/
 
//	delay(33); 
	
//	if (Value) return 0;
//	return 1;
//} 


/****************DS18B20写命令函数************************/
//向1-WIRE 总线上写1个字节
void write_byte(uchar val)
{
  uchar i;
  for(i=8;i>0;i--)
  {
   DQ=1;                 //从高拉倒低
   DQ=0;                  //5 us
   DQ=val&0x01;                           //最低位移出
   delay(100);                              //66 us
   val=val/2;                             //右移1位 
   }
   DQ=1;
   delay(1);
}
//
/****************DS18B20读1字节函数************************/
//从总线上取1个字节

uchar read_byte(void)
{
    int i=0;
	unsigned int u=0;
	for (i=0;i<8;i++)
	{   
//		DQ_LOW();
        DQ=0;
//		delay2us();/*从高拉至低电平,产生读时间隙,2us*/
		delay(10);
		u>>=1;
//		DQ_HIGH();
 		DQ=1;
//		delay2us();/*此延时必须要加，否则由于刚设置为输入，信号不稳定，立即读入时会是错误值*/
//		delay2us();
//		delay1us();
		delay(10);
		if(DQ) u|=0x80;/*读入位*/
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
/****************读出温度函数************************/
//
uint read_temp()
{
 unsigned char a=0;
 unsigned char b=0;
//  uint tp;
    uint t;
  ow_reset();                  //总线复位
//  ack_ds18b20();//从机应答
//  delay(500);
  write_byte(0xcc);            //发命令
//  write_byte(0x44);            //发转换命令
//  ow_reset();
//  delay(100);
//  write_byte(0xcc);            //发命令
  write_byte(0xbe);
  delay(300);    

  a=read_byte();    //读温度值的第字节
  b=read_byte();    //读温度值的高字节
  t=b;
 
  t <<=8;       // 低位补0 即0x00
  t =t |a;      // 两字节合成一个整型变量。


//  tp=read_byte();

  /*-----------------------------------*/         
	if(t>0x07ff)
//	if(t>0x0fff) /*判断是否为负温，若是负温，取反加一，乘6.25*/
	{      
		t=~t;
		t++;
		t=(unsigned int)(t*6.25);
		t|=0xC000;
	}
	else
//		tp=tp&0x07ff
		t=(unsigned int)(t*6.25);/*是正温*/
	
  ow_reset();                  //总线复位
//  ack_ds18b20();//从机应答
 // delay(500);
  write_byte(0xcc);            //发命令
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
 void ReadROM(void)                                                          //读ROM
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

        date1=((t&0xF0)>>4);     //取出字节高4位
        date2=t&0x0F;		     //取出字节低4wei  

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
 void display00(void)                                                   //显示函数
{
/*        uint num,tableH,tableL,i;
        uchar table0[16];
        num=0;
        while(num<16)
        {
                for(i=0;i<8;i++)
                {       
                        tableL=table[i]&0x0f;                                        //低四位
                        tableH=table[i]>>4;
                        tableH&=0x0f;                                                           //高四位
                        if((tableH<=0x09)&&(tableH>=0x00))                                                                //小于等于9的话，显示数字，+0x30
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

/*void get_number()               //读取ds18b20的序列号
{
  ow_reset();
  write_byte(0x33);            //读ROM,读ds18b20的64位序列号
  c=read_byte();              //连续读取8个字节，从低位到高位依次读取
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


/*  a=read_byte();    //读温度值的第字节
  b=read_byte();    //读温度值的高字节
  t=b;
 
  t <<=8;       // 低位补0 即0x00
  t =t |a;      // 两字节合成一个整型变量。
  t=t>>4;       //高位补1

  m=b;
  m<<=8;
  m=m|a;
  m=m&0x0f;
  
  t=t*10+m;
  return t;
*/
//  }



