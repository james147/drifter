#include "Commands.h"

HardwareSerial *serials[3];

SerialCommands::SerialCommands() : _serial(0), _bufferLength(0), _timeout(100), _escaped(false)
{}

void SerialCommands::begin(Stream *serial) {
  this->_serial = serial;
}

void SerialCommands::_parse_command()
{
  Command command;
  command.id = word(_command_buffer[0], _command_buffer[1]);
  command.command = _command_buffer[2];
  
}

bool SerialCommands::processSerial()
{
  while (Serial.available()) {
    byte in = Serial.read();
    
    // Look for special chars is not escaped
    if (!_escaped) {
      switch(in) {
        case '\\':
          _escaped = true;
          break;
        case '$':
          _buffer_length = 0;
          break;
        case '%':
          _parseCommand();
          _buffer_length = 0;
          break;
      }
    } else {
      _escaped = false;
      if (_buffer_length == 255) {
        return false;
      }
      _command_buffer[_buffer_length++] = in;
    }
  }
}

Command SerialCommands::next()
{
  // No commands waiting
  if (!_serial->available()) {
    return (Command){0, 0, 0};
  }
  long start_time = millis();
  // Attempt to read the next command
  while (true) {
    // See if we are taking to long
    if (millis() - start_time > _timeout) {
      return (Command){0, 0, 0};
    }
    
    int nextByte = _serial->read();
    if (nextByte == -1) {
      continue;
    }
    
    char c = nextByte;
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