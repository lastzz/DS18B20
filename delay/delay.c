

#include "stc12.h"
#include "delay.h"
#include <intrins.h>

void delayms(unsigned int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
} 



void delay(unsigned int time)
{
	while(--time);
}


