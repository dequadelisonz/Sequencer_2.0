/******************************************************************************
Class CycleEngine

*******************************************************************************/

#ifndef CYCLEENGINE_H
#define CYCLEENGINE_H

#include <chrono>

class CycleEngine
{

private:

protected:
    bool _isRunning = true;

public:
    virtual bool onUserCreate() = 0;
    virtual bool onUserUpdate(float elapsedTime) = 0;
    // virtual bool onUserDestroy() { return true; }

    CycleEngine()
    {
    }

    void start()
    {
        if (!onUserCreate())
        {
            _isRunning = false;
            std::cerr << "Something with cycle initialization went wrong" << std::endl;
        }

        // std::chrono::steady_clock::time_point tp1 = std::chrono::steady_clock::now();
        // std::chrono::steady_clock::time_point tp2;
        auto tp1 = std::chrono::system_clock::now();
        auto tp2 = std::chrono::system_clock::now();

        while (_isRunning)
        {
            tp2 = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsedTime = tp2 - tp1;
            tp1 = tp2;
            _isRunning = onUserUpdate(elapsedTime.count());
        }
    };
};

#endif
