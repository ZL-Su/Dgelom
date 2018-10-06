/**************************************************************************
Copyright(C) 2018, Zhilong(Dgelom) Su, all rights reserved.
This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#pragma once
#include <memory>
#include "../dgelom/macro_def.h"

DGE_BEGIN
template<std::size_t _N>
struct _copy_n {
	template<typename _Ty> inline static
	void op(_Ty _Dst[], const _Ty& _Src, std::size_t _Pos) {
		_Dst[_N][_Pos] = (_Src[_Pos]);
		_copy_n<_N - 1>::op(_Dst, _Src, _Pos);
	}
};

template<>
struct _copy_n<0> {
	template<typename _Ty> inline static 
	void op(_Ty _Dst[], const _Ty& _Src, std::size_t _Pos) {
		_Dst[0][_Pos] = _Src[_Pos];
	}
};

template<std::size_t _N> struct _New_n
{
	template<typename _Ty> static
	DGE_HOST_FINL auto op(_Ty* _Ptr[], std::size_t _Size) {
		_Ptr[_N] = new _Ty[_Size];
		_New_n<_N - 1>::op(_Ptr, _Size);
	}
	template<typename _Ty> static
	DGE_HOST_FINL auto del(_Ty* _Ptr[]) {
		delete [] _Ptr[_N];
		_New_n<_N - 1>::del(_Ptr);
	}
};
template<> struct _New_n<0>
{
	template<typename _Ty> static
	DGE_HOST_FINL auto op(_Ty* _Ptr[], std::size_t _Size) {
		_Ptr[0] = new _Ty[_Size];
	}
	template<typename _Ty> static
	DGE_HOST_FINL auto del(_Ty* _Ptr[]) {
		delete [] _Ptr[0];
	}
};

DGE_END
