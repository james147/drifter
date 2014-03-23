#include <Arduino.h>

#ifndef Command_H
#define Command_H

struct Command {
  char id;
  byte length;
  byte *args;
};

class SerialCommands
{
public:
  SerialCommands();
  void begin(Stream *serial);
  Command next();
  
private:
  Stream *_serial;
  char _commandBuffer[];
  byte _bufferLength;
};

void serialEvent();

#endif // Command_H
