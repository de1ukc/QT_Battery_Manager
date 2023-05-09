#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "battery_manager.h"
#include "qtimer.h"
#include "QProgressBar"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSleep_clicked();

    void on_btnHibernation_clicked();


public slots:
    void onTimeout();
    void fillingFields();

private:
    Ui::MainWindow *ui;
    batteryManager *bm;

};
#endif // MAINWINDOW_H



