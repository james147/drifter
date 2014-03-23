#include "Commands.h"

HardwareSerial *serials[3];

SerialCommands::SerialCommands() : _serial(0), _bufferLength(0)
{}

void SerialCommands::begin(Stream *serial) {
  this->_serial = serial;
}

Command SerialCommands::next()
{
  // Attempt to read the next command
  while (_serial->available()) {
    char c = _serial->read();
    if (c == '\n') {
      // We have found the end of the command, convert buffer into command
      Command command;
      command.id = _commandBuffer[0];
      command.length = _bufferLength - 1;
      command.args = (byte*)_commandBuffer + 1;
      // Reset buffer
      _bufferLength = 0;
      return command;
    }
    _commandBuffer[_bufferLength] = c;
    _bufferLength++;
  }
  // Command not complete, return a null command
  return (Command){0, 0, 0};
}

void serialEvent() {
}