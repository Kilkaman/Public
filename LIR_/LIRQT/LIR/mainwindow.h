#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMainWindow>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QtCharts>
#include <QVector>

#include "MyPort.h"
#include "Math_m.h"
#include "File_m.h"
#include "MyPlot.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QThread *thread_Port = new QThread;//Создаем поток для порта платы
    Port *PortNew = new Port();//Создаем обьект классa

    QThread *thread_Mat = new QThread;
    Math_m *Mat = new Math_m();

    QThread *thread_File = new QThread;
    File_m *mFile = new File_m();

 //QThread *thread_Plot = new QThread;
//    MyPlot *m_Plot = new MyPlot();

    QTimer *TmrTX = new QTimer();

 //   QThread *thread_TMRTX = new QThread;//Создаем поток для порта таймера

    char  mass_tst [256];
    char dat[2048];

    int tstmass[2048];

//Plot
    double xBegin, xEnd, h, X;
    int N;
    QVector <double> x,y;
    int PlotMass[0xfff];
    bool f_plot = 0;
    int n_point = 0;
    int plot_size;
     bool f_stream = 0;
     bool f_modT = 0;
signals:

    void savesettings(QString name,QThread* X);
    void writeData(char command,char dat1, char dat2, char dat3);//, char dat4, char dat5, char dat6, char dat7);
    void sig_ReadInPort();
    void sig_StrtTmod(int T);

    void startRX(int msec, const QObject *receiver, const char *member);
    void MakeIntmass_s(void* adr, int size, int n );
    void SendName(QString filename);
    //
    void SaveFile_s(void* adr, int size, int n);
    void SaveOnOff(bool f_save);
    void close_port();
    void StartStopPlot(bool f, int n);


    void MakePlotDat(void* adr, int size, int n);
    //
 private slots:

    void updateTime();
     void Print(QString data);
     void PrintError(QString data);

     void UpLCD1(void* adr, int n);

     void on_Connect_clicked();

     void on_Exchange_clicked(bool checked);

     void on_TST_clicked();

//     void on_horizontalSlider_sliderMoved(int position);

     void on_A1_s_sliderMoved(int position);

//     void on_A2_s_sliderMoved(int position);

//     void on_Ph_s_sliderMoved(int position);

//     void on_A3_s_sliderMoved(int position);

     void on_Set_A1_clicked();

//     void on_Set_Ph_clicked();

//     void on_Set_A2_clicked();

//     void on_Set_A3_clicked();

     void on_Comand_Box_currentIndexChanged(int index);

     void UpdateData(void);

     void on_SaveOnOff_clicked(bool checked);

     void on_Browse_clicked();



     void on_Plot_clicked(bool checked);

     void PlotGraph(void* adr,int size, int max);

     void on_Y_scale_sliderMoved(int position);

     void on_X_scale_sliderMoved(int position);

     void on_Y_take_new_scale_clicked();

     void on_X_take_new_scale_clicked();

     void on_SetTimeout_clicked();
     void GetAng(int i1);


     void on_TimeRun_clicked();

private:
    Ui::MainWindow *ui;
    int timeout, timeout1, timeout2 ;
    int B0,B1,B2,B3,B4,B5,B6,B7;
    bool f_rxtx;

};
#endif // MAINWINDOW_H
