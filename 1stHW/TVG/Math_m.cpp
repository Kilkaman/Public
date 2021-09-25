#include "Math_m.h"

#include <qdebug.h>

//
Math_m::Math_m(QObject *parent) :
    QObject(parent)
{


}

Math_m::~Math_m()
{
    qDebug("By in Thread!");
}

void Math_m::MakeIntmass (void* adr, int size, int n )
{
   char* l_adr1;
   l_adr1 = (char*) adr;
   int i, j = 0, k = 0;
   char b1,b2;

   for (i = 0;i<800;i++) mass1[i]=*(l_adr1 + i)&0xff;

   i = 0;
       for (int i = 0;i<8;i++)Dat[i] = 0;
    i = 0;

while(size>i)
  {
   b1 = *(l_adr1 + i);
   i++;
   b2 = *(l_adr1 + i);
   i++;

   Dat[j] +=(((b2&0xff)<<8)|(b1&0xff))&0xffff;//считаем среднее значение каждого параметра
   Datint[k] = (((b2&0xff)<<8)|(b1&0xff))&0xffff;
   j++;
   k++;
   if (j == n) j = 0;
  }

   for(i = 0;i<n;i++) Dat[i]/=size/(n*2);
   void *adr1 = &Dat[0];
   void *adr2 = &Datint[0];
   UpLCD( adr1,  n);
   SaveFile_s(adr2, size/2, n);
   if(f_plot) MakePlotDat(adr2,size/2,n_Line);
   i = 0;
}
void Math_m::MakePlotDat(void *adr, int size, int n)
{
    int* adr1 = (int*) adr;
    int   num1 = 0 ;
    int max = 0;
    while (size>0) {
     //if((num&0x7) == (n-1))

        PlotDat[num1] = *(adr1 + n );
        if (PlotDat[num1]>max) max = PlotDat[num1];
        num1++;


     n+=7;

     size-=7;


    }
adr = &PlotDat[0];
 SandPlotDat(adr, num1, max);

}
void Math_m::StartStopPlot(bool f,int n)
{
    f_plot = f;
    n_Line = n;

}
