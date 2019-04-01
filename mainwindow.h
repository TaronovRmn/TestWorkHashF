#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>
#include "jsproxy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  public slots:

  private slots:
    QFileInfoList searchFiles(QString);
    void startCalculation();
    void showResult(QString);


  private:
    Ui::MainWindow *ui;
    JSProxy * jsProxy;
};

#endif // MAINWINDOW_H
