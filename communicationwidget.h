#ifndef COMMUNICATIONWIDGET_H
#define COMMUNICATIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QScrollBar>
#include <QThread>
#include <QtSerialPort>

#include "response.h"
#include "osv.h"
#include "arena.h"

#define FAIL_PERIOD 20                               //enes library calls will fail at a rate ~ 1/FAIL_PERIOD

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

public slots:
    void responseReady(QString msg);

private slots:
    void checkPorts();
    void read();
    void setPort(QString name);

    void on_clearPortButton_clicked();

private:
    Ui::CommunicationWidget *ui;
    QSerialPort* thisPort;
    QTimer* refreshTimer;
    bool commandMode = false;
    QString commandBuffer;
    void executeCommand();
};

#endif // COMMUNICATIONWIDGET_H
