#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;

class VecCmp {
    public:
        bool operator() (const vector<size_t> & v1, const vector<size_t> & v2) const {
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
}

class solution {
    public:
        int minPatches(const vector<int> & nums, int n) {
            return 0;
        }

    public:
        std::set<vector<size_t>, VecCmp> allSubsets(size_t len) {
            vector<vector<size_t>> perms;
            vector<size_t> start;
            for (size_t i = 0; i < len; i++)
                start.push_back(i);

            do {
                perms.push_back(start);
            } while (std::next_permutation(start.begin(), start.end()));

            std::set<vector<size_t>, VeCmp> subsets;
            for (size_t i = 1; i < len; i++) {
                
            }
        }
};

int main() {

    solution soln;
    auto perms = soln.allSubsets(3);
    for (auto vec : perms) {
        for (auto n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }
}