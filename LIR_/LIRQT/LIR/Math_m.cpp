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
  volatile int i, j = 0, k = 0;
   char b1,b2,b3,b4;

//   for (i = 0;i<800;i++) mass1[i]=*(l_adr1 + i)&0xff;

//   i = 0;
//       for (int i = 0;i<8;i++)Dat[i] = 0;
//    i = 0;

while(size>=i)
  {
   b1 = *(l_adr1 + i);
   i++;
   b2 = *(l_adr1 + i);
   i++;
   b3 = *(l_adr1 + i);
   i++;
   b4 = *(l_adr1 + i);
   i++;
  Datint[k] = AngCalc(b1,b2,b3,b4);
  Dat[j] +=Datint[k];
  // Dat[j] +=(((b4&0xff)<<24)|((b3&0xff)<<16)|((b2&0xff)<<8)|(b1&0xff))&0xffffffff;//считаем среднее значение каждого параметра
  // Datint[k] =(((b4&0xff)<<24)|((b3&0xff)<<16)|((b2&0xff)<<8)|(b1&0xff))&0xffffffff;//записываем int

   j++;
   k++;
   if (j == n) j = 0;
  }

   for(i = 0;i<n;i++) Dat[i]/=size/(n*4);
   //void *adr1 = &Dat[0];
   void *adr2 = &Datint[0];
   UpLCD( adr2,  size/4);
   SaveFile_s(adr2, size/4, n);
   if(f_plot) MakePlotDat(adr2,size/4,n_Line);
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


     n+=1;

     size-=1;


    }
adr = &PlotDat[0];
 SandPlotDat(adr, num1,max*360/(1<<24));

}
void Math_m::StartStopPlot(bool f,int n)
{
    f_plot = f;
    n_Line = n;

}

int Math_m::AngCalc(char dat0, char dat1,char dat2,char dat3)
{
    int i1 = (unsigned char)dat0 + ((unsigned char)dat1<<8) + ((unsigned char)dat2<<16) + ((unsigned char)dat3<<24);


//Ang_Lir=("%03d\xB0 %02d' %02d\"",ig,im,is);
       // str.append("%03d\xB0 %02d' %02d\"",ig,im,is);

    return i1;

}
