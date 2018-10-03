/***************************************************************************
This file is part of Matrice, an effcient and elegant C++ library for SC.
      Copyright(C) 2018, Zhilong (Dgelom) Su (su-zl@seu.edu.cn), 
		                   all rights reserved.

This program is free software : you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once
#include <type_traits>
#include <tuple>
#include "../dgelom/macro_def.h"

DGE_BEGIN

template<typename _Pixty, typename = typename std::enable_if<std::is_arithmetic<_Pixty>::value>::type>
DGE_HOST_FINL void _Grayscale_stretch(_Pixty* Img, std::size_t rows, std::size_t cols)
{
	typedef _Pixty                         pixel_t;
	typedef pixel_t*                      iterator;

	const std::size_t N = rows * cols;
	iterator _Begin = Img, _End = Img + N;

	pixel_t _Max = pixel_t(0), _Min = pixel_t(255);
	for (; _Begin != _End; ++_Begin)
	{
		_Max = _Max > *_Begin ? _Max : *_Begin;
		_Min = _Min < *_Begin ? _Min : *_Begin;
	}

	float_t _Scal = 255.f / float_t(_Max - _Min);
	for (_Begin -= N; _Begin != _End; ++_Begin)
		*_Begin = pixel_t(_Scal * (*_Begin - _Min));
}

// Usage: auto [x_begin, x_end, dx] = _Tidy_axis(x, max_x, x0, x1);
template<typename _Valty> DGE_HOST_FINL
std::tuple<int, int, _Valty> _Tidy_axis(_Valty x, int limx, int x0, int x1)
{
	const auto ix = static_cast<int>(x);
	if (ix < 0) return std::make_tuple(0, 0, _Valty(0));
	if (ix > limx - 2) return std::make_tuple(limx - 1, limx - 1, _Valty(1));
	return std::make_tuple(ix, ix + 1, ix + 1 - x);
}
//_Imty - image type, _Gdty - matrix type; If they are user defined type, cols() and rows() methods should be implemented for accessing the number of column, and the number of row. In addition, operator()(size_t _Col, size_t _Row) is neccessary for accessing the element at position (_Col, _Row).
//img - image, gx - gradient in x direction, gy - gradient in y direction, x[2] - coordinate of interpolation point for input, which will be overwritten by the interpolated gradients; return interpolated image intensity.
template<typename _Imty, typename _Gdty, typename _Valty> DGE_HOST_FINL
_Valty _Bilinear_interp(const _Imty& img, const _Gdty& gx, const _Gdty& gy, _Valty x[2])
{
	using Image_t = _Imty;
	using Matrx_t = _Gdty;
	using pixel_t = typename Image_t::value_t;
	using value_t = std::common_type_t<typename Matrx_t::value_t, _Valty>;

	int x0, x1, y0, y1;
	auto dx = _Tidy_axis(x[0], img.cols(), x0, x1);
	auto dy = _Tidy_axis(x[1], img.rows(), y0, y1);
	auto dxt = 1.0 - dx, dyt = 1.0 - dy;
	auto _Interp = [&](auto _F11, auto _F12, auto _F21, auto _F22)->auto 
	     { return dy * (dx*_F11 + dxt*_F12) + dyt*(dx*_F21 + dxt*_F22); };

	auto Gx11 = value_t(gx(x0, y0)), Gx12 = value_t(gx(x1, y0));
	auto Gx21 = value_t(gx(x0, y1)), Gx22 = value_t(gx(x1, y1));
	x[0] = _Interp(Gx11, Gx12, Gx21, Gx22);

	auto Gy11 = value_t(gy(x0, y0)), Gy12 = value_t(gy(x1, y0));
	auto Gy21 = value_t(gy(x0, y1)), Gy22 = value_t(gy(x1, y1));
	x[1] = _Interp(Gy11, Gy12, Gy21, Gy22);

	auto I11 = value_t(img(x0, y0)), I12 = value_t(img(x1, y0));
	auto I21 = value_t(img(x0, y1)), I22 = value_t(img(x1, y1));
	return _Interp(I11, I12, I21, I22);
}

// Value of k-th B-Spline basic function at t.
template<typename _T, typename = std::enable_if_t<std::is_arithmetic_v<_T>>>
DGE_HOST_FINL constexpr _T _Bspline_kernel(size_t k, _T t) {
	assert(0 <= t && t < 1);
	assert(k < 4);

	switch (k) {
	case 0: return (t * (t * (-t + 3) - 3) + 1) / 6;
	case 1: return (t * t * (3 * t - 6) + 4) / 6;
	case 2: return (t * (t * (-3 * t + 3) + 3) + 1) / 6;
	case 3: return t * t * t / 6;
	default: return 0;
	}
}

DGE_END
