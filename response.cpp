#include "response.h"

Response::Response(QThread* parent, QString data, unsigned int delay) : QThread(parent)
{
    waitTime = delay;
    msg = data;
}

Response::~Response()
{

}

void Response::run()
{
    this->msleep(waitTime);
    emit delayOver(msg);
}
