#ifndef PORTS_H
#define PORTS_H

#include "types.h"

uint8 port_byte_in(uint16 port);
void port_byte_out(uint16 port, uint8 data);
uint16 port_word_int(uint16 port);
void port_word_out(uint16 port, uint16 data);
void io_wait();

#endif