#ifndef JSONFILEREADER_H
#define JSONFILEREADER_H

#include <QJsonDocument>

class JsonFileReader
{
public:
    JsonFileReader();
    QJsonDocument readFile(const QString &filePath);
};

#endif // JSONFILEREADER_H
