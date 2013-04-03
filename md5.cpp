#include <iostream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <cstring>	// memcpy

#include <cstdio>	// sprintf_s

#include "md5.h"

using namespace std;

void md5_private(uint8_t* str, size_t size, MD5Hash* h)
{
	uint32_t *w, a, b, c, d, val=0, tmp;
	h->a = a0; h->b = b0; h->c = c0; h->d = d0;

	int g=0;
	// Calculation of new length

	size_t len = size*8 + 1;
	while((len%512) != 448) len++;
	len = len/8;

	uint8_t* msg = (uint8_t*) calloc(len + 64, sizeof(uint8_t));
	memcpy(msg, str, size);

	msg[size] = 0x80;	// Set bit 1

	uint32_t bitsSize = 8*size;
	memcpy(msg + len, &bitsSize, 4);

	for(unsigned int offset = 0; offset < len; offset += 64)
	{
		w = (uint32_t*) (msg+offset);
		a = a0; b = b0; c = c0; d = d0;

		for(int i=0; i<64; i++)
		{
			if(i<16)
			{
				val = F(b,c,d);
				g = i;
			} 
			else if (i<32)
			{
				val = G(b,c,d);
				g = (5*i+1)%16;
			}
			else if (i<48)
			{
				val = H(b,c,d);
				g = (3*i+5)%16;
			}
			else
			{
				val = I(b,c,d);
				g = (7*i)%16;
			}

			tmp = d;
			d = c;
			c = b;
			b += LEFTROTATE((a + val + MD5_K[i] + w[g]), MD5_S[i]);
			a = tmp;
		}

		h->a += a;
		h->b += b;
		h->c += c;
		h->d += d;
	}

	return;
}

uint32_t littleEndian(uint32_t n)
{
	uint32_t ret = 0;

	ret |= (n & (uint32_t) 0x000000ff) << 24;
	ret |= ((n & (uint32_t) 0x0000ff00) >> 8) << 16;
	ret |= ((n & (uint32_t) 0x00ff0000) >> 16) << 8;
	ret |= (n & (uint32_t) 0xff000000) >> 24;

	return ret;
}

void md5hash2littleEndian(MD5Hash* h)
{
	h->a = littleEndian(h->a);
	h->b = littleEndian(h->b);
	h->c = littleEndian(h->c);
	h->d = littleEndian(h->d);
}

string	md5hash2string(MD5Hash h)
{
	char buf[33] = {0};
	snprintf(buf, 33, "%.8x%.8x%.8x%.8x", h.a, h.b, h.c, h.d);

	return string(buf);
}

string md5(string str)
{
	size_t len = (size_t) str.length();
	uint8_t* tab = (uint8_t*) str.c_str();

	MD5Hash h;
	md5_private(tab, len, &h);
	md5hash2littleEndian(&h);

	return md5hash2string(h);
}
