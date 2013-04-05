#include <iostream>
#include <cstring>

#include "hashutils.h"
#include "sha1.h"

using namespace std;

string 	sha1(string str)
{
	uint8_t* s = (uint8_t*) (str.c_str());
	SHA1Hash h;
	
	sha1_private(s, str.length(), &h);
	
	return SHA1HashToString(h);
}

void	sha1_private(uint8_t* str, size_t size, SHA1Hash* h)
{
	size_t tmpSize = toSHA1Size(8*size);
	size_t len = 8*size+1;
	
	while((len%512)!=448) len++;
	len/=8;
	
	uint8_t* msg = (uint8_t*) calloc(len+8, sizeof(uint8_t));
	
	memcpy(msg, str, size);
	msg[size] = 0x80;
	memcpy(msg+len, &tmpSize, 8); 
	
	h->h0 = 0x67452301;
	h->h1 = 0xEFCDAB89;
	h->h2 = 0x98BADCFE;
	h->h3 = 0x10325476;
	h->h4 = 0xC3D2E1F0;
	
	uint32_t W[80];
	uint32_t A,B,C,D,E, TEMP, VAL;

	for(int offset=0; offset<len+8; offset+=64)
	{
		for(int i=0; i<16; i++)
		{
			W[i] = msg[offset+4*i] << 24;
			W[i]|= msg[offset+4*i+1] << 16;
			W[i]|= msg[offset+4*i+2] << 8;
			W[i]|= msg[offset+4*i+3];
		}
		
		for(int i=16; i<80; i++)
		{
			W[i] = LEFTROTATE(W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16], 1);
		}
		
		A = h->h0; B = h->h1; C = h->h2; D = h->h3; E = h->h4;
		
		for(int t=0; t<80; t++)
		{
			if(t<20) VAL = SHA1_F(B,C,D);
			else if(t<40) VAL = SHA1_G_I(B,C,D);
			else if(t<60) VAL = SHA1_H(B,C,D);
			else VAL = SHA1_G_I(B,C,D);
		
			TEMP = LEFTROTATE(A , 5) + E + VAL + W[t] + SHA1_K[t/20];
			E=D;
			D=C;
			C=LEFTROTATE(B, 30);
			B=A;
			A=TEMP;
		}
		
		h->h0 += A; h->h1 += B; h->h2 += C; h->h3 += D; h->h4 += E;
	}
	
	free(msg);
}

size_t	toSHA1Size(size_t sha1Size)
{
	uint32_t low = (uint32_t) ((sha1Size << 32) >> 32);
	uint32_t high = (uint32_t) (sha1Size >> 32);
	
	low = littleEndian(low);
	high = littleEndian(high);
	
	size_t ret = 0;
	ret |= (size_t) high;
	ret |= ((size_t) low) << 32;
	
	return ret;
}

string	SHA1HashToString(SHA1Hash h)
{
	char buf[41] = {0};
	
	snprintf(buf, 41, "%.8x%.8x%.8x%.8x%.8x", h.h0, h.h1, h.h2, h.h3, h.h4);
	return string(buf);
}
