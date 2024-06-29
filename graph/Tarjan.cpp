#include <bits/stdc++.h>
using namespace std;
class  ADJ {
   private:
       vector<vector<int>> adj;
   public:
       int n = -1;

    void addEdge(int from, int to) {
        if (n <= 0)
            throw runtime_error("You must initialize adj");
        if (from < 0 || from >= n || to < 0 || to >= n)
            throw out_of_range("Node index out of range");
        adj[from].push_back(to);
    }

    void addBiEdge(int from, int to) {
        addEdge(from, to);
        addEdge(to, from);
    }

    void init(int n) {
        this->n = n;
        adj.clear();
        adj.resize(n);
    }

    const vector<int>& operator[](int index) const {
        return adj[index];
    }
} adj;

struct BCC {
    vector<vector<pair<int, int> > > bcc_edges;
    vector<vector<int> > bcc_nodes;
    vector<vector<int> > has_bcc;
    stack<pair<int, int> > st;
    int bcccnt = 0;
    void init(int n) {
        bcc_edges.clear();
        bcc_nodes.clear();
        has_bcc.clear();
        has_bcc.resize(n);
    }
    void clear_stack() {
        while (st.size()) {
            st.pop();
        }
    }
    void push(int u, int v) { st.push({u, v}); }
    void createBCC(int u, int v) {
        bcc_edges.emplace_back();
        while (st.top() != mp(u, v)) {
            bcc_edges.back().pb(st.top());
            st.pop();
        }
        bcc_edges.back().pb(st.top());
        st.pop();
        bcccnt++;
    }
    void createBCC() {
        if (st.size() == 0) return;
        bcc_edges.emplace_back();
        while (st.size()) {
            bcc_edges.back().pb(st.top());
            st.pop();
        }
        bcccnt++;
    }
    void generateBCCNode() {
        unordered_set<int> st;
        for (auto &bcc : bcc_edges) {
            st.clear();
            for (auto &edge : bcc) {
                st.insert(edge.first);
                st.insert(edge.second);
            }
            bcc_nodes.emplace_back();
            for (auto &node : st) {
                bcc_nodes.back().pb(node);
                has_bcc[node].pb(bcc_nodes.size() - 1);
            }
        }
    }
} bcc;

struct AritculationPoints {
    unordered_set<int> nodes;
    void init() { nodes.clear(); }
    bool is_apoint(int p) { return nodes.count(p); }
    void add(int p) { nodes.insert(p); }
} articulationPoints;

pair<int, int> getpair(int x, int y) { return {min(x, y), max(x, y)}; }
struct Bridges {
    set<pair<int, int> > bridges;
    void init() { bridges.clear(); }
    bool is_bridge(int u, int v) { return bridges.count(getpair(u, v)); }
    void add(int u, int v) { bridges.insert(getpair(u, v)); }
} bridges;

struct Tarjan {
    public:
    void run(ADJ &adj, bool with_articulationPoints, bool _with_bridges, bool _with_bcc) {
        with_articulationPoints = with_articulationPoints;
        with_bridges = _with_bridges;
        with_bcc = _with_bcc;
        init(adj.n);
        for (int i = 0; i < adj.n; ++i) {
            if (!visited[i]) {
                dfs(i, adj);
                if (with_bcc) {
                    bcc.createBCC();
                }
            }
        }
    }
    private:
    vector<int> visited;
    vector<int> discoveryTime;
    vector<int> lowestDiscoveryTime;
    // The parent of each node based on the DFS traversal
    vector<int> parent;
    // An articulation point is a node whose removal causes the graph to split into two or more components
    bool with_articulationPoints;
    // A Biconnected Component (BCC) is a maximal subgraph that has no articulation points
    bool with_bcc;
    // A bridge is an edge that, when removed, increases the number of connected components of the graph
    bool with_bridges;
    int timer;
    void dfs(int node, ADJ &adj) {
        visited[node] = 1;
        discoveryTime[node] = lowestDiscoveryTime[node] = timer++;
        int children = 0;
        for(auto child: adj[node]) {
            if (child == parent[node]) continue;
            if (visited[child] == 1) {
                if (with_bcc && discoveryTime[child] < lowestDiscoveryTime[node]) bcc.push(node, child);
                lowestDiscoveryTime[node] = min(discoveryTime[child], lowestDiscoveryTime[node]);
            } else if (!visited[child]) {
                if (with_bcc) bcc.push(node, child);
                ++children;
                parent[child] = node;
                dfs(child, adj);
                lowestDiscoveryTime[node] = min(lowestDiscoveryTime[node], lowestDiscoveryTime[child]);
                if (with_bcc) {
                    if (parent[node] == -1 && children > 1) bcc.createBCC(node, child);
                    if (parent[node] != -1 && lowestDiscoveryTime[child] >= discoveryTime[node]) {
                        bcc.createBCC(node, child);
                    }
                }
                if (with_bridges && lowestDiscoveryTime[child] > discoveryTime[node]) bridges.add(node, child);
                if (with_articulationPoints && lowestDiscoveryTime[child] >= discoveryTime[node] && parent[node] != -1) {
                    // if lowestDiscoveryTime[child] >= discoveryTime[node] then node is Arc pnt, except the root should be skipped
                    articulationPoints.add(node);
                }
            }
        }
        if (with_articulationPoints && parent[node] == -1 && children > 1) {
            // if root has more than a child => it's a arc pnt
            articulationPoints.add(node);
        }
    }

    void init(int n) {
        timer = 0;
        visited.assign(n, 0);
        discoveryTime.assign(n, -1);
        lowestDiscoveryTime.assign(n, -1);
        parent.assign(n, -1);
        if (with_bridges) bridges.init();
        if (with_articulationPoints) articulationPoints.init();
        if (with_bcc) bcc.init(adj.n);
    }
} tarjan;

int main() {}