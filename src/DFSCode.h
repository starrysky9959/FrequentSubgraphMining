/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-26 21:20:53
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-11-29 02:09:51
 * @Description:  
 */
#pragma once
#include <algorithm>
#include <vector>
#include "Graph.h"

/*
class DFSEdge {
public:
    DFSEdge(int source_vid,
            int target_vid,
            int vev_label) :
        source_vid_(source_vid),
        target_vid_(target_vid), vev_label_(vev_label) {
    }

    bool operator==(const DFSEdge &other) const {
        return (source_vid_ == other.source_vid_) && (target_vid_ == other.target_vid_) && (vev_label_ == other.vev_label_);
    }

    int source_vid_;
    int target_vid_;
    int vev_label_;
};

*/


class DFSCode {
public:
    void minDFSCode( Graph & graph){
        is_visited_.assign(graph.vertexSize(), false);
        int min_key = graph.vertexSize();
        for (const auto &[k,v]: graph.vertex_map_){
            min_key = std::min(min_key, k);
        }

        int origin_vid = min_key;
        is_visited_[origin_vid] = true;
        dfs(graph, origin_vid);
    }
    void dfs( Graph & graph, int current_vid) const{
        for (auto &[target_vid, edges]: graph.vertex_map_[current_vid].out_edges_){
            
        }
    }
    std::vector<bool> is_visited_;
    std::vector<Edge> edge_seq_;
};