#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Union-Find (Disjoint Set) structure to track set sizes
class UnionFind {
private:
    vector<int> parent;
    vector<int> size; // number of 1 in each disjoint set
    int max_area;    
    
public:
    // init with the sizes of the horizontal segments found in Step 1
    explicit UnionFind(int n, const vector<int>& initial_sizes) 
        : size(initial_sizes), max_area(0) {
        
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        
        // find the max area among the initial disconnected horizontal segments
        for (int s : size) {
            if (s > max_area) {
                max_area = s;
            }
        }
    }

    // finds the root island with inline path compression
    int find(int i) {
        return parent[i] == i ? i : (parent[i] = find(parent[i])); 
    }

    // unites two segments and updates the max area
    void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        
        if (rootI != rootJ) {
            parent[rootI] = rootJ; // merge sets
            
            // add the area of the merged set to the new root
            size[rootJ] += size[rootI]; 
            
            // dynamically update the max_area
            max_area = std::max(max_area, size[rootJ]);
        }
    }

    // return the maximum island size in O(1) time
    int getMaxArea() const {
        return max_area;
    }
};

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        const int rows = grid.size();
        const int cols = grid[0].size();
        
        // 2D grid to store the horizontal segment ID for each cell
        vector<vector<int>> horizontal_ids(rows, vector<int>(cols, -1));
        vector<int> segment_sizes; // stores the init area of each horizontal segment
        int current_id = 0;
        
        // find horizontal segments and their init sizes
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) { 
                    // a new segment starts
                    if (j == 0 || grid[i][j - 1] == 0) {
                        current_id++;
                        segment_sizes.push_back(0); // add a counter for the new segment
                    }
                    horizontal_ids[i][j] = current_id - 1;
                    
                    // increase+1 the size of the current horizontal segment
                    segment_sizes.back()++; 
                }
            }
        }
        
        // if no land was found
        if (current_id == 0) return 0;
        
        // init Union-Find with the sizes of horizontal segments
        UnionFind uf(current_id, segment_sizes);
        
        // check vertical adj and unite
        for (int i = 0; i < rows - 1; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1 && grid[i + 1][j] == 1) {
                    uf.unite(horizontal_ids[i][j], horizontal_ids[i + 1][j]);
                }
            }
        }
        return uf.getMaxArea();
    }
};
