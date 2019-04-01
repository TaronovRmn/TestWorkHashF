#ifndef HASHCALCULATOR_H
#define HASHCALCULATOR_H

#include <QObject>
#include <QFileInfoList>
#include <QListWidget>

class HashCalculator : public QObject {
    Q_OBJECT
  public:
    explicit HashCalculator(QObject *parent = nullptr);

  signals:

  public slots:
    static QString calcMD5(QString);
    static void calcFileList(QFileInfoList&, QListWidget*);
  private:

};

#endif // HASHCALCULATOR_H
