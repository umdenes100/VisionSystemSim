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
    std::normal_distribution<double> entropy_dist (RESP_DELAY_MILLIS, RESP_TIME_MILLIS * ENTROPY_STDDEV);
    std::default_random_engine gen;
    gen.seed(static_cast<std::linear_congruential_engine<unsigned int, 16807, 0, 2147483647>::result_type>(rand()));
    this->msleep(static_cast<unsigned int>(entropy_dist(gen)));
    emit delayOver(msg);
}
