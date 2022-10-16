/******************************************************************************
Class JSONdoc

*******************************************************************************/

#ifndef JSONDOC_H
#define JSONDOC_H

#include "ArduinoJson-v6.19.4.h"
#include <fstream>
#include <string>
//#include <malloc.h>
#include "Sequencer.h"

using std::ifstream;
using std::string;

enum JSONReadStatus
{
    JSON_FORMAT_OR_MEMORY_ERROR,
    FILE_READING_ERROR,
    NET_READING_ERROR,
    READ_OK
};

const char CYCLE[] = "cycle";
const char OFFSET[] = "offset";
const char GROUP_DURATION[] = "groupDuration";
const char ID[] = "id";
const char DESCRIPTION[] = "Descrizione";
const char DURATION[] = "Durata";
const char uP_INSTRUCTION[] = "Comando_uP";

class JSONdoc
{
    friend class Sequencer;

protected:
    const char *_jsonFile;
    DynamicJsonDocument _doc;

private:
    // JSONdoc () {};

    JSONReadStatus _import()
    {
        JSONReadStatus status;
        ifstream inputFile;
        string _jsonBUF;
        inputFile.open(_jsonFile);
        if (!inputFile.fail())
        {
            getline(inputFile, _jsonBUF);
            DeserializationError err = deserializeJson(_doc, _jsonBUF);

            if (!err)
                status = JSONReadStatus::READ_OK;

            else
                status = JSONReadStatus::JSON_FORMAT_OR_MEMORY_ERROR;
        }
        else
            status = JSONReadStatus::FILE_READING_ERROR;

        inputFile.close();

        // std::cout << "After reading file : " << std::endl;
        // malloc_stats();

        return status;
    }

public:
    JSONdoc(const char *jsonFile, const int docSize) : _jsonFile(jsonFile),
                                                       _doc(docSize)
    {
        // std::cout << "Inside JSONdoc constructor : " << std::endl;
        // malloc_stats();
    }

    ~JSONdoc()
    {
        //_doc.~BasicJsonDocument();
    }
};

#endif