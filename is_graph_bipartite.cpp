// For the given graph, we check if there are identical sets, and since it is undirected, we consider the edge [i,j] and [j,i] to be the same. 
// Then, we try to merge the individual subsets so that in the end exactly 2 sets are formed. Within each set, there are no edges between its nodes, 
// but there are edges connecting nodes from one set to the other, because that is how we constructed these 2 sets.

#include <vector>
#include <numeric>

using namespace std;

// Union-Find data structure for managing the sets
class UnionFind {
private:
    vector<int> parent;

public:
    explicit UnionFind(int n) {
        parent.resize(n);
        // std::iota fills the vector with 0, 1, 2, ..., n-1
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        // path compression - O(1)
        return parent[i] == i ? i : (parent[i] = find(parent[i]));
    }

    void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
        }
    }

    // checks if 2 nodes are already in the exact same set
    bool isSameSet(int i, int j) {
        return find(i) == find(j);
    }
};

class Solution {
public:
    bool isBipartite(const vector<vector<int>>& graph) {
        int n = graph.size();
        UnionFind uf(n);

        // iterate through every node in the graph
        for (int i = 0; i < n; ++i) {
            // if the node has no neighbors, skip it
            if (graph[i].empty()) continue;
            // check all neighbors of node 'i'
            for (int neighbor : graph[i]) {
                // first rule: a node and its neighbor cannt be in the same set
                if (uf.isSameSet(i, neighbor)) {
                    return false; // Graph is not bipartite
                }
                // second rule: all neighbors of node 'i' must be in the same set.
                // so, we unite the current neighbor with the first neighbor in the list.
                uf.unite(graph[i][0], neighbor);
            }
        }
        return true;
    }
};
