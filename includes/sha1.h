#ifndef SHA1_HEAD
#define SHA1_HEAD

#include <iostream>
#include <cstdint>

#define SHA1_F(B,C,D)		(((B) & (C)) | ((~(B)) & (D)))
#define SHA1_G_I(B,C,D)		((B) ^ (C) ^ (D))
#define SHA1_H(B,C,D)		(((B) & (C)) | ((B) & (D)) | ((C) & (D)))

typedef struct
{
	uint32_t h0, h1, h2, h3, h4;
} SHA1Hash;

const uint32_t	SHA1_K[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};

std::string	sha1(std::string);
void		sha1_private(uint8_t*, size_t, SHA1Hash*);
size_t		toSHA1Size(size_t);
std::string	SHA1HashToString(SHA1Hash);

#endif
