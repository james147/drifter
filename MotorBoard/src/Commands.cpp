#include "Commands.h"

SerialCommands::SerialCommands() : _serial(0), _buffer_length(0), _number_commands(0)
{}

void SerialCommands::begin(Stream *serial) {
  this->_serial = serial;
}

void SerialCommands::addCommand(char command, bool (*callback)(SerialCommands*))
{
  _commands[_number_commands++] = { command, callback };
}

void SerialCommands::processSerial()
{
  while (Serial.available()) {
    byte in = Serial.read();
    
    if (in == '\r') {
      processCommand();
      _buffer_length = 0;
      _command_buffer[0] = 0;
      return;
    }
    if (_buffer_length == 254) {
      Serial.println("Buffer full, clearing buffer");
      _command_buffer[_buffer_length++] = in;
      _command_buffer[_buffer_length] = 0;
      return;
    }
      _command_buffer[_buffer_length++] = in;
      _command_buffer[_buffer_length] = 0;
  }
}

void SerialCommands::processCommand()
{
  if (_buffer_length < 3) {
    Serial.print("Error: command long long enough");
    return;
  }
  Serial.print("Receved: ");
  int command_id = _command_buffer[0] << 8 | _command_buffer[1];
  char command_char = _command_buffer[2];
  Serial.print(command_id);
  Serial.print(", ");
  Serial.print(command_char);
  Serial.println();
}
