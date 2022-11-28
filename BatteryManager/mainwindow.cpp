#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    bm = new batteryManager();
    bm->fill_infrormation();

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
    bm->fill_battery();
    bm->fill_infrormation();
    bm->initChemistry();
    fillingFields();
}

void MainWindow::fillingFields()
{
    ui->AC_status_value->setText(this->bm->get_AC_status());

    ui->battery_charge_level_value->setText(this->bm->get_battery_charge_procent() + "%");

    ui->battery_type_value->setText(this->bm->get_battery_type());

    ui->current_capacity_value->setText(this->bm->get_current_capacity() + " mWh");

    ui->max_capacity_value->setText(this->bm->get_max_capacity() + " mWh");

    ui->designed_capacity_value->setText(this->bm->get_designed_capacity() + " mWh");

    ui->cycles_value->setText(this->bm->get_cycles_count());

    QString bat_lifetime = this->bm->get_battery_lifetime();
    if (bat_lifetime == "От сети" && this->bm->get_AC_status() == "От батареи"){
        ui->remaning_time_work_value->setText("...");
    } else {
        ui->remaning_time_work_value->setText(bat_lifetime);
    }

    ui->remaning_time_charge_value->setText(this->bm->get_battery_remanin_charge_time());

    if (ui->remaning_time_work->text() == "От сети" &&
            this->bm->get_AC_status() == "От батареи"){
        ui->remaning_time_work->setText("...");
    }

    ui->power_saving_value->setText(this->bm->get_battery_saver_status());

    if (this->bm->charging()){
        statusBar()->showMessage(tr("Батарея Заряжается.") + " Скорость зарядки: " +
                                 this->bm->get_charge_speed().c_str() + " mW");
    }else if (this->bm->discharging()) {
         statusBar()->showMessage(tr("Батарея Разряжается.") + " Скорость разрядки: " +
                                  this->bm->get_charge_speed().c_str() + " mW");
    } else {
        statusBar()->showMessage(tr("Батарея Заряжена."));
    }

    int procent = this->bm->get_battery_procent();
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
