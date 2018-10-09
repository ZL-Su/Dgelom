#include <iostream>
#include <array>
#include "../leetcode/solutions.h"
#include "../utils/copy.h"


#define _NODE_LIST(type) \
struct node_of_ ##type { \
type value; \
struct node_of_ ##type * next; \
};

template<std::size_t N> struct fib_const {
	static constexpr std::size_t value =
		fib_const<N - 1>::value + fib_const<N - 2>::value;
};
template<> struct fib_const<1> {
	static constexpr std::size_t value = 1;
};
template<> struct fib_const<0> {
	static constexpr std::size_t value = 0;
};

template<typename _Ty = void>
constexpr int my_sizeof() { return sizeof(_Ty); }
template<> constexpr int my_sizeof() { return 1; }

template<typename _Ty>
const_auto_exp is_array = false;
template<typename _Ty>
const_auto_exp is_array<_Ty[]> = true;
template<typename _Ty, std::size_t _N>
const_auto_exp is_array<_Ty[_N]> = true;

TPL_TY bool is_pointer(_Ty x) { return false; }
TPL_TY bool is_pointer(_Ty *x) { return true; }

int main() try
{
	// \leetcode solutions
	Leetcode_solution _Lcsol;
	std::vector<std::string> _Strs = { "c","acc","ccc" };
	auto _Prefix = _Lcsol.longestCommonPrefix(_Strs);

	system("pause");
	return 0;
}
catch (std::exception& _E) { throw _E; }