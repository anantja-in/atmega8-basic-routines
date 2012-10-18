#include<avr/io.h>
#include"inter_integrated.h"
main()
{
   unsigned  char b[10];
   unsigned char str[20];
   unsigned char k;
   char m;
   write_rtc();
   read_rtc(*a);
   sprintf(str,"%d%d%d%d%d%d",b[0],b[1],b[2],b[3],b[4],b[5],b[6]);
   for(m=0;m<=5;m++)
   for(k=0;k<=65000;k++);
   uart1_tx_string(str);
 }  