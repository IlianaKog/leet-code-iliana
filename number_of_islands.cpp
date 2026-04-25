#include <vector>
#include <numeric> 
using namespace std;

// gia kathe grammi orizontia i, koitame apo poio mexri poio j uparxoun sunexomenoi "1", kathe omada apo "1" pairnei ena unique ID.
// epeita enwnoume ta epimerous orizontia nhsia: 
// an vroume 2 komvous apo 2 orizontia nhsia na isxuei idio j diaforetiko i (ta i diaferoun kata 1) tote enwnoume ta nhsia se ena.


// Union-Find (Disjoint Set) structure
class UnionFind {
private:
    vector<int> parent;
    int count; // dynamically track the number of disjoint sets
    
public:
    // use explicit constructor and member initializer list
    explicit UnionFind(int n) : count(n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
    }

    // finds the root island with path compression
    int find(int i) {
        // inline path compression
        return parent[i] == i ? i : (parent[i] = find(parent[i])); 
    }

    // unites two horizontal segments
    void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ; // merge sets
            count--; // decrease total island count upon successful merge
        }
    }

    // return the current number of islands in O(1)
    int getCount() const {
        return count;
    }
};

class Solution {
public:
    // pass by const reference to avoid copying data
    int numIslands(const vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        const int rows = grid.size();
        const int cols = grid[0].size();
        
        // 2D grid to store the horizontal segment ID for each cell
        vector<vector<int>> horizontal_ids(rows, vector<int>(cols, -1));
        int current_id = 0;
        
        // find horizontal segments
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    // a new segment starts if it's the first column OR the previous cell is water
                    if (j == 0 || grid[i][j - 1] == '0') {
                        current_id++;
                    }
                    // assign the current ID (0-indexed)
                    horizontal_ids[i][j] = current_id - 1;
                }
            }
        }
        
        // if no horizontal segments were found, there is no land
        if (current_id == 0) return 0;
        
        // init Union-Find based on the total number of horizontal segments
        UnionFind uf(current_id);
        
        // check vertical adjacencies and unite (Disjoint-Set Union)
        for (int i = 0; i < rows - 1; ++i) {
            for (int j = 0; j < cols; ++j) {
                // if a cell and the one exactly below it are both land
                if (grid[i][j] == '1' && grid[i + 1][j] == '1') {
                    // unite their horizontal segment IDs
                    uf.unite(horizontal_ids[i][j], horizontal_ids[i + 1][j]);
                }
            }
        }
        return uf.getCount();
    }
};




