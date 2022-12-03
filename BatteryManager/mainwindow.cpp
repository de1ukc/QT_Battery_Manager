#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    bm = new batteryManager();
    bm->fillInfrormation();

    ui->setupUi(this);

    fillingFields();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(3000); // обновление каждые 3с, в идеале сделать обновление на изменение в структурах

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSleep_clicked()
{
    bm->sleep();
}


void MainWindow::on_btnHibernation_clicked()
{
    bm->hibernation();
}

void MainWindow::onTimeout()
{
    bm->fillBattery();
    bm->fillInfrormation();
    bm->initChemistry();
    fillingFields();
}

void MainWindow::fillingFields()
{
    ui->AC_status_value->setText(this->bm->getACStatus());

    ui->battery_charge_level_value->setText(this->bm->getBatteryChargeProcent() + "%");

    ui->battery_type_value->setText(this->bm->getBatteryType());

    ui->current_capacity_value->setText(this->bm->getCurrentCapacity() + " mWh");

    ui->max_capacity_value->setText(this->bm->getMaxCapacity() + " mWh");

    ui->designed_capacity_value->setText(this->bm->getDesignedCapacity() + " mWh");

    ui->cycles_value->setText(this->bm->getCyclesCount());

    QString bat_lifetime = this->bm->getBatteryLifetime();
    if (bat_lifetime == "От сети" && this->bm->getACStatus() == "От батареи"){
        ui->remaning_time_work_value->setText("...");
    } else {
        ui->remaning_time_work_value->setText(bat_lifetime);
    }

    ui->remaning_time_charge_value->setText(this->bm->getBatteryRemaninChargeTime());

    if (ui->remaning_time_work->text() == "От сети" &&
            this->bm->getACStatus() == "От батареи"){
        ui->remaning_time_work->setText("...");
    }

    ui->power_saving_value->setText(this->bm->getBatterySaverStatus());

    if (this->bm->charging()){
        statusBar()->showMessage(tr("Батарея Заряжается.") + " Скорость зарядки: " +
                                 this->bm->getChargeSpeed().c_str() + " mW");
    }else if (this->bm->discharging()) {
         statusBar()->showMessage(tr("Батарея Разряжается.") + " Скорость разрядки: " +
                                  this->bm->getChargeSpeed().c_str() + " mW");
    } else {
        statusBar()->showMessage(tr("Батарея Заряжена."));
    }

    int procent = this->bm->getBatteryProcent();
    //int procent = 10;
    if(procent < 20){
      //  ui->batteryBar->setTextVisible(false);
        ui->batteryBar->setValue(procent);
     //   ui->batteryBar->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #FF0000; width: 1px;}");

    } else if (procent >= 20 && procent <=100) {
        ui->batteryBar->setValue(procent);
    } else {
       // ui->batteryBar->setTextVisible(true); нужно вставить ошибку
    }
}
