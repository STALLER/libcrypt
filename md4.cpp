#include <iostream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <cstring>	// memcpy

#include <cstdio>	// sprintf_s

#include "hashutils.h"
#include "md4.h"

using namespace std;

void md4_private(uint8_t* str, size_t size, MD4Hash* h)
{
	h->a = 0x67452301;
	h->b = 0xefcdab89;
	h->c = 0x98badcfe;
	h->d = 0x10325476;
	
	size_t len = 8*size+1, bits = 8*size;
	while((len%512)!=448) len++;
	len/=8;
	
	uint8_t* msg = (uint8_t*) calloc(len+8, sizeof(uint8_t));
	memcpy(msg, str, size);
	msg[size] = 0x80;
	memcpy(msg+len, &bits, 8);

	uint32_t *w;
	uint32_t a,b,c,d, val, s, tmp;
	
	for(int offset=0; offset < len; offset+=64)
	{
		w = (uint32_t*) (msg+offset);
		
		a = h->a; b = h->b; c = h->c; d = h->d;
		
		for(int i=0; i<48; i++)
		{
			if(i<16) val = MD4_F(b,c,d);
			else if(i<32) val = MD4_G(b,c,d) + 0x5A827999;
			else val = MD4_H(b,c,d) + 0x6ED9EBA1;
			
			val = LEFTROTATE(a + val + w[MD4_K[i]], MD4_S[(i%4) + 4*(i/16)]);
			
			tmp = d;
			d=c;
			c=b;
			b=val;
			a=tmp;
		}
		
		h->a += a;
		h->b += b;
		h->c += c;
		h->d += d;
	}
	
	free(msg);
}

string md4(string str)
{
	uint8_t* s = (uint8_t*) str.c_str();
	MD4Hash h;
	
	md4_private(s, str.length(), &h);
	MD4Hash2littleEndian(&h);
	
	return MD4Hash2string(h);
}

void MD4Hash2littleEndian(MD4Hash* h)
{
	h->a = littleEndian(h->a);
	h->b = littleEndian(h->b);
	h->c = littleEndian(h->c);
	h->d = littleEndian(h->d);
}

string	MD4Hash2string(MD4Hash h)
{
	char buf[33] = {0};
	snprintf(buf, 33, "%.8x%.8x%.8x%.8x", h.a, h.b, h.c, h.d);

	return string(buf);
}
