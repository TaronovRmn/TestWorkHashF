#include "hashcalculator.h"
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QThread>


HashCalculator::HashCalculator(QObject *parent) : QObject(parent) {

}

QString HashCalculator::calcMD5(QString fileName) {
    QString result;
    QCryptographicHash cryp(QCryptographicHash::Md5);
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly) ) {
        cryp.addData(& file);
        result = cryp.result().toHex().data();
        file.close();
    }
    return result;
}

void HashCalculator::calcFileList(QFileInfoList &fileList, QListWidget * list) {
    foreach (QFileInfo file, fileList) {
        QString result;
        result = calcMD5(file.absoluteFilePath()) + " = " + file.fileName();
        list->addItem(result);

    }

}
