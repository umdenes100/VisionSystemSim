#ifndef COMMUNICATIONWIDGET_H
#define COMMUNICATIONWIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <QScrollBar>

#include "osv.h"
#include "arena.h"

#define RESP_TIME_MILLIS 250    //average response time of the VS
#define RESP_DELAY_MILLIS (RESP_TIME_MILLIS - 75)  //avg delay used (offset by 50sms because of other delays)
#define FAIL_PERIOD 9           //enes library calls will fail at a rate ~ 1/FAIL_PERIOD

namespace Ui {
class CommunicationWidget;
}

class CommunicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommunicationWidget(QWidget *parent = nullptr);
    ~CommunicationWidget();
    OSV* osv;
    Arena* arena;

private slots:
    void checkPorts();
    void read();
    void setPort(QString name);

private:
    Ui::CommunicationWidget *ui;
    QSerialPort* thisPort;
    QTimer* refreshTimer;
    bool commandMode = false;
    QString commandBuffer;
    void executeCommand();
};

#endif // COMMUNICATIONWIDGET_H
