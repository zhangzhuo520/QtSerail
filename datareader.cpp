#include "datareader.h"
#include <QSettings>
DataReader::DataReader()
{
    m_config_reader = new DataReader(QDir::homePath() + "/config.data", QSettings::IniFormat);
}

QString DataReader::read(const QString & key)
{
    return  m_config_reader->value(key);
}
