/******************************************************************************
Class KnotCycle

*******************************************************************************/

#ifndef KNOTCYCLE_H
#define KNOTCYCLE_H

#include "CycleEngine.h"
#include "Sequencer.h"
#include "JSONdoc.h"
#include <iostream>

const char IMPORT_OK[] = "Cycle has been correctly imported.\n";
const char ERROR_MSG[] = "Cycle have not been imported, possible failures:\n"
                         "\t-JSON file is not present;\n"
                         "\t-JSON file has wrong name or format;\n"
                         "\t-There's no enough memory reserved to init JSON doc.\n\n";

class KnotCycle : public CycleEngine
{

private:
    // int i = 0;
    JSONdoc _jsonDoc;
    Sequencer _seq;
    Sequencer::iterator _it;
    float _curDuration, _timer = 0.0f, kSpeed = 3.0f;
    bool _fired = false;

public:
    KnotCycle(const char *fileName, int docSize) : _jsonDoc(fileName, docSize), _seq(_jsonDoc), _it(_seq.begin())
    {
    }

    bool onUserCreate()
    {
        if (_seq.hasRead())
        {
            std::cout << IMPORT_OK;

            _curDuration = _it->getGroupDuration();

            return true;
        }
        else
        {
            std::cout << ERROR_MSG;
            return false;
        }
    }

    bool onUserUpdate(float elapsedTime)

    {
        _timer += elapsedTime;

        // std::cout << "\t\tElapsed time : " << elapsedTime << std::endl;
        // std::cout << "\t\tTimer : " << _timer << std::endl;
        // std::cout << "Fired : " << _fired << std::endl;

        if (!_fired)
        {
            auto pass = _it->begin();
            for (pass; pass != _it->end(); ++pass)
            {
                std::cout << "\tPass id : " << pass->getId() << " ***Timer: " << _timer << " *** " << std::endl;
                std::cout << "\tPass description : " << pass->getDescription() << std::endl;
                std::cout << "\tPass duration [s] : " << pass->getDuration() << std::endl;
                std::cout << "\t\tPin nr : " << pass->get_uP_instruction().pin << std::endl;
                std::cout << "\t\t\tPin status : " << pass->get_uP_instruction().status << std::endl
                          << std::endl;
            }
            _fired = true;
            _timer = 0.0f;
        }

        if (_timer >= _curDuration * kSpeed)
        {
            _fired = false;
            if (_it == --_seq.end()) //check if current iterator is the last element of the list
                _it = _seq.begin();
            else
                ++_it;
            _curDuration = _it->getGroupDuration();
        }

        return true;
    }
};

#endif