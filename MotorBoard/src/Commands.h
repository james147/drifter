#include <Arduino.h>

#ifndef Command_H
#define Command_H

class SerialCommands
{
public:
  SerialCommands();
  void begin(Stream *serial);
  void addCommand(char command, bool (*callback)(SerialCommands*));
  void processSerial();
  
private:

  struct Command {
    char command;
    bool (*callback)(SerialCommands*);
  };
  Command _commands[10];
  byte _number_commands;
  Stream *_serial;
  char _command_buffer[255];
  byte _buffer_length;
  
  void processCommand();
};

void serialEvent();

#endif // Command_H
