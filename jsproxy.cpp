#include "jsproxy.h"
#include "mainwindow.h"

JSProxy::JSProxy(QObject * poParent) : QObject(poParent) {
    setObjectName("qtProxy");

}
void JSProxy::setFilePath(const QString & filePath) {
    filePath_=filePath;
    emit pathReceived();

}
QString JSProxy::getFilePath() {
    return filePath_;
}
