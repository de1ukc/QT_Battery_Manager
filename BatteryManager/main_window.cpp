#include "main_window.h"
#include "ui_mainwindow.h"
//#include "battery_manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    batteryManager *bm = new batteryManager();

//    bm->fill_infrormation();
//    delete bm;

}

MainWindow::~MainWindow()
{
    delete ui;
}

