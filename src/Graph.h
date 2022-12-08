/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-26 01:41:06
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-12-05 00:45:32
 * @Description:  
 */
#pragma once
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include "Vertex.h"
#include "Edge.h"

class Graph {
public:
    Graph() :
        next_eid(0) {
    }

    ~Graph() = default;

    // Grpah(const Graph &) = default;
    // Grpah(Graph &&) = default;

    void addVertex(int vid, int vlabel) {
        vertex_map_.emplace(vid, Vertex(vid, vlabel));
        vlabel_map_[vlabel].emplace(vid);
    }
    void addEdge(int source_id, int target_id, int elabel) {
        int eid = next_eid++;
        // edge_map_.emplace(eid, Edge(eid, source_id, target_id, elabel));
        vertex_map_[source_id].addEdges(source_id, target_id, vertex_map_[source_id].vlabel_, elabel, vertex_map_[target_id].vlabel_);
        // elabel_map_[elabel].emplace(eid);
    }

    size_t vertexSize() const {
        return vertex_map_.size();
    }
    size_t edgeSize() const {
        return edge_map_.size();
    }
    int next_eid;
    // vid:Vertex
    std::unordered_map<int, Vertex> vertex_map_;
    // eid:Edge
    std::unordered_map<int, Edge> edge_map_;
    std::unordered_map<int, std::unordered_set<int>> vlabel_map_;
    std::unordered_map<int, std::unordered_set<int>> elabel_map_;
};