#include <iostream>
#include <array>
#include <adept.h>
#include <adept_source.h>
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

template<std::size_t _N = 0>  struct _Reduce_n {
	template<typename _Ty>
	static inline constexpr auto value(const _Ty* _Data[[_N]]) {
		return (_Reduce_n<_N - 1>::value(_Data) + _Data[_N]);
	}
};
template<> struct _Reduce_n<0> {
	template<typename _Ty>
	static inline constexpr auto value(const _Ty* _Data[[]]) {
		return (_Data[0]);
	}
};

using adept::adouble;
adouble afunc(const adouble x[2]) {
	adouble y = 4.0;
	adouble s = 2.*x[0] + 3.*x[1] * x[1];
	y *= std::sin(s.value());
	return y;
}

std::tuple<double, double, double> func_and_grad(const double x_val[2]) {
	adept::Stack stack;
	adouble x[2]{ x_val[0], x_val[1] };

	stack.new_recording();
	adouble y = afunc(x);
	y.set_gradient(1.0);
	stack.compute_adjoint();

	return std::make_tuple(y.value(), x[0].get_gradient(), x[1].get_gradient());
}

int main() try
{
	// \leetcode solutions
	Leetcode_solution _Lcsol;
	std::vector<std::string> _Strs = { "c","acc","ccc" };
	auto _Prefix = _Lcsol.longestCommonPrefix(_Strs);

	double x_val[] = { 0.5, 1.0 };
	auto [y, dy_dx1, dy_dx2] = func_and_grad(x_val);


	system("pause");
	return 0;
}
catch (std::exception& _E) { throw _E; }