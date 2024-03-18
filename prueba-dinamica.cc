#include<vector>
#include<tuple>
#include<algorithm>
#include<limits>
#include<iostream>


struct TravellingSalesmanGraph {
    int num_vertices_;
    std::vector<std::vector<int> > edges_;
    std::vector<std::vector<int> > min_path_last_vertex_;
    std::vector<std::vector<int> > min_path_;
    // Format: min_path_[vertex_set_explored][last_vertex]
    // State giving the cost of the minimum path/cycle that has explored a certain set of vertices and reached a
    // certain end vertex. Start is at nothing explored and at vertex 0.
    //   vertex_set_explored - Bit field of the vertices we have already traversed. No. of possible values: 2^n
    //   last_vertex - The current vertex we are on. No. of possible values: n
    
    TravellingSalesmanGraph(int num_vertices) {
        num_vertices_ = num_vertices;
        // Initialize edges with very large weights to denote that they are impassable
        edges_.resize(num_vertices, std::vector<int>(num_vertices, std::numeric_limits<int>::max()));
    }
    
    void add_edge(int a, int b, int w) {
        // Adds an undirected edge between a and b of weight w. Assumes vertixes are numbered from 0
        edges_[a][b] = w;
        edges_[b][a] = w;
    }
    
    std::pair<int, std::vector<int> > find_travelling_salesman_cycle() {
        min_path_.resize(1 << num_vertices_, std::vector<int>(num_vertices_, std::numeric_limits<int>::max()));
        min_path_last_vertex_.resize(1 << num_vertices_, std::vector<int>(num_vertices_, -1));
        min_path_[0][0] = 0;  // Our starting point
        
        // Iterating over sets this way guarantees we explore smaller sets first
        for(unsigned int explored_set = 0; explored_set < (1U << num_vertices_); explored_set++) {
            for(int last_vertex = 0; last_vertex < num_vertices_; last_vertex++)
                    if(min_path_[explored_set][last_vertex] != std::numeric_limits<int>::max()) {  // Valid state?
                for(int next_vertex = 0; next_vertex < num_vertices_; next_vertex++)
                        if(
                            edges_[last_vertex][next_vertex] != std::numeric_limits<int>::max() // Edge exists
                         && (explored_set & (1U << next_vertex)) == 0  // We don't go back to already explored vertex
                        ) {
                    // Perform the traversal and see if we find a new shortest path/cycle to the destination state
                    const unsigned int next_set = explored_set + (1U << next_vertex);
                    const int next_cost = min_path_[explored_set][last_vertex] + edges_[last_vertex][next_vertex];
                    if(next_cost < min_path_[next_set][next_vertex]) {
                        min_path_[next_set][next_vertex] = next_cost;
                        min_path_last_vertex_[next_set][next_vertex] = last_vertex;
                    }
                }
            }
        }
        int result_cost = min_path_[(1 << num_vertices_) - 1][0];
        std::vector<int> cycle = {0};
        if (result_cost != std::numeric_limits<int>::max()) {
            int cur_state = (1 << num_vertices_) - 1;
            int cur_vertex = 0;
            
            while(cur_state > 0) {  // Traverse back the minimum cycle
                int prev_vertex = min_path_last_vertex_[cur_state][cur_vertex];
                cur_state -= (1 << cur_vertex);
                cur_vertex = prev_vertex;
                cycle.push_back(cur_vertex);
            }
            std::reverse(cycle.begin(), cycle.end());
        }
        return std::make_pair(min_path_[(1 << num_vertices_) - 1][0], cycle);  // The state corresponding to having traversed the cycle
    }
};


int main() {
    TravellingSalesmanGraph graph(4);
    graph.add_edge(0, 1, 25);
    graph.add_edge(1, 2, 10);
    graph.add_edge(2, 3, 5);
    graph.add_edge(3, 0, 15);
    graph.add_edge(0, 2, 10);
    graph.add_edge(1, 3, 45);
    int min_tsp_cycle_cost;
    std::vector<int> min_tsp_cycle;
    std::tie(min_tsp_cycle_cost, min_tsp_cycle) = graph.find_travelling_salesman_cycle();
    // Expected: 14
    // Expected: 0 2 1 3 0
    std::cout << min_tsp_cycle_cost << std::endl;
    for(int vertex : min_tsp_cycle) {
        std::cout << vertex << " ";
    }
    std::cout << '\n';  // Expected: '0 2 1 3 0\n
    return 0;
}