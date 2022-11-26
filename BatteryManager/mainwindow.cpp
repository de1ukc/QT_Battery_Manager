#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "battery_manager.h"
#include "qtimer.h"

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

    ui->remaning_time_work_value->setText(this->bm->get_battery_lifetime());

    ui->remaning_time_charge_value->setText(this->bm->get_battery_full_lifetime());

    if (ui->AC_status_value->text() == "От батареи" &&
            (ui->remaning_time_charge_value->text() == "Устройство подключено к сети" ||
             ui->remaning_time_work_value->text() == "Устройство подключено к сети")){

        ui->remaning_time_work_value->setText("...");
        ui->remaning_time_charge_value->setText("...");
    }

    ui->power_saving_value->setText(this->bm->get_battery_saver_status());

    if (this->bm->charging()){
        statusBar()->showMessage(tr("Батарея Заряжается.") + " Скорость зарядки: " +
                                 this->bm->get_charge_speed().c_str() + " mW");
    }else {
         statusBar()->showMessage(tr("Батарея Разряжается.") + " Скорость разрядки: " +
                                  this->bm->get_charge_speed().c_str() + " mW");
    }
}


void MainWindow::on_pushButton_clicked()
{
    this->bm->set_battery_saver();
}

