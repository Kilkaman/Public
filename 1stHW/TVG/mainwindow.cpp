
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
    ui->Comand_Box->addItem("Single Shots");
    ui->Comand_Box->addItem("Streaming");

    ui->Chouse_Line->addItem("Line 1");
    ui->Chouse_Line->addItem("Line 2");
    ui->Chouse_Line->addItem("Line 3");
    ui->Chouse_Line->addItem("Line 4");
    ui->Chouse_Line->addItem("Line 5");
    ui->Chouse_Line->addItem("Line 6");
    ui->Chouse_Line->addItem("Line 7");
    ui->Chouse_Line->addItem("Line 8");

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
    TmrTX->moveToThread(thread_TMR);
    TmrRX->moveToThread(thread_TMR);


    ui->Dat_out_0->setDecMode();
    ui->Dat_out_1->setDecMode();
    ui->Dat_out_2->setDecMode();
    ui->Dat_out_3->setDecMode();
    ui->Dat_out_4->setDecMode();
    ui->Dat_out_5->setDecMode();
    ui->Dat_out_6->setDecMode();
    ui->Dat_out_7->setDecMode();

    ui->Y_scale_LCD->setDecMode();
    ui->Y_scale->setTickInterval(1);
    ui->Y_scale->setMinimum(20);
    ui->Y_scale->setMaximum(2048);

    ui->X_scale_LCD->setDecMode();
    ui->X_scale->setTickInterval(1);
    ui->X_scale->setMinimum(50);
    ui->X_scale->setMaximum(5000);

    ui->b0->setHexMode();
    ui->b1->setHexMode();
    ui->b2->setHexMode();
    ui->b3->setHexMode();
    ui->b4->setHexMode();
    ui->b5->setHexMode();
    ui->b6->setHexMode();
    ui->b7->setHexMode();


    //ui->A1_s->setTickInterval(1);
    ui->A1_s->setMaximum(2048);
    ui->Ph_s->setMaximum(255);
    ui->A2_s->setMaximum(2048);
    ui->A3_s->setMaximum(2048);




    connect(this, SIGNAL(savesettings(QString)),PortNew,SLOT(Write_Settings_Port(QString)));//Сигнал -нажатие Слот - ввод настроек
    connect(this, SIGNAL(close_port()),PortNew, SLOT(s_close_port()));
    connect(this, SIGNAL(writeData(char ,char , char , char, char ,char , char , char )),PortNew,SLOT(WriteToPort(char, char , char , char, char ,char , char , char ))); // сигнал от кнопки к слоту на отправку
    connect(this, SIGNAL(writeData1(char )),PortNew,SLOT(WriteToPort1(char ))); // сигнал от кнопки к слоту на отправку

    //  connect(this, SIGNAL(Port_work(bool,int)),PortNew, SLOT(F_work(bool, int)));


    connect(PortNew, SIGNAL(Toconsol(QString)), this, SLOT(Print(QString))); // сигнал в коде, если необходим вывод на экран - Слот- вывод текста в консоль.
    connect(PortNew, SIGNAL(Error(QString)), this, SLOT(PrintError(QString))); // сигнал в коде, если необходим вывод на экран - Слот- вывод текста в консоль.
    connect(PortNew, SIGNAL(SandRxBuff(void*, int, int)),Mat, SLOT(MakeIntmass(void*, int, int)));




    //connect(TmrTX, SIGNAL(timeout()), PortNew, SLOT( ReadInPort()));
    connect(TmrTX, SIGNAL(timeout()), this, SLOT(UpdateData()));
    connect(this, SIGNAL(sig_ReadInPort()), PortNew, SLOT(ReadInPort()) );

    connect(this, SIGNAL(startTMR()), TmrTX, SLOT(start()));
    connect(this, SIGNAL(stopTMR()), TmrTX, SLOT(stop()));
    // connect(this, SIGNAL(timeoutTMR(int)), TmrTX, SLOT(setInterval(int)));

    connect(this, SIGNAL(MakeIntmass_s(void*, int, int)),Mat,SLOT(MakeIntmass(void*, int, int)) );
    connect(Mat, SIGNAL(UpdateLCD_out(int, int, int, int, int, int, int, int)),this, SLOT(UpdateLCD_slt(int, int, int, int, int, int, int, int)));
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

  //  ui->widget->graph(0)->moveToThread(thread_Plot);
    thread_TMR->start();
    thread_Port->start();
    thread_Mat->start();
    thread_File->start();
   // thread_Plot->start();

    ui->adrFile->setText("C:/data/0");
    SendName("C:/data/0");
    x.clear();
    y.clear();
    plot_size = 5000;
    for( int i = 0; i<plot_size;i++)
    {
        x.push_back(i);
       // y.push_back(*(adr1 + i));
    }
     savesettings("COM6");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Connect_clicked()
{
   savesettings(ui->comboBox->currentText());
}

void MainWindow::on_Exchange_clicked(bool checked)
{
if (checked)
    {
    ui->SetTimeout->hide();
    UpdateData();

    }
else
    {
   stopTMR();
close_port();
 ui->SetTimeout->show();

    }
    f_rxtx = checked;
}



void MainWindow::Print(QString data)
{

    ui->consol->clear();
    ui->consol->clearHistory();
    ui->consol->textCursor().insertText(data+'\r'); // Вывод текста в консоль
    ui->consol->moveCursor(QTextCursor::End);//Scroll

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
 uint8_t a =(uint8_t) (ui->tsttxt->toPlainText().toInt())&0xff;
    writeData1(a);
   // TmrRX->singleShot(50,this,SLOT(updateTime()));
TmrRX->singleShot(100,PortNew,SLOT(ReadInPort1()));

}


void MainWindow::on_A1_s_sliderMoved(int position)
{
    ui->A1->display(position);
}

void MainWindow::on_A2_s_sliderMoved(int position)
{
    ui->A2->display(position);
}

//void MainWindow::on_horizontalSlider_sliderMoved(int position)
//{

//}

void MainWindow::on_Ph_s_sliderMoved(int position)
{
    ui->Ph->display(position);
}



void MainWindow::on_A3_s_sliderMoved(int position)
{
    ui->A3->display(position);
}

void MainWindow::on_Set_A1_clicked()
{
    int a = ui->A1_txt->toPlainText().toInt();
    ui->A1->display(a);
    ui->A1_s->setValue(a);
}

void MainWindow::on_Set_Ph_clicked()
{
    int a = ui->Ph_txt->toPlainText().toInt();
    a&=0xff;
    ui->Ph->display(a);
    ui->Ph_s->setValue(a);
}

void MainWindow::on_Set_A2_clicked()
{
    int a = ui->A2_txt->toPlainText().toInt();
    ui->A2->display(a);
    ui->A2_s->setValue(a);
}

void MainWindow::on_Set_A3_clicked()
{
    int a = ui->A3_txt->toPlainText().toInt();
    ui->A3->display(a);
    ui->A3_s->setValue(a);
}

void MainWindow::on_Comand_Box_currentIndexChanged(int index)
{
    switch (index)
    {
    case(0):
    ui->b0->display(0x30);
    break;
    case(1):
    ui->b0->display(0x34);
    break;
    B0 = index;

    }
}
 void MainWindow::UpdateData(void)
 {
    if (TmrTX->isActive()) sig_ReadInPort();
    B0 = ui->b0->value();
   // B1 = 0x5;
    B2 = ui->Ph->value();
    B3 = ui->A1->value();
    B4 = (B3>>8)&0xff;
    B5 = ui->A2->value();
    B6 = (B5>>8)&0xff;
    B7 = ui->A3->value();
    writeData(B0 ,B1 , B2 , B3, B4 ,B5 , B6 , B7 );
    ui->b1->display(B1&0xff);
    ui->b2->display(B2&0xff);
    ui->b3->display(B3&0xff);
    ui->b4->display(B4&0xff);
    ui->b5->display(B5&0xff);
    ui->b6->display(B6&0xff);
    ui->b7->display(B7&0xff);
    if (!TmrTX->isActive()) startTMR();

       StartStopPlot(f_plot, ui->Chouse_Line->currentIndex());
       plot_size = ui->X_scale_LCD->value();

 }


void MainWindow::UpLCD1(void* adr, int n)
{
int* adr1 = (int*) adr;

for (int i = 0; i < n; i++) {
    tstmass[i] = *(adr1+i) ;
}

ui->Dat_out_0->display(*(adr1));
ui->Dat_out_1->display(*(adr1+1));
ui->Dat_out_2->display(*(adr1+2));
ui->Dat_out_3->display(*(adr1+3));
ui->Dat_out_4->display(*(adr1+4));
ui->Dat_out_5->display(*(adr1+5));
ui->Dat_out_6->display(*(adr1+6));
ui->Dat_out_7->display(*(adr1+7));
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

void MainWindow::on_B1_butt0_clicked(bool checked)
{
  if (checked) B1|=1;
  else B1 &= 0xFE;
}

void MainWindow::on_B1_butt1_clicked(bool checked)
{
    if (checked) B1|=2;
    else B1 &= 0xFD;
}

void MainWindow::on_B1_butt4_clicked(bool checked)
{
    if (checked) B1|=1<<5;
    else B1 &= 0xDF;
}

void MainWindow::on_B1_butt2_clicked(bool checked)
{
    if (checked) B1|=1<<2;
    else B1 &= 0xFB;
}

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
  ui->widget->clearGraphs();
  for (int i = 0;i<size;i++) {
     y.push_back(*(adr1+i));

  }
 // y.append(*adr1);
  n_point+=size;
  // ui->Dat_out_7->display(y.end);
  ui->widget->xAxis->setRange(0,plot_size);
  ui->widget->yAxis->setRange(max-delta,max+delta);
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
ui->Y_scale_LCD->display(position);
}

void MainWindow::on_X_scale_sliderMoved(int position)
{
    ui->X_scale_LCD->display(position);
}

void MainWindow::on_Y_take_new_scale_clicked()
{
    int a = ui->Y_scale_txt->toPlainText().toInt();//A1_txt->toPlainText().toInt();
    ui->Y_scale_LCD->display(a);
    ui->Y_scale->setValue(a);

}

void MainWindow::on_X_take_new_scale_clicked()
{
    int a = ui->X_scale_txt->toPlainText().toInt();//A1_txt->toPlainText().toInt();
    ui->X_scale_LCD->display(a);
    ui->X_scale->setValue(a);
}

void MainWindow::on_SetTimeout_clicked()
{
    int a = ui->Timeout_txt->toPlainText().toInt();
    timeout = a;
    ui->TimeoutLSD->display(a);
    TmrTX->moveToThread(QApplication::instance()->thread());
    TmrTX->setInterval(a);
    moveToThread(thread_TMR);


    //startTMR();
}
