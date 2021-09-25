#ifndef FILE_M_H
#define FILE_M_H
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>
class File_m: public QObject
{
    Q_OBJECT

public:

    explicit File_m(QObject *parent = 0);

    ~File_m();




 private:

    bool m_save = 0;
    int len = 0;
    QByteArray filedata;
    QTime m_time;
    QString s_time;
    QString filename;
    QString name0 = "C:/data/0";

 signals:




 private slots:
 void SaveFile(void* adr, int size, int n);
 void GetName(QString name);
 void SaveOnOff(bool f_save);
};



#endif // FILE_M_H
