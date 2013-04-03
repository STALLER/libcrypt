#ifndef MD4_HEAD
#define MD4_HEAD

#include <iostream>
#include <stdint.h>

#define MD4_F(x,y,z) (((x)&(y))|((~(x))&(z)))
#define MD4_G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define MD4_H(x, y, z) ((x) ^ (y) ^ (z))

typedef struct MD4Hash
{
	uint32_t a,b,c,d;
} MD4Hash;

const uint8_t MD4_S[12] = {3,7,11,19, 3,5,9,13, 3,9,11,15};
const uint8_t MD4_K[48] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15, 0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

void		md4_private(uint8_t* str, size_t size, MD4Hash*);
void		MD4Hash2littleEndian(MD4Hash*);
std::string 	md4(std::string);
std::string	MD4Hash2string(MD4Hash);

#endif
