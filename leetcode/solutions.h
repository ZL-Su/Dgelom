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
#include <cctype>
#include <vector>
#include <algorithm>

class Leetcode_solution
{
	struct ListNode {int val;ListNode *next;ListNode(int x) : val(x), next(nullptr) {}};
public:
	// \Problem 1. Two Sum
	std::vector<int> twoSum(std::vector<int>& _Nums, int _Target) {
		for (auto _Begin = _Nums.begin(); _Begin != _Nums.end(); ++_Begin) {
			auto _Pos = std::find_if(_Begin + 1, _Nums.end(), [&_Begin, _Target](const auto& _Val)->bool {
				return ((*_Begin + _Val) == _Target);
			});
			if (_Pos != _Nums.end()) {
				return { (int)std::distance(_Nums.begin(), _Begin), (int)std::distance(_Nums.begin(), _Pos) };
			}
		}

		return (std::vector<int>());
	}

	// \Problem 2. Add Two Numbers
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		using value_type = int;

		auto _Zero_root = new ListNode(0);
		auto _Ret = _Zero_root;
		value_type _Tens_holder = 0;
		for (auto _L = l1, _R = l2; _L || _R;) {

			auto _Value = (_L ? _L->val : 0) + (_R ? _R->val : 0) + _Tens_holder;
			_Tens_holder = _Value / 10;
			_Value = _Tens_holder == 1 ? _Value - 10 : _Value;

			_Ret->next = new ListNode(_Value);
			_Ret = _Ret->next;
			_L = _L ? _L->next : nullptr;
			_R = _R ? _R->next : nullptr;
		}
		_Ret->next = _Tens_holder == 1 ? new ListNode(_Tens_holder) : nullptr;
		_Ret = _Zero_root->next;
		delete _Zero_root;

		return (_Ret);
	}

	// Problem 3. Longest Substring Without Repeating Characters
	int lengthOfLongestSubstring(std::string s) {
		std::size_t _Len = 0, _Pos;
		std::string _Sub;

		for (const auto& _Val : s) {
			_Pos = _Sub.find(_Val);
			if (_Pos != _Sub.npos) {
				_Sub = _Sub.substr(_Pos + 1);
			}
			_Sub += _Val;
			_Len = std::max(_Len, _Sub.length());
		}

		return static_cast<int>(_Len);
	}

	// Problem 4. Median of Two Sorted Arrays
	double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
		std::vector<int> _Merge(nums1.begin(), nums1.end());
		_Merge.insert(_Merge.end(), nums2.begin(), nums2.end());
		//std::sort(_Merge.begin(), _Merge.end());
		_Merge_sort(_Merge.begin(), _Merge.end());

		auto _Size = _Merge.size();
		auto _Half = _Size >> 1;
		if (_Size % 2) {
			return (_Merge[_Half]);
		}
		return (_Merge[_Half - 1] + _Merge[_Half])*0.5;
	}

	// Problem 7. Reverse Integer
	int reverse(int x) {
		using int64_type = long long;

		int64_type _Ret = 0;
		while (x) {
			_Ret = _Ret * 10 + x % 10;
			x /= 10;
		}

		return (_Ret > INT_MAX || _Ret < INT_MIN ? 0 : _Ret);
	}

	// Problem 8. String to Integer (atoi)
	int myAtoi(std::string _Str) {
		int _Ret = 0;
		if (_Str.empty() || std::isalpha(*_Str.begin())) return _Ret;
		
		auto _It = _Str.begin();
		for (; _It < _Str.end();) {
			if (std::isspace(*_It)) ++_It;
			else break;
		}
		if (std::isalpha(*_It)) return _Ret;

		int _Sign = 1;
		if (*_It == '+') ++_It;
		else if (*_It == '-') {
			_Sign = -1;
			++_It;
		}
		if (!std::isdigit(*_It)) return _Ret;

		int _Temp;
		for (; _It < _Str.end(); ++_It) {
			auto _Cval = *_It;
			if (std::isdigit(_Cval)) {
				_Temp = _Ret;
				_Ret = _Ret * 10 + *_It - '0';
				if (_Ret < 0 || _Temp != (_Ret - (*_It - '0')) / 10)
					return _Sign == 1 ? INT_MAX : INT_MIN;
			}
			else break;
		}
		return _Ret * _Sign;
	}

	// \Problem 9. Palindrome Number
	bool isPalindrome(int x) {
		if (x < 0) return false;
		if (x < 10) return true;

		int _Temp = x, _Pali = 0;
		while (_Temp) {
			auto _Single = _Temp % 10;
			_Pali = _Pali * 10 + _Single;
			_Temp = (_Temp - _Single)/10;
		}

		return (_Pali == x ? true : false);
	}

	// \Problem 11. Container With Most Water [O(n^2)]
	int maxArea(std::vector<int>& height) {
		const auto& _H = height;
		if (_H.size() < 2) return 0;
		int _Max_area = 0;

		// Solu 1: bruteforce method
		for (auto _It = _H.begin(); _It < _H.end(); ++_It) {
			for (auto _Pos = _It + 1; _Pos < _H.end(); ++_Pos) {
				auto _Area = std::min(*_It, *_Pos)*std::distance(_It, _Pos);
				_Max_area = _Max_area > _Area ? _Max_area : _Area;
			}
		}

		// Solu 2:

		return _Max_area;
	}

private:
	template<class Iter>
	void _Merge_sort(Iter first, Iter last)
	{
		if (last - first > 1) {
			Iter middle = first + (last - first) / 2;
			_Merge_sort(first, middle);
			_Merge_sort(middle, last);
			std::inplace_merge(first, middle, last);
		}
	}
};