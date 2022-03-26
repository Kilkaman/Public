#ifndef MATH_H
#define MATH_H
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>

class Math_m : public QObject
{
    Q_OBJECT

public:

    explicit Math_m(QObject *parent = 0);

    ~Math_m();

    int Dat[0x3ff];
    int Datint[0xfff];
    char mass1[2048];
    int PlotDat[0xfff];
    int* Adr_mass;
    bool f_plot = 0;
    int n_Line;
    int n_point =0;
     QString Ang_Lir;
    //void MakePlotDat(void* adr, int size, int n );

 private:

 signals:


 void UpLCD(void* adr, int n);
 void SaveFile_s(void* adr, int size, int n);
 void SandPlotDat(void* adr,int size, int max);

 private slots:

 void MakeIntmass(void* adr, int size, int n );
 void StartStopPlot(bool f, int n);
 void MakePlotDat(void* adr, int size, int n );
 int AngCalc(char dat0, char dat1,char dat2,char dat3);

};



#endif // MATH_H
