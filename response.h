#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QtDebug>
#include <QTextCodec>

class Response : public QThread
{
    Q_OBJECT

public:
    explicit Response(QThread *parent = nullptr, QString data = "", unsigned int delay=0);
    ~Response();
    void run() override;

signals:
    void delayOver(QString msg);
public slots:

private:
    QString msg;
    unsigned int waitTime;
};

#endif // RESPONSE_H
