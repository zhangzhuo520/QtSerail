#include "datawriter.h"
#include <QSettings>
#include <QDir>
DataWriter::DataWriter()
{
    m_config_writer = new QSettings(QDir::currentPath() + "/config.data", QSettings::IniFormat);
}

void DataWriter::write(const QString & key, const QString & value)
{
    m_config_writer->setValue(key, value);
}
