
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//ищем доступнык порты
    ui->comboBox->addItem(info.portName());//выводим доступные порты в combobox


    ui->TST->hide();
    ui->Chouse_Line->hide();


    ui->Comand_Box->addItem("Single Shots");
    ui->Comand_Box->addItem("Streaming");


    ui->Chouse_Line->addItem("Line 1");
    ui->Chouse_Line->addItem("Line 2");
    ui->Chouse_Line->addItem("Line 3");
    ui->Chouse_Line->addItem("Line 4");
//    ui->Chouse_Line->addItem("Line 5");
//    ui->Chouse_Line->addItem("Line 6");
//    ui->Chouse_Line->addItem("Line 7");
//    ui->Chouse_Line->addItem("Line 8");

    B1 = 0;
    f_rxtx = 0;
//    timeout1 = 0;//интервал ожидания приема
//    timeout2 = 50;//интервал на обработку
    timeout = 50;
    ui->TimeoutLSD->display(timeout);

    PortNew->moveToThread(thread_Port);//помешаем класс  в поток
    Mat->moveToThread(thread_Mat);
    mFile->moveToThread(thread_File);

    TmrTX->setInterval(timeout);// между отправками

   // TmrTX->moveToThread(thread_TMRTX);




   // ui->Y_scale_LCD->setDecMode();
    ui->Y_scale->setTickInterval(1);
    ui->Y_scale->setMinimum(10);
    ui->Y_scale->setMaximum(360);

  //  ui->X_scale_LCD->setDecMode();
    ui->X_scale->setTickInterval(1);
    ui->X_scale->setMinimum(100);
    ui->X_scale->setMaximum(15000);

    ui->b0->setHexMode();
    ui->b1->setHexMode();
    ui->b2->setHexMode();
    ui->b3->setHexMode();



    //ui->A1_s->setTickInterval(1);
      ui->A1_s->setMinimum(5000);
    ui->A1_s->setMaximum(100000);
ui->A1->display(5000);



    connect(this, SIGNAL(savesettings(QString,QThread*)),PortNew,SLOT(Write_Settings_Port(QString,QThread*)));//Сигнал -нажатие Слот - ввод настроек
    connect(this, SIGNAL(close_port()),PortNew, SLOT(s_close_port()));
  // connect(this, SIGNAL(writeData(char ,char , char , char, char ,char , char , char )),PortNew,SLOT(WriteToPort(char, char , char , char, char ,char , char , char ))); // сигнал от кнопки к слоту на отправку
   connect(this, SIGNAL(writeData(char ,char , char , char)),PortNew,SLOT(WriteToPort(char, char , char , char))); // сигнал от кнопки к слоту на отправку
    //  connect(this, SIGNAL(Port_work(bool,int)),PortNew, SLOT(F_work(bool, int)));

   connect(this, SIGNAL(sig_StrtTmod(int)),PortNew, SLOT( s_StrtTmod(int)));
    //connect(PortNew, SIGNAL(sig_EndSave(QString,bool)), this, SLOT(s_EndSave(QString,bool)));

    connect(PortNew, SIGNAL(Toconsol(QString)), this, SLOT(Print(QString))); // сигнал в коде, если необходим вывод на экран - Слот- вывод текста в консоль.
    connect(PortNew, SIGNAL(Error(QString)), this, SLOT(PrintError(QString))); // сигнал в коде, если необходим вывод на экран - Слот- вывод текста в консоль.
    connect(PortNew, SIGNAL(SandRxBuff(void*, int, int)),Mat, SLOT(MakeIntmass(void*, int, int)));




    //connect(TmrTX, SIGNAL(timeout()), PortNew, SLOT( ReadInPort()));
    connect(TmrTX, SIGNAL(timeout()), this, SLOT(UpdateData()));
    connect(this, SIGNAL(sig_ReadInPort()), PortNew, SLOT(ReadInPort()) );

//    connect(this, SIGNAL(startTMR()), TmrTX, SLOT(start()));
//    connect(this, SIGNAL(stopTMR()), TmrTX, SLOT(stop()));
//     connect(this, SIGNAL(delTMR()), TmrTX, SLOT(destroyed()));
//     connect(this, SIGNAL(newTmrT(int)),TmrTX,SLOT(setInterval(int)));

    // connect(this, SIGNAL(timeoutTMR(int)), TmrTX, SLOT(setInterval(int)));

    connect(this, SIGNAL(MakeIntmass_s(void*, int, int)),Mat,SLOT(MakeIntmass(void*, int, int)) );
    //connect(Mat, SIGNAL(UpdateLCD_out(int, int, int, int, int, int, int, int)),this, SLOT(UpdateLCD_slt(int, int, int, int, int, int, int, int)));
    connect(Mat, SIGNAL(UpLCD(void*, int)),this, SLOT(UpLCD1(void*, int)));
    connect(Mat, SIGNAL(SaveFile_s(void*, int,   int)), mFile, SLOT(SaveFile(void*, int, int)) );
    connect(this,SIGNAL(SendName(QString)),mFile, SLOT(GetName(QString)));
    connect(this,SIGNAL(SaveOnOff(bool)),mFile, SLOT(SaveOnOff(bool)));

   // connect(this, SIGNAL(SaveFile_s( void*, int, int)), mFile, SLOT(SaveFile( void*, int, int)) );

    connect(Mat,SIGNAL(SandPlotDat(void* ,int, int )),this,SLOT(PlotGraph(void* ,int , int )));
    connect(this,SIGNAL(StartStopPlot(bool , int )),Mat,SLOT(StartStopPlot(bool, int )));
        //tst
     connect(this, SIGNAL(MakePlotDat(void* , int , int  )), Mat,SLOT(MakePlotDat(void* ,int,int))) ;
        //
 QThread* X = TmrTX->thread();

 savesettings("COM4",X);
  //  ui->widget->graph(0)->moveToThread(thread_Plot);
   // thread_TMRTX->start();

    thread_Port->start();
    thread_Mat->start();
    thread_File->start();
   // thread_Plot->start();

    ui->adrFile->setText("C:/data/0");
    SendName("C:/data/0");
    x.clear();
    y.clear();
    plot_size = 10000;
    for( int i = 0; i<plot_size;i++)
    {
        x.push_back(i);
       // y.push_back(*(adr1 + i));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Connect_clicked()
{
   savesettings(ui->comboBox->currentText(),0);
}

void MainWindow::on_Exchange_clicked(bool checked)
{
if (checked)
    {
    ui->SetTimeout->hide();
    ui->Comand_Box->hide();
    UpdateData();

    }
else
    {
  TmrTX->stop();

close_port();
 ui->SetTimeout->show();
ui->Comand_Box->show();
    }
    f_rxtx = checked;
}



void MainWindow::Print(QString data)
{

    ui->consol->clear();
    ui->consol->clearHistory();
    ui->consol->textCursor().insertText(data+'\r'); // Вывод текста в консоль
    ui->consol->moveCursor(QTextCursor::End);//Scroll
    if (data=="Dat is saved")
    {
        ui->Comand_Box->setCurrentIndex(0);
        ui->SaveOnOff->clicked(0);
        ui->Plot->clicked(0);
        ui->Exchange->clicked(0);

    }


}

void MainWindow::PrintError(QString data)
{

    ui->ErrorBox->clear();
    ui->ErrorBox->clearHistory();
    ui->ErrorBox->textCursor().insertText(data+'\r'); // Вывод текста в консоль
    ui->ErrorBox->moveCursor(QTextCursor::End);//Scroll

}
void MainWindow:: updateTime()
{



}

void MainWindow::on_TST_clicked()
{

//    unsigned int* X = 0;
//    unsigned char* Y = 0;
//    X+=4;
//    Y+=4;
   writeData(0x42 ,0x30 , 0x30 , 0x30);//, 0x30 ,0x30 , 0x30 , 0x30 );

}


void MainWindow::on_A1_s_sliderMoved(int position)
{
    ui->A1->display(position);
}



//void MainWindow::on_horizontalSlider_sliderMoved(int position)
//{

//}




void MainWindow::on_Set_A1_clicked()
{
    int a = ui->A1_txt->toPlainText().toInt();
    if (a<5000)a = 5000;
    ui->A1->display(a);
    ui->A1_s->setValue(a);
}




void MainWindow::on_Comand_Box_currentIndexChanged(int index)
{
    switch (index)
    {
    case(0):
    ui->b0->display(0x41);
    f_stream = 0;
   // B0 = index;
    break;
    case(1):
    ui->b0->display(0x42);
  //  B0 = 0x47;
    f_stream = 1;

    break;


    }

}
 void MainWindow::UpdateData(void)
 {
    if (TmrTX->isActive()) sig_ReadInPort();
    else TmrTX->start();
    B0 = ui->b0->value();
   B1 = 0x5;
   B1 = ui->A1->value();
   B2 = (B1>>8)&0xff;
    B3 =0;
      writeData(B0 ,B1 , B2 , B3);//, B4 ,B5 , B6 , B7 );

    ui->b1->display(B1&0xff);
    ui->b2->display(B2&0xff);
    ui->b3->display(B3&0xff);
    if (f_stream) ui->b0->display(0x42);
    //if (!TmrTX->isActive()) startTMR();

       StartStopPlot(f_plot, ui->Chouse_Line->currentIndex());
       //plot_size = ui->X_scale_LCD->value();

 }


void MainWindow::UpLCD1(void* adr, int n)
{
int* adr1 = (int*) adr;

for (int i = 0; i < n; i++) {
    tstmass[i] = *(adr1+i) ;
    GetAng( *(adr1+i));
}


n = 0;

}

void MainWindow::on_SaveOnOff_clicked(bool checked)
{
    SaveOnOff(checked);
}

void MainWindow::on_Browse_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if(filename != "")
    {
    ui->adrFile->setText(filename);
    }
    SendName(filename);
}

//void MainWindow::on_B1_butt0_clicked(bool checked)
//{
//  if (checked) B1|=1;
//  else B1 &= 0xFE;
//}

//void MainWindow::on_B1_butt1_clicked(bool checked)
//{
//    if (checked) B1|=2;
//    else B1 &= 0xFD;
//}

//void MainWindow::on_B1_butt4_clicked(bool checked)
//{
//    if (checked) B1|=1<<5;
//    else B1 &= 0xDF;
//}

//void MainWindow::on_B1_butt2_clicked(bool checked)
//{
//    if (checked) B1|=1<<2;
//    else B1 &= 0xFB;
//}

void MainWindow::on_Plot_clicked(bool checked)
{
    f_plot = checked;
    if(checked) ui->Chouse_Line->setHidden(1);
    else  ui->Chouse_Line->show();
}

void MainWindow::PlotGraph(void *adr, int size, int max)
{
  int* adr1 = (int*) adr;
  int size1 = y.size();
  int delta = ui->Y_scale->value();
  float X;
  ui->widget->clearGraphs();
  for (int i = 0;i<size;i++) {
    //GetAng((int) *(adr1+i));
      X = (float)(*(adr1+i));
     X/=(1<<24);
      X*=360;
     y.push_back(X);

  }

 // y.append(*adr1);
  n_point+=size;
  // ui->Dat_out_7->display(y.end);
  ui->widget->xAxis->setRange(0,plot_size);
  ui->widget->yAxis->setRange(X-delta,X+delta);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x,y);
  ui->widget->replot();

  if(size1>plot_size)
   {
        //ui->widget->graph(0)->clearData();
         //x.clear();
        y.erase(y.begin(), y.end()-plot_size);
       // n_point = 0;

         ui->widget->xAxis->setRange(0,size1);
   }


}



void MainWindow::on_Y_scale_sliderMoved(int position)
{
//ui->Y_scale_LCD->display(position);
}

void MainWindow::on_X_scale_sliderMoved(int position)
{
    plot_size = position;

 //   ui->X_scale_LCD->display(position);
}

void MainWindow::on_Y_take_new_scale_clicked()
{
    int a = ui->Y_scale_txt->toPlainText().toInt();//A1_txt->toPlainText().toInt();
 //   ui->Y_scale_LCD->display(a);
    ui->Y_scale->setValue(a);

}

void MainWindow::on_X_take_new_scale_clicked()
{
    int a = ui->X_scale_txt->toPlainText().toInt();//A1_txt->toPlainText().toInt();
   // ui->X_scale_LCD->display(a);
    ui->X_scale->setValue(a);
}

void MainWindow::on_SetTimeout_clicked()
{
    int a = ui->Timeout_txt->toPlainText().toInt();
    timeout = a;
    ui->TimeoutLSD->display(a);
    TmrTX->stop();
    TmrTX->setInterval(a);

}

void MainWindow::GetAng(int i1)
{
int is,im,ig;
long long ils;


    ils = 360*60*60;
    ils *= i1;
    is = (int)(ils>>24);
    //
    ig = is/(60*60);
    im = (is/(60))%60;
    is = is%60;
    ui->Deg->display(ig);
    ui->mins->display(im);
    ui->sec->display(is);

}

void MainWindow::on_TimeRun_clicked()
{

  //  f_modT = 1;
    ui->Comand_Box->setCurrentIndex(1);
    ui->SaveOnOff->clicked(1);
    ui->Plot->clicked(1);
    ui->Exchange->clicked(1);
   sig_StrtTmod(ui->A1->value());

}
