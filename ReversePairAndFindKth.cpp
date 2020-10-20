#include<vector>
#include<iostream>

using namespace std;

namespace reverse_pair {
	void mergeEntry(vector<int> nums, int& count, int left, int mid, int right) {
		vector<int> temp(right - left + 1, 0);
		int i = left;
		int j = mid + 1;
		int index = 0;
		while (i <= mid && j <= right) {
			if (nums[i] > nums[j]) {
				count += mid - i + 1;
				temp[index++] = nums[j++];
			}
			else {
				temp[index++] = nums[i++];
			}
		}

		while (i <= mid) {
			temp[index++] = nums[i++];
		}

		while (j <= right) {
			temp[index++] = nums[j++];
		}
	}

	void merge(vector<int>& nums, int& count, int left, int right) {
		if (left >= right) return;
		int mid = left + (right - left) / 2;
		merge(nums, count, left, mid);
		merge(nums, count, mid + 1, right);
		mergeEntry(nums, count, left, mid, right);
	}

	int merge(vector<int> nums) {
		int count = 0;
		merge(nums, count, 0, nums.size()-1);
		return count;
	}

}


namespace findKth {
	int paration(vector<int> nums, int left, int right) {
		int i = left;
		for (int j = left; j < right; j++) {
			if (nums[j] < nums[right]) {
				if (i != j) {
					swap(nums[i], nums[j]);
				}
				i++;
			}
		}
		swap(nums[i], nums[right]);
		return i;
	}

	int findKth(vector<int> nums, int left, int right, int& k) {
		
		int mid = paration(nums, left, right);
		if (mid > k - 1) {
			return findKth(nums, left, mid - 1, k);
		}
		else if (mid < k - 1) {
			return findKth(nums, mid + 1, right, k);
		}
		else {
			return nums[mid];
		}
	}

	int quickFindVarious(vector<int>& nums) {
		int k = 7;
		return findKth(nums, 0, nums.size() - 1, k);
	}
}



int main1() {
	//排序算法都可以应对有重复的问题；
	vector<int> vi = { 30,20,10,10,15,4,8,40,80,20,9 };
	cout<<findKth::quickFindVarious(vi)<<endl;

	cout << reverse_pair::merge(vi) << endl;
	return 0;
}



