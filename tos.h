#ifndef __TOS_H
#define __TOS_H

#include <stdint.h>

// BIOS
int32_t Bconin(const int16_t dev);
int16_t Bconstat(const int16_t dev);
void Vsync();

// TOS
int32_t Cconin();
void Cconws(const char* s);
void Cconout(const uint16_t ch);
int32_t Cnecin();

void *Malloc(int32_t number);
int32_t Mfree(void *block);
int32_t Mshrink(void *block, int32_t newsize);

// XBIOS
int32_t Random();
int16_t Getrez();

#endif
