#include <Commands.h>

Command::Command() {}

_Commands::_Commands() :
    _currentCommand(0),
    _lastCommand(0),
    _queueSize(8)
{}

void _Commands::begin(int baud_rate) {
    Serial.begin(baud_rate);
}

Command _Commands::getNextCommand() {

}

void serialEvent() {
    while(Serial.available()) {
        char inChar = (char)Serial.read();

        if (inChar == '\r' || inChar == '\n') {
            Serial.println("Ok");
        }
    }
}

_Commands Commands;
