#pragma once
#include <vector>
#include <algorithm>

class Solution
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