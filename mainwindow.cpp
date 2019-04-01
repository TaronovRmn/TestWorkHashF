#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsproxy.h"
#include "hashcalculator.h"
#include <QWebEngineView>
#include <QWebChannel>
#include <QDir>
#include <QThread>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>

static const int THREAD_COUNT = 7;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QWebEngineView *view = new QWebEngineView(ui->widget);
    view->load(QUrl("qrc:/resource/resources/inputform.html"));
    view->resize(400,200);
    view->show();


    QWebChannel * poChannel = new QWebChannel(view->page());
    view->page()->setWebChannel(poChannel);
    jsProxy = new JSProxy(this);
    poChannel->registerObject(jsProxy->objectName(), jsProxy);
    connect(jsProxy, SIGNAL(pathReceived()), this, SLOT(startCalculation()));


}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::startCalculation() {
    QFileInfoList fileList = searchFiles(jsProxy->getFilePath());
    QVector<QFileInfoList> fileGroups;

    int filesInThread = fileList.length() / THREAD_COUNT;
    int rem = fileList.length() % THREAD_COUNT;

    for (int t = 0; t < THREAD_COUNT; t++) {
        QFileInfoList threadFileList;
        for (int i = 0; i < filesInThread; i++) {
            if (!fileList.isEmpty()) {
                threadFileList.push_back(fileList.first());
                fileList.pop_front();
            }
        }
        if (rem != 0) {
            if (!fileList.isEmpty()) {
                threadFileList.push_back(fileList.first());
                fileList.pop_front();
            }
            rem--;
        }
        fileGroups.push_back(threadFileList);

    }

    foreach (QFileInfoList list, fileGroups) {

        QtConcurrent::run( &HashCalculator::calcFileList, list, ui->listWidget);
    }



}

QFileInfoList MainWindow::searchFiles(QString filePath) {
    QDir dir(filePath);
    QFileInfoList allFiles = dir.entryInfoList(QDir::Files);
    return allFiles;
}

void MainWindow::showResult(QString result) {
    ui->listWidget->addItem(result);

}


