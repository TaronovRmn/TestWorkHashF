#ifndef JSPROXY_H
#define JSPROXY_H

#include <QObject>


class JSProxy : public QObject {
    Q_OBJECT
  public:
    JSProxy(QObject * poParent = Q_NULLPTR);
    // Expose function to HTML/JS
    Q_INVOKABLE void setFilePath(const QString & filePath);
    QString getFilePath();

  private:
    QString filePath_;
  signals:
    void pathReceived();
};

#endif // JSPROXY_H
