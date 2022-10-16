/******************************************************************************
Class PassesList

*******************************************************************************/

#ifndef PASSESLIST_H
#define PASSESLIST_H

#include <string.h>
#include <list>
#include <cassert>

const char PASS_DELIMITER[] = "_";
const char STATUS_ON[] = "ON";
const char STATUS_OFF[] = "OFF";

struct uP_instruction_t
{
    short unsigned int pin;
    bool status;
};

class Pass
{
private:
    const int _id;
    const char *_description;
    const uP_instruction_t _uPInstr;
    const double _duration;

    uP_instruction_t set_uP_instruction(const char *uP_Inst)
    {
        uP_instruction_t uP_I;
        char temp[7];
        strcpy(temp, uP_Inst);
        // extract the token of pin number from input string (the first one)
        char *token = strtok(temp, PASS_DELIMITER);
        // convert to short unsigned int and assign to pin field
        uP_I.pin = strtol(token, NULL, 0);
        // extract the token of status number from input string (the second one)
        token = strtok(NULL, PASS_DELIMITER);
        // compare with string "ON" or "OFF" and set the status consequently
        uP_I.status = (strcmp(token, STATUS_ON) == 0) ? true : false;
        return uP_I;
    }

public:
    Pass(int id,
         const char *descr,
         double duration,
         const char *uP_instruction) :

                                       _id(id),
                                       _description(descr),
                                       _uPInstr(set_uP_instruction(uP_instruction)),
                                       _duration(duration)
    {
    }

    int getId() const
    {
        return _id;
    }

    char const *getDescription() const
    {
        return _description;
    }

    uP_instruction_t get_uP_instruction() const
    {
        return _uPInstr;
    }

    double getDuration() const
    {
        return _duration;
    }
};

/***************************************************************************************/

class PassesList : public std::list<Pass>
{
private:
    const double _offset;
    const double _groupDuration;
    PassesList::iterator _curPos;
    bool _isAtBegin=true;

public:
    PassesList(double offset, double groupDuration) : _offset(offset),
                                                      _groupDuration(groupDuration),
                                                      _curPos(this->begin())
    {
    }

    double getOffset() const
    {
        return _offset;
    }

    double getGroupDuration() const
    {
        return _groupDuration;
    }

    // void push(Pass p)
    // {
    //     _passList.push_back(p);
    // }

    // list<Pass>::iterator getBegin()
    // {
    //     return _passList.begin();
    // }

    // list<Pass>::iterator getEnd()
    // {
    //     return _passList.end();
    // }

    // Pass &advance()
    // {
    //     assert(!this->empty());
    //     Pass p = *_curPos;
    //     if (_curPos != _passList.end())
    //     {
    //         std::advance(_curPos, 1);
    //         _isAtBegin=false;
    //     }
    //     else
    //     {
    //         _curPos = this->begin();
    //         _isAtBegin=true;
    //     }
    // }
};

#endif
