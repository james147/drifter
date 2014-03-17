#include <Arduino.h>

#ifndef Command_H
#define Command_H

class Command
{
    public:
        Command();
};

class _Commands
{
    public:
        _Commands();
        void begin(int baud_rate);
         Command getNextCommand();
    private:
        const byte queueSize;
        Command _commandQueue[8];
        byte _currentCommand;
        byte _lastCommand;
};

extern _Commands Commands;
void test();
void serialEvent();

#endif // Command_H
