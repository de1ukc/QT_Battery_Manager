#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "battery_manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    bm = new batteryManager();
    bm->fill_infrormation();

    ui->setupUi(this);
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

