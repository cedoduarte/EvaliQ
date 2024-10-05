#ifndef JSONFILEREADER_H
#define JSONFILEREADER_H

#include <QJsonDocument>

/**
 * @class JsonFileReader
 * @brief A class for reading JSON files and returning their contents as QJsonDocument.
 */
class JsonFileReader
{
public:
    /**
     * @brief Constructs a JsonFileReader object.
     */
    JsonFileReader();

    /**
     * @brief Reads a JSON file and returns its contents as a QJsonDocument.
     *
     * @param filePath The path to the JSON file to read.
     * @return A QJsonDocument containing the data from the file.
     * @throws std::runtime_error if the file cannot be opened or the contents are invalid JSON.
     */
    QJsonDocument readFile(const QString &filePath);
};

#endif // JSONFILEREADER_H

