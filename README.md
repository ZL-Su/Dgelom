# Dgelom
C++ codes for computer vision and numeric computation.

## 1. SIMD vectorization
We have released a stand-alone SIMD vectorization library "dge-simd" in Dgelom/support/arch. It is a portable modern C++ library for accelarating C/C++ code on Intel CPU platform. The dge-simd is simple since it includes only on core type and a sequence of operators. The core type named ```dgelom::Packet_``` with interface as:

``` template<typename _Ty, int _Elems> class Packet_```;

Example:

Define a 4-vector from a given scalar _Val

```dgelom::Packet_<float, 4> _Packed_4(_Val);``` // {_Val, _Val, _Val, _Val}

...or initializer list

```dgelom::Packet_<float, 4> _Packed_4{0.f, 1.f, 2.f, 3.f};``` // {0.f, 1.f, 2.f, 3.f}

...or from a pointer _Ptr with length at least is 4

```dgelom::Packet_<float, 4> _Packed_4(_Ptr);``` // {_Ptr[0], _Ptr[1], _Ptr[2], _Ptr[3]}

...or from a forward type _T with a pointer-returned method `.data()`

```dgelom::Packet_<float, 4> _Packed_4(_T(...).data());``` // {.data()[0], .data()[1], .data()[2], .data()[3]}

To be continued...
