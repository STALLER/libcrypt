#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>

#include "hashutils.h"
#include "md5.h"
#include "md2.h"
#include "md4.h"
#include "sha1.h"

#define NALGO 4
#define ALGOS "md2", "md4", "md5", "sha1"

using namespace std;

int main(int argc, char** argv)
{
	if(argc<2)
	{
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
