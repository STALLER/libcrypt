#ifndef MAIN_HEAD
#define MAIN_HEAD

#include <iostream>

typedef struct
{
	bool 		found;
	std::string	arg;
} Argument;

void	usage(std::string);
void	findArg(char, Argument*, int, char**);
bool	inStringArray(std::string, std::string*, size_t);

#endif
