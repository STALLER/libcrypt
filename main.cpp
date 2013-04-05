#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>

#include "main.h"
#include "hashutils.h"
#include "md5.h"
#include "md2.h"
#include "md4.h"
#include "sha1.h"

#define NALGO 4
#define ALGOS "md2", "md4", "md5", "sha1"

using namespace std;

int 	main(int argc, char** argv)
{
	string algos[NALGO] = {ALGOS};
	
	Argument listAlg;
	findArg('l', &listAlg, argc, argv);

	if(listAlg.found)
	{
		cout << "Usable Hash functions :" << endl;
		for (int i=0; i<NALGO; i++)
			cout << algos[i] << endl;

		return EXIT_SUCCESS;
	}
	
	Argument algo, str;
	findArg('a', &algo, argc, argv);
	findArg('s', &str, argc, argv);

	if(algo.arg.length() && !inStringArray(algo.arg, algos, NALGO))
	{
		cout << "Unimplemented algorithm '" << algo.arg << "'" << endl;
		exit(2);
	}

	string s = (str.found) ? str.arg : string("");
	bool all = !algo.found;

	cout << "crypt <" << s << ">" << endl << endl;

	if(all || inStringArray("md2", algos, NALGO)) cout << "md2 " << md2(s) << endl;
	if(all || inStringArray("md4", algos, NALGO)) cout << "md4 " << md4(s) << endl;
	if(all || inStringArray("md5", algos, NALGO)) cout << "md5 " << md5(s) << endl;
	if(all || inStringArray("sha1", algos, NALGO)) cout << "sha1 " << sha1(s) << endl;

	return EXIT_SUCCESS;
}

void	usage(string pgName)
{
	cout << "Usage: " << pgName << " [-a<algorithm>] [-s<string>] | [-l]" << endl << endl;
	cout << "\t-a<algo> : Select a specific algorithm to be applied. If not used, outputs a line for each algorithm" << endl;
	cout << "\t-s<string> : The string to be hashed. If not used, gives the hash of '' (empty string)" << endl;
	cout << "\t-l : List algorithms in use" << endl << endl;
	exit(1);
}

void	findArg(char argName, Argument* ret, int argc, char** argv)
{
	ret->found = false;

	for(int i=1; i<argc; i++)
	{
		if(argv[i][0] == '-' && argv[i][1] == argName)
		{
			ret->arg = string(argv[i]+2);
			ret->found = true;
			break;
		}
	}
}

bool	inStringArray(string needle, string* haystack, size_t arraySize)
{
	for(size_t i=0; i<arraySize; i++)
	{
		//cout << needle << " " << haystack[i] << endl;
		if(needle == haystack[i]) return true;
	}

	return false;
}
