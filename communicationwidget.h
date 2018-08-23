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

namespace Ui {
class CommunicationWidget;
}

class CommunicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommunicationWidget(QWidget *parent = 0);
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
    int hasPort = -1;
    bool commandMode = false;
    QString commandBuffer;
    void executeCommand();
};

#endif // COMMUNICATIONWIDGET_H
