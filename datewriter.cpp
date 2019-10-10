#include "datewriter.h"
#include <QSettings>
#include <QDir>
DateWriter::DateWriter()
{
    m_config_writer = new QSettings(QDir::homePath() + "/config.data", QSettings::IniFormat);
}

void DateWriter::write(const QString & key, const QString & value)
{
    m_config_writer->setValue(key, value);
}
