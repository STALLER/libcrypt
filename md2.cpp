#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdio>

#include "md2.h"

using namespace std;

string md2(string s)
{
	uint8_t* str = (uint8_t*) s.c_str();
	uint8_t h[16];

	md2private(str, (size_t) s.length(), h);

	return MD2HashToString(h);
}

string MD2HashToString(uint8_t h[16])
{
	char tmp[33] = {0};
	int n;

	for(int i=0; i<16; i++)
	{
		n = snprintf(tmp+2*i, 3, "%.2x", h[i]);
	}

	return string(tmp);
}

void md2private(uint8_t* str, size_t size, uint8_t h[16])
{
	size_t len = size;
	while(len%16) len++;

	int pad = (int) (len-size);

	uint8_t* msg = (uint8_t*) calloc(len, sizeof(uint8_t));
	memcpy(msg, str, size);
	for(int i=0; i<pad; i++) msg[size+i] = (uint8_t) pad;

	uint8_t C[16] = {0}, c;
	int L = 0;

	for(int i=0; i< len/16; i++)
	{
		for(int j=0; j<16; j++)
		{
			c = msg[i*16+j];
			C[j] = C[j] ^ MD2_S[c^L];
            cout << (int) c << " - " << L << " - " << (c^L) << " - " << (int) MD2_S[c^L] << endl;
			L = C[j];
		}
        cout << "---------------" << endl;
	}

    cout << "Checksum : " << MD2HashToString(C) << endl;

}
