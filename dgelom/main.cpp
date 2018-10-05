#include <iostream>
#include "../leetcode/solutions.h"

int main() try
{
	// \leetcode solutions
	Leetcode_solution _Lcsol;

	std::vector<int> _H{ 1, 8, 6, 2, 5, 4, 8, 3, 7 };

	auto _Res = _Lcsol.maxArea(_H);


	system("pause");
	return 0;
}
catch (std::exception& _E) { throw _E; }