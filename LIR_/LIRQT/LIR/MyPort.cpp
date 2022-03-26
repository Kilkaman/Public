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
void Port::Write_Settings_Port(QString name,QThread* X )//setup COM port
{
//if (X)thisPort.moveToThread(X);
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

    f_ready = 0;

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


void Port::WriteToPort(char command,char dat1, char dat2, char dat3)//, char dat4, char dat5, char dat6, char dat7)
{

   if((!is_busy)&( thisPort.isOpen()))
   {
     //thisPort.clear();
    // thisPort.open(QSerialPort::ReadWrite);
    //Toconsol("TX");

   // QString str2 ;//= ui->lineEdit->text();
    //char data1[16];

    data1[0] = command;
    data1[1] = dat1;
    data1[2] = dat2;
    data1[3] = dat3;
    if (last_command != data1[0])
    { f_ready = 0;
        f_ready += 1;

    }last_command = data1[0];
  //  str2 =;
 //  qDebug() << "WriteToPort(QByteArray data) " "\n";
      //if(thisPort.isOpen())
      {
          qDebug() << "toPort " <<data1[0] << "\n";
          qDebug()<<"In" << "\n";
          thisPort.write(data1,4);
          is_busy = 1;
          qDebug()<<"out" << "\n";
      }
    }
    else
    {
       s_time = m_time.currentTime().toString();

     Error("need more time" + m_time.currentTime().toString());
     qDebug()<<0 << "\n";
    }

}


void Port::ReadInPort()
{
    f_ready+=1;
    if(f_ready>=10) f_ready = 10;

    if(!thisPort.isOpen())    thisPort.open(QSerialPort::ReadWrite);
 Toconsol(thisPort.portName() + " Open");


// Читаем данные

switch (last_command)
{
    case(0x42)://B
        {
             num1 = thisPort.read(2);
              unsigned int X = thisPort.bytesAvailable();
            unsigned int num2 = (0Xff&(num1[0]))|((0xff&num1[1])<<8);

            if (X!=num2)
            {
                qDebug()<<X << num2<< "\n";
                is_busy = 0;
                if (f_ready<10)Error( "Config" + m_time.currentTime().toString());
                else Error( "Invalid bytes number" + m_time.currentTime().toString());
                 thisPort.readAll();
                  errs++;
               // s_close_port();
                 return;
            }
            qDebug()<<X << "\n";
             if (!num2)
             {
                   is_busy = 0;
                   if (f_ready<10)Error( "Config" + m_time.currentTime().toString());
                    else Error( " 0 bytes " + m_time.currentTime().toString());
                //thisPort.readAll();
                 //s_close_port();

                return;
             }
             {

                  Rxbuff =  thisPort.read(num2);
                  void* adr = Rxbuff.data();
                  if (f_ready==10)
                  {
                   if(f_tmod)
                   {
                       Tmr->singleShot(Time,this,SLOT (s_StopTmod()));
                       f_tmod=0;
                       errs = 0;
                   }
                  SandRxBuff(adr, num2,  1);
                  SaveFile_s("tst", adr,num2, 1, 1);
                  }
                  else Error( "Config" + m_time.currentTime().toString());
             }//else  Error( " 0 bytes " + m_time.currentTime().toString());
        }
    break;
    case(0x41)://A
       {

    num1 = thisPort.read(2);

     unsigned int X = thisPort.bytesAvailable();
   unsigned int num2 = (0Xff&(num1[0]))|((0xff&num1[1])<<8);

   if (X!=num2)
   {
       is_busy = 0;
       if (f_ready<5)Error( "Config" + m_time.currentTime().toString());
      else Error( "Invalid bytes number" + m_time.currentTime().toString());
        thisPort.readAll();
      // s_close_port();
        return;
   }
   qDebug()<<X << "\n";
    if (!num2)
    {
          is_busy = 0;
          if (f_ready<5)Error( "Config" + m_time.currentTime().toString());
        else  Error( "0 bytes" + m_time.currentTime().toString());
         // thisPort.readAll();
        //s_close_port();
       return;
    }else
    {
        f_ready = 10;
         Rxbuff =  thisPort.read(num2);
         void* adr = Rxbuff.data();
         SandRxBuff(adr, num2,  1);
         SaveFile_s("tst", adr,num2, 1, 1);
    }
      }

    break;
    case(0x47)://G
        {
        int num = thisPort.bytesAvailable();
        if((num ) != 0)
         {

             Rxbuff =  thisPort.read(num);
             void* adr = Rxbuff.data();
             SandRxBuff(adr, num,  1);
             SaveFile_s("tst", adr, num, 1, 1);


         }else  Error( " 0 bytes " + m_time.currentTime().toString());
        }
    break;


}

is_busy = 0;

}
void Port:: s_close_port(){

    thisPort.clear();
    thisPort.close();
     Toconsol("Port is closed");
      f_ready =0;
     f_ready+=1;
}

void Port::s_StrtTmod(int T)
{
    f_tmod = 1;

    Time = T;

}


void Port::s_StopTmod()
{
  Toconsol("Dat is saved");
  if(!errs)   Error( " Dat saved, 0 errors " + m_time.currentTime().toString());
  else Error( " Dat saved with errors " + m_time.currentTime().toString());

}
