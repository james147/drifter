#include <Arduino.h>

#ifndef Command_H
#define Command_H

struct Command {
  int id
  char command;
  byte length;
  byte *args;
};

class SerialCommands
{
public:
  SerialCommands();
  void begin(Stream *serial);
  Command next();
  bool processSerial();
  
private:
  Stream *_serial;
  char _command_buffer[255];
  byte _buffer_length;
  bool _escaped;
  
  void _parse_command();
};

void serialEvent();

#endif // Command_H
