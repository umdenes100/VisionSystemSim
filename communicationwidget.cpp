#include "communicationwidget.h"
#include "ui_communicationwidget.h"
#include <QThread>

CommunicationWidget::CommunicationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommunicationWidget)
{
    ui->setupUi(this);
    refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(checkPorts()));
    connect(ui->comboBox, SIGNAL(activated(QString)), this, SLOT(setPort(QString)));
    refreshTimer->start(500);
    thisPort = nullptr;
}

CommunicationWidget::~CommunicationWidget()
{
    delete ui;
}

void CommunicationWidget::setPort(QString name)
{
    if (thisPort != nullptr) {
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
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(name));
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
    QString msg = "";
    if(commandBuffer == "location") {
        double orientation = osv->location.theta > PI ? osv->location.theta - 2 * PI : osv->location.theta;

        QString location = "";
        location += QString::number(osv->location.x) + ",";
        location += QString::number(osv->location.y) + ",";
        location += QString::number(orientation) + "\n";
        msg = location;
    } else if(commandBuffer == "destination") {
        QString destination = "";
        destination += QString::number(osv->destination.x) + ",";
        destination += QString::number(osv->destination.y) + "\n";
        msg = destination;
    } else if(commandBuffer[0] == 'l') {
        // set left pwm
        commandBuffer.remove("l");
        osv->setLeftPWM(commandBuffer.toInt(), arena->getEntropy());
        return;
    } else if(commandBuffer[0] == 'r') {
        //set right pwm
        commandBuffer.remove("r");
        osv->setRightPWM(commandBuffer.toInt(), arena->getEntropy());
        return;
    }else if(commandBuffer.contains("distance")) {
        // read distance
        commandBuffer.remove("distance");
        int index = commandBuffer.toInt();
        QString send = QString::number(arena->getDistance(index)) + "\n";
        thisPort->write(send.toUtf8());
        return;
    }

    if (arena->getEntropy()) {
        if (rand() % FAIL_PERIOD == 0) {
            return;
        }
        std::normal_distribution<double> entropy_dist (RESP_DELAY_MILLIS, RESP_TIME_MILLIS * ENTROPY_STDDEV);
        std::default_random_engine gen;
        gen.seed(static_cast<std::linear_congruential_engine<unsigned int, 16807, 0, 2147483647>::result_type>(rand()));
        Response *response = new Response(nullptr, msg, static_cast<unsigned int>(entropy_dist(gen)));
        connect(response, &Response::finished, response, &QObject::deleteLater);
        connect(response, SIGNAL(delayOver(QString)), this, SLOT(responseReady(QString)));
        response->start();
    } else {
        thisPort->write(msg.toUtf8());
    }

}

void CommunicationWidget::responseReady(QString msg)
{
    thisPort->write(msg.toUtf8());
}

void CommunicationWidget::checkPorts()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QString currName = ui->comboBox->currentText();
    ui->comboBox->clear();
    foreach(QSerialPortInfo port, ports) {
        ui->comboBox->addItem(port.portName());
    }
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(currName));
}
