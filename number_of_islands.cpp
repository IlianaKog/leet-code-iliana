#include <vector>
using namespace std;

// gia kathe grammi orizontia i, koitame apo poio mexri poio j uparxoun sunexomenoi "1", kathe omada apo "1" pairnei ena unique ID.
// epeita enwnoume ta epimerous orizontia nhsia: 
// an vroume 2 komvous apo 2 orizontia nhsia na isxuei idio j diaforetiko i (ta i diaferoun kata 1) tote enwnoume ta nhsia se ena.


// Union-Find (disjoint set) structure to merge components
class UnionFind {
private:
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.resize(n);
        // init: each horizontal segment is its own parent (separate island)
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // finds the root island to which segment i belongs
    int find(int i) {
        if (parent[i] == i) return i;
        // path compression for optimization - O(1) 
        return parent[i] = find(parent[i]); 
    }

    // unites two horizontal segments (i and j)
    void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ; // make one root point to the other
        }
    }

    // counts the total number of independent islands left at the end
    int countIslands() {
        int count = 0;
        for (int i = 0; i < parent.size(); ++i) {
            if (parent[i] == i) count++;
        }
        return count;
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int rows = grid.size();
        int cols = grid[0].size();
        
        // 2D grid to store the horizontal segment ID for each cell
        vector<vector<int>> horizontal_ids(rows, vector<int>(cols, -1));
        int current_id = 0;
        
        // find horizontal segments
        for (int i = 0; i < rows; ++i) {
            bool in_segment = false;
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    if (!in_segment) {
                        // found the start of a new horizontal segment
                        current_id++;
                        in_segment = true;
                    }
                    // assign the current ID (0-indexed)
                    horizontal_ids[i][j] = current_id - 1;
                } else {
                    //the current segment ends
                    in_segment = false;
                }
            }
        }
        
        // if no horizontal segments were found, there is no land
        if (current_id == 0) return 0;
        
        // initialize Union-Find based on the total number of horizontal segments found
        UnionFind uf(current_id);
        
        // check vertical adjacencies and unite (Disjoint-Set Union)
        // check each row (except the last one) against the one immediately below it
        for (int i = 0; i < rows - 1; ++i) {
            for (int j = 0; j < cols; ++j) {
                // if a cell and the one exactly below it are both land...
                if (grid[i][j] == '1' && grid[i+1][j] == '1') {
                    // unite their horizontal segment IDs
                    uf.unite(horizontal_ids[i][j], horizontal_ids[i+1][j]);
                }
            }
        }
        return uf.countIslands();
    }
};




