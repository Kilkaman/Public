#ifndef MYPORT_H
#define MYPORT_H


#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>


struct Settings {
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class Port : public QObject
{
    Q_OBJECT

public:

    explicit Port(QObject *parent = 0);

    ~Port();
      QTimer *Tmr= new QTimer();

    QSerialPort thisPort;

   // Settings SettingsPort;

 private:

    QByteArray Rxbuff;
    QString s_time;
    QByteArray num1;
    QTime m_time;
    int Rxind, Rxi;
    char Plotbuff[512];
    int Arr[ 0x8000];
    char data1[16];
    bool is_busy;
    bool f_work;
    char f_ready;
    int len;
    bool f_tmod=0;
    unsigned int Time;
    char last_command;
    int errs;
 signals:

     void Toconsol(QString data);
     void Error(QString data);
     void SandRxBuff(void* adr, int size, int n);
     void SaveFile_s(QString name,void* adr, int size, bool open, int n);

 private slots:

     void Write_Settings_Port(QString name,QThread* X/*, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl*/);
     void WriteToPort(char command,char dat1, char dat2, char dat3);//, char dat4, char dat5, char dat6, char dat7);
     void ReadInPort();
     void s_close_port();
     void s_StrtTmod(int T);
     void s_StopTmod();

};



#endif // MYPORT_H
