#include "MyPort.h"

#include <qdebug.h>

//
Port::Port(QObject *parent) :
    QObject(parent)
{
}

Port::~Port()
{
    qDebug("By in Thread!");
}
void Port::Write_Settings_Port(QString name)//setup COM port
{

   qDebug() << "Setting " ;
   thisPort.clear();
   thisPort.close();
   thisPort.setPortName(name);
   thisPort.setBaudRate(460800);
   thisPort.setDataBits(QSerialPort::Data8);
   thisPort.setParity(QSerialPort::NoParity);
   thisPort.setStopBits(QSerialPort::OneStop);
   thisPort.setFlowControl(QSerialPort::NoFlowControl);
   thisPort.open(QSerialPort::ReadWrite);
  // thisPort.clear();



    if (thisPort.isOpen())
   {
     qDebug() << "Description: " << name << "\n";
        Toconsol(name + " Open");
     } else
        {
         Error(name + " Not open " + m_time.currentTime().toString() );
          thisPort.close();

        }
 }


void Port::WriteToPort(char command,char dat1, char dat2, char dat3, char dat4, char dat5, char dat6, char dat7)
{

   if(!is_busy)
   {
     thisPort.clear();
      thisPort.open(QSerialPort::ReadWrite);
    //Toconsol("TX");
    qDebug() << "WriteToPort(QByteArray data) " "\n";
    QString str2 ;//= ui->lineEdit->text();
    //char data1[16];


    data1[0] = command;
    data1[1] = dat1;
    data1[2] = dat2;
    data1[3] = dat3;

    data1[4] = dat4;
    data1[5] = dat5;
    data1[6] = dat6;
    data1[7] = dat7;


    str2 =data1;

      if(thisPort.isOpen())
      {
          qDebug() << "toPort " <<str2 << "\n";
          thisPort.write(data1,8);
          is_busy = 1;
      }
    }
    else
    {
       s_time = m_time.currentTime().toString();

     Error("need more time" + m_time.currentTime().toString());
    }

}


void Port::WriteToPort1(char command)
{

    thisPort.clear();
     thisPort.open(QSerialPort::ReadWrite);
   //Toconsol("TX");
   qDebug() << "WriteToPort(QByteArray data) " "\n";
   QString str2 ;//= ui->lineEdit->text();
   //char data1[16];
   data11[0] =  command;
   int n = command;
   for (int var = 1; var < n-1; ++var) {
      data11[var] = rand()&0xff ;
   }

unsigned char crc =  Crc8((unsigned char*) data11, n-1);
data11[n-1] = crc;
   str2 =data1;

     if(thisPort.isOpen())
     {

         thisPort.write(data11,n);
 qDebug() << "toPort " <<str2 << "\n";

    }
}

void Port::ReadInPort()
{
//Toconsol("RX");
QString  str1 ;
QByteArray num1;

// Читаем данные
 num1 = thisPort.read(2);
 int num2 = (0Xff&(num1[0]))|((0xff&num1[1])<<8);

qDebug() << "bytes to get " <<num2  << "\n";

 int num = thisPort.bytesAvailable();
qDebug() << "bytes Available " <<num << "\n";

if((num2 ) != num)
{

    Error("bytes to get is not Available " + m_time.currentTime().toString() );

    thisPort.clear();

 qDebug()<< "Bytes to get is not available " << "\n";
} else{
    if((num2 ) != 0)
    {
        Rxbuff =  thisPort.read(num2);
        void* adr = Rxbuff.data();
      SandRxBuff(adr, num2,  7);
        SaveFile_s("tst", adr, num2, 1, 7);

//       len = 900;
//       while(num>len){
//       ReadAndPlot(len);
//       num-=len;
//        }

    }else  Error( " 0 bytes " + m_time.currentTime().toString());
  }
is_busy = 0;

}

void Port:: s_close_port(){

    thisPort.clear();
    thisPort.close();
     Toconsol("Port is closed");
}



void Port::ReadInPort1()
{
//Toconsol("RX");
QString  str1 ;
QByteArray num1;

int num = thisPort.bytesAvailable();

// Читаем данные
 num1 = thisPort.read(num );
 for (int i = 0; i<num;i++)
 {
     if ( data11[i] != num1[i])
     {

         Error("bad"+ m_time.currentTime().toString());
         break;
     }
 }
Toconsol("good");
}

unsigned char Port:: Crc8(unsigned char *pcBlock, unsigned char len)
{
    unsigned char crc = 0xFF;

        while (len--)
            crc = Crc8Table[crc ^ *pcBlock++];

        return crc;
}
