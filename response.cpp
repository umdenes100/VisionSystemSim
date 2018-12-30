#include "response.h"

Response::Response(QThread* parent, QString data) : QThread(parent)
{
    msg = data;
}

Response::~Response()
{

}

void Response::run()
{
    quint32 num = gen.generate();
    rand_eng.seed(static_cast<std::linear_congruential_engine<unsigned int, 16807, 0, 2147483647>::result_type>(num));
    this->msleep(static_cast<unsigned int>(entropy_dist(rand_eng)));
    emit delayOver(msg);
}
