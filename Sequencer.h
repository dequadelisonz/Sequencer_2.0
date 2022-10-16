/******************************************************************************
Class Sequencer

*******************************************************************************/

#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "PassesList.h"
#include "JSONdoc.h"
//#include <iostream>
//#include <malloc.h>

class Sequencer : public std::list<PassesList>
{

private:
    // std::list<PassesList> _groupsList;
    JSONdoc &_jsonDoc;

    bool _hasRead = false;

    JSONReadStatus _readSource()
    {
        JSONReadStatus status = _jsonDoc._import();
        if (status == JSONReadStatus::READ_OK)
        {
            JsonArray cycle = _jsonDoc._doc[CYCLE];

            // outer cycle parsing iteration
            for (JsonObject c : cycle)
            {
                // set members of a group of passes
                PassesList passesList(c[OFFSET], c[GROUP_DURATION]);

                // iterate through group of passes fields to find the array of passes
                for (JsonPair p : c)
                {
                    if (p.value().is<JsonArray>())
                    {
                        // array of passes is found
                        JsonArray passes = p.value();

                        // iterate through each single pass of the array
                        for (JsonObject p : passes)
                        {
                            int id;
                            const char *descr;
                            double duration;
                            const char *uP_Inst;

                            for (JsonPair s : p)
                            {
                                if (s.key() == ID)
                                {
                                    id = s.value();
                                }
                                else if (s.key() == DESCRIPTION)
                                {
                                    descr = s.value();
                                }
                                else if (s.key() == DURATION)
                                {
                                    duration = s.value();
                                }
                                else if (s.key() == uP_INSTRUCTION)
                                {
                                    uP_Inst = s.value();
                                }
                            }
                            Pass pass(id, descr, duration, uP_Inst);

                            passesList.push_back(pass);
                        }
                    }
                }
                // then the group of passes is pushed in the sequencer list
                this->push_back(passesList);
            }
        }

        // std::cout << "After filling the list : " << std::endl;
        // malloc_stats();

        return status;
    }

public:
    Sequencer(JSONdoc &doc) : _jsonDoc(doc)
    {
        if (_readSource() == JSONReadStatus::READ_OK)
            _hasRead = true;
    }

    // PassesList::iterator& acceptGroup () const
    // {
    //     return _groupsList
    // }

    bool hasRead() const
    {
        return _hasRead;
    }
};

#endif