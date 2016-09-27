#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>

using std::vector;

class VecCmp {
public:
  bool operator()(const vector<size_t> & v1, const vector<size_t> & v2) const {
    if (v1.size() != v2.size()) {
      return v1.size() < v2.size();
    }
    else {
      for (size_t i = 0; i < v1.size(); i++) {
	if (v1[i] != v2[i]) {
	  return v1[i] < v2[i];
	}
      }
      return false;
    }
  }
};

class solution {
public:
  int minPatches(const vector<int> & nums, int n) {
    auto equals = [](const vector<int> & v1, const vector<int> & v2) {
      if (v1.size() != v2.size())
	return false;
      else {
	for (size_t i = 0; i < v1.size(); i++)
	  if (v1[i] != v2[i])
	    return false;
	return true;
      }
    };
    auto curr = nums;
    std::for_each(curr.begin(), curr.end(), [](auto && d){std::cout << d << " ";});
    std::cout << std::endl;
    auto next = allsums(curr, n);
    while (!equals(curr, next)) {
      curr = next;
      std::for_each(curr.begin(), curr.end(), [](auto && d){std::cout << d << " ";});
      std::cout << std::endl;
      next = allsums(curr, n);
    }

    return curr.size()-nums.size();
  }

private:
  std::set<vector<size_t>, VecCmp> allSubsets(size_t len) {
    vector<vector<size_t>> perms;
    vector<size_t> start;
    for (size_t i = 0; i < len; i++)
      start.push_back(i);

    do {
      perms.push_back(start);
    } while (std::next_permutation(start.begin(), start.end()));

    std::set<vector<size_t>, VecCmp> subsets;
    for (size_t i = 1; i < len; i++) {
      for (auto vec : perms) {
	vector<size_t> temp(i);
	if (std::is_sorted(vec.begin(), vec.begin()+i)) {
	  std::copy(vec.begin(), vec.begin()+i, temp.begin());
	  subsets.insert(temp);
	}
      }
    }
    subsets.insert(perms[0]);
    return subsets;
  }

  vector<int> allsums(const vector<int> & nums, int n) {
    auto subsets = allSubsets(nums.size());
    vector<int> existingSums;
    for (auto it = subsets.begin(); it != subsets.end(); ++it) {
      // int sum = std::accumulate(nums.begin()+it->front()+std::distance(it->begin(),it->begin()), nums.begin()+it->front()+std::distance(it->begin(),it->end()), 0);
      int sum = 0;
      for (size_t i = 0; i < it->size(); i++)
	sum += nums[(*it)[i]];
      existingSums.push_back(sum);
    }

    std::sort(existingSums.begin(), existingSums.end());

    vector<int> nums_mod = nums;
    for (int i = 1; i <= n; i++) {
      if (std::find(existingSums.begin(), existingSums.end(), i) == existingSums.end()) {
	auto it = std::lower_bound(nums_mod.begin(), nums_mod.end(), i);
	nums_mod.insert(it, i);
	return nums_mod;
      }
    }
    return nums;
  }
};

int main() {

  // vector<int> nums{1,5,10};
  // int n = 20;

  // vector<int> nums{1,3};
  // int n = 6;

  vector<int> nums{1,2,2};
  int n = 5;

  solution soln;
  // auto perms = soln.allSubsets(3);
  // for (auto vec : perms) {
  //     for (auto n : vec) {
  //         std::cout << n << " ";
  //     }
  //     std::cout << std::endl;
  // }

  // auto subsets = soln.allSubsets(3);
  // for (auto it = subsets.begin(); it != subsets.end(); ++it) {
  //   for (size_t i = 0; i < it->size(); i++)
  //     std::cout << (*it)[i] << " ";
  //   std::cout << std::endl;
  // }
  int numPatches = soln.minPatches(nums, n);

  std::cout << "The minimum number of patches is:\n";
  std::cout << numPatches << std::endl;
}
