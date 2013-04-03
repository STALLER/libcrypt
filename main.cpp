#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>

#include "md5.h"
#include "md2.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc<2)
	{
		cout << "Usage : " << argv[0] << " <string>" << endl;
		return EXIT_FAILURE;
	}

	uint8_t h[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

	string s = md2((string) argv[1]);
	cout << "md2(" << argv[1] << ") = " << s << endl;

	s = md5((string) argv[1]);
	cout << "md5(" << argv[1] << ") = " << s << endl;

	return EXIT_SUCCESS;
}
