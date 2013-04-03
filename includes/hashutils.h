#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <iostream>
#include <cstdint>

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

uint32_t	littleEndian(uint32_t);

#endif
