#include "Logger.h"
#include "TextEditToQIODeviceAdapter.h"

QIODevice* Logger::_device = 0;

void Logger::setDevice(QIODevice* device) {
    _device = device;
}

Logger* Logger::getInstance()
{
    static Logger instance(_device);
    return &instance;
}

Logger::Logger(QIODevice* device)
    : QDebug (device) {}

