#include "datareader.h"
#include <QDir>
#include <QSettings>
DataReader::DataReader()
{
    m_config_reader = new QSettings(QDir::currentPath() + "/config.data", QSettings::IniFormat);
}

QString DataReader::read(const QString & key)
{
    return  m_config_reader->value(key).toString();
}
