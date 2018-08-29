#include "communicationwidget.h"
#include "ui_communicationwidget.h"

CommunicationWidget::CommunicationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommunicationWidget)
{
    ui->setupUi(this);
    refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(checkPorts()));
    connect(ui->comboBox, SIGNAL(activated(QString)), this, SLOT(setPort(QString)));
    refreshTimer->start(500);
    thisPort = NULL;
}

CommunicationWidget::~CommunicationWidget()
{
    delete ui;
}

void CommunicationWidget::setPort(QString name)
{
    if (thisPort != NULL) {
        thisPort->close();
    }
    thisPort = new QSerialPort(name, this);
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
        if(osv->location.theta > PI) {
            orientation = osv->location.theta - 2 * PI;
        } else {
            orientation = osv->location.theta;
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
        commandBuffer.remove("distance");
        int index = commandBuffer.toInt();
        QString send = QString::number(arena->getDistance(index)) + "\n";
        thisPort->write(send.toUtf8());
        return;
    }
}

void CommunicationWidget::checkPorts()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    ui->comboBox->clear();
    foreach(QSerialPortInfo port, ports) {
        ui->comboBox->addItem(port.portName());
    }
}
