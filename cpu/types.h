#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint32;
typedef int sint32;
typedef unsigned short uint16;
typedef short sint16;
typedef unsigned char uint8;
typedef char sint8;

#define low_16(address) (uint16)((address) & 0xffff)
#define high_16(address) (uint16)(((address) >> 16) & 0xffff)

#endif