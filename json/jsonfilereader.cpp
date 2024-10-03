#include "jsonfilereader.h"

#include <QFile>
#include <QTextStream>

JsonFileReader::JsonFileReader() {}

QJsonDocument JsonFileReader::readFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString json = stream.readAll();
        file.close();
        return QJsonDocument::fromJson(json.toUtf8());
    }
    return QJsonDocument();
}
