#ifndef DATAREADER_H
#define DATAREADER_H
#include <QString>

class QSettings;
class DataReader
{
public:
    DataReader();
    QString read(const QString&);

private:
    QSettings *m_config_reader;
};

#endif // DATAREADER_H
