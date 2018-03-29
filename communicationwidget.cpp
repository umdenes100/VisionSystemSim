#include "communicationwidget.h"
#include "ui_communicationwidget.h"

CommunicationWidget::CommunicationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommunicationWidget)
{
    ui->setupUi(this);
    refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(checkPorts()));
    refreshTimer->start(500);
}

CommunicationWidget::~CommunicationWidget()
{
    delete ui;
}

void CommunicationWidget::read()
{
    while(thisPort->bytesAvailable()) {
        char c;
        thisPort->getChar(&c);

        if(!commandMode) {
            if(c == '#') {
                commandMode = true;
                continue;
            }

            ui->textBrowser->insertPlainText(QString(c));
            ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
        } else {
            if(c == '*') {
                commandMode = false;
                executeCommand();
                commandBuffer = "";
                continue;
            }

            commandBuffer.append(c);
        }
    }
}

void CommunicationWidget::executeCommand()
{
    // TODO: everythign

    if(commandBuffer == "location") {
        float orientation;
        if(osv->orientation > PI) {
            orientation = osv->orientation - 2 * PI;
        } else {
            orientation = osv->orientation;
        }
        QString location = "";
        location += QString::number(osv->location.x) + ",";
        location += QString::number(osv->location.y) + ",";
        location += QString::number(orientation) + "\n";
        thisPort->write(location.toUtf8());
        return;
    }

    if(commandBuffer == "destination") {
        QString destination = "";
        destination += QString::number(osv->destination.x) + ",";
        destination += QString::number(osv->destination.y) + "\n";
        thisPort->write(destination.toUtf8());
        return;
    }

    if(commandBuffer[0] == 'l') {
        // set left pwm
        commandBuffer.remove("l");
        osv->setLeftPWM(commandBuffer.toInt());
        return;
    }

    if(commandBuffer[0] == 'r') {
        //set right pwm
        commandBuffer.remove("r");
        osv->setRightPWM(commandBuffer.toInt());
        return;
    }

    if(commandBuffer.contains("distance")) {
        // read distance
        return;
    }
}

void CommunicationWidget::checkPorts()
{
    if(hasPort) {
        return;
    }

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    if(ports.size() > 0) {
        // if we have a new port
        // TODO: check for bs
        hasPort = true;
        thisPort = new QSerialPort(ports[0].portName(), this);
        thisPort->setBaudRate(QSerialPort::Baud9600);
        thisPort->setParity(QSerialPort::NoParity);
        thisPort->setDataBits(QSerialPort::Data8);
        thisPort->setStopBits(QSerialPort::OneStop);
        thisPort->setFlowControl(QSerialPort::NoFlowControl);

        while(!thisPort->isOpen()) {
            thisPort->open(QSerialPort::ReadWrite);
        }
        connect(thisPort, SIGNAL(readyRead()), this, SLOT(read()));
    }
}
