#ifndef DATEWRITER_H
#define DATEWRITER_H
#include <QString>

class QSettings;
class DataWriter
{
public:
    DataWriter();

    void write(const QString&, const QString&);

private:
     QSettings *m_config_writer;
};

#endif // DATEWRITER_H
