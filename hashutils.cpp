#include <iostream>
#include <cstdint>

#include "hashutils.h"

using namespace std;

uint32_t littleEndian(uint32_t n)
{
	uint32_t ret = 0;

	ret |= (n & (uint32_t) 0x000000ff) << 24;
	ret |= ((n & (uint32_t) 0x0000ff00) >> 8) << 16;
	ret |= ((n & (uint32_t) 0x00ff0000) >> 16) << 8;
	ret |= (n & (uint32_t) 0xff000000) >> 24;

	return ret;
}