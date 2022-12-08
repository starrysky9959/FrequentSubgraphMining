/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-22 13:03:58
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-12-02 00:23:55
 * @Description:  
 */
#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Edge.h"

class Vertex {
public:
    Vertex() = default;
    Vertex(int vid, int vlabel) :
        vid_(vid), vlabel_(vlabel) {
    }
    Vertex(Vertex &&v) = default;
    Vertex(const Vertex &v) = default;
    ~Vertex() = default;

    void addEdges(int source_vid,
                  int target_vid,
                  int source_vlabel,
                  int elabel,
                  int target_vlabel) {
        std::cout << "error" << std::endl;
        Edge out_edge(source_vid, target_vid, source_vlabel, elabel, target_vlabel, 1);
        auto ret = out_edges_.find(target_vid);
        if (ret == out_edges_.end()) {
            out_edges_.emplace(target_vid, std::vector<Edge>());
        }
        out_edges_[target_vid].emplace_back(out_edge);

        Edge in_edge(target_vid, source_vid, target_vlabel, elabel, source_vlabel, 2);
        ret = in_edges_.find(target_vid);
        if (ret == in_edges_.end()) {
            in_edges_.emplace(target_vid, std::vector<Edge>());
        }
        in_edges_[target_vid].emplace_back(in_edge);
    }

    std::string toString() {
        // return "(" + std::to_string(tag_) + ", " + std::to_string(id_) + ", " + name_ + ")";
        return "(" + std::to_string(vid_) + ", " + std::to_string(vlabel_) + ")";
    }

    int vid_;
    int vlabel_;
    // std::string name_;
    std::unordered_map<int, std::vector<Edge>> out_edges_; // real edges
    std::unordered_map<int, std::vector<Edge>> in_edges_;  // reverse edges used for directed graph
};