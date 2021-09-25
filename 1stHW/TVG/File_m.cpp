#include "File_m.h"

#include <qdebug.h>

//
File_m::File_m(QObject *parent) :
    QObject(parent)
{


}

File_m::~File_m()
{
    qDebug("By in Thread!");
}

void File_m::SaveFile(void* adr, int size, int n)
{
    if (m_save)
    {
 bool open ;
 if ((len>=10000000)|(len == 0)) open = 1;
 else  open = 0;

if(open){
s_time = m_time.currentTime().toString();
s_time ="_"+s_time+".txt";
s_time[3] = s_time[0];
s_time[6] = s_time[0];
len = 0;
}
QFile file1(name0+s_time);
QTextStream out(&file1);
if(open)file1.open(QIODevice::WriteOnly|QIODevice::Text);
else file1.open(QIODevice::Append|QIODevice::Text);

if (file1.exists())
{
   int* l_adr1;
    l_adr1 = (int*) adr;
    int i = 0, j = 0;

   int dat;

    while(size>i)
      {
       dat = *(l_adr1 + i);
       out<<dat<<"\t";
       i++;
       j++;
       if (j == n)
       {
         out <<"\n";
         j = 0;
       }
     }
    //out <<"\n";
 file1.close();
 len +=size;
  }
    }

}

void File_m::SaveOnOff(bool f_save)
{
    m_save = f_save;
    if (!f_save) len = 0;
}
void File_m::GetName(QString name)
{
    name0 = name;
}
