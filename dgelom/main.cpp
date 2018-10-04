#include <iostream>
#include "../leetcode/solutions.h"

int main() try
{
	// \leetcode solutions
	Leetcode_solution _Lcsol;

	std::string _Str = "2147483648";
	auto _Res = _Lcsol.myAtoi(_Str);


	system("pause");
	return 0;
}
catch (std::exception& _E) { throw _E; }