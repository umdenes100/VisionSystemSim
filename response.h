#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QtDebug>
#include <QTextCodec>
#include <QRandomGenerator>
#include "detail.h"

#define RESP_TIME_MILLIS 250                        //average response time of the VS
#define RESP_DELAY_MILLIS (RESP_TIME_MILLIS - 75)   //avg delay used (offset by 50sms because of other delays)

static QRandomGenerator gen = QRandomGenerator::securelySeeded();
static std::normal_distribution<double> entropy_dist (RESP_DELAY_MILLIS, RESP_TIME_MILLIS * ENTROPY_STDDEV);
static std::default_random_engine rand_eng (gen.generate());

class Response : public QThread
{
    Q_OBJECT

public:
    explicit Response(QThread *parent = nullptr, QString data = "");
    ~Response() override;
    void run() override;

signals:
    void delayOver(QString msg);
public slots:

private:
    QString msg;
};

#endif // RESPONSE_H
