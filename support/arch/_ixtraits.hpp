#pragma once
#include <type_traits>
#include "../../dgelom/macro_def.h"
#ifdef __AVX__
#include <mmintrin.h>    //_m64
#include <emmintrin.h>   //_m128
#include <immintrin.h>   //_m256
#include <zmmintrin.h>   //_m512
DGE_BEGIN

template<typename T> struct is_common_int64 { enum { value = std::is_integral_v<T> && sizeof(T) == 8 }; };
template<typename T> struct is_int64 { enum { value = std::is_signed_v<T> && std::is_integral_v<T> && sizeof(T) == 8 }; };
template<typename T> struct is_uint64 { enum { value = std::is_unsigned_v<T> && std::is_integral_v<T> && sizeof(T) == 8 }; };
template<typename T> struct is_float32 { enum { value = std::is_floating_point<T>::value && (sizeof(T) == 4) }; };
template<typename T> struct is_float64 { enum { value = std::is_floating_point<T>::value && (sizeof(T) == 8) }; };

#pragma region <!-- simd traits -->
template<typename T, int _Elems> struct conditional {};
template<typename T> struct conditional<T, 2>
{
	using type = std::conditional_t<is_common_int64<T>::value, __m128i, std::conditional_t<is_float32<T>::value, __m64, std::conditional_t<is_float64<T>::value, __m128d, void>>>;
};
template<typename T> struct conditional<T, 4>
{
	using type = std::conditional_t<is_common_int64<T>::value, __m256i, std::conditional_t<is_float32<T>::value, __m128, std::conditional_t<is_float64<T>::value, __m256d, void>>>;
};
template<typename T> struct conditional<T, 8>
{
	using type = std::conditional_t<is_common_int64<T>::value, __m512i, std::conditional_t<is_float32<T>::value, __m256, std::conditional_t<is_float64<T>::value, __m512d, void>>>;
};
template<typename T> struct conditional<T, 16>
{
	using type = typename std::conditional_t<is_float32<T>::value, __m512, typename std::conditional_t<is_float64<T>::value, __m512d, void>>;
};
template<typename T, int _Elems> using conditional_t = typename conditional<T, _Elems>::type;

template<typename T, int _Elems> struct simd_traits
{
	struct is_sfp8 { enum { value = is_float32<T>::value && _Elems == 8 }; };
	struct is_dfp8 { enum { value = is_float64<T>::value && _Elems == 8 }; };
};
template<typename T, int _Elems> _INLINE_VAR
constexpr auto is_simd_sfx8_v = simd_traits<T, _Elems>::is_sfp8::value;
template<typename T, int _Elems> _INLINE_VAR
constexpr auto is_simd_dfx8_v = simd_traits<T, _Elems>::is_dfp8::value;
#pragma endregion
DGE_END
#endif // __AVX__