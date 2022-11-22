/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-22 13:00:59
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-11-22 23:54:27
 * @Description:  
 */
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include <chrono>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

bool fileToLines(std::vector<std::string> &lines, const std::string &file_name) {
    std::ifstream fin(file_name, std::ios::in);
    if (!fin) {
        std::cerr << "open file error" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(fin, line)) {
        lines.emplace_back(line);
    }
    fin.close();
    return true;
}

// tag 1: account
// tag 2: card
bool loadVertex(std::unordered_map<int, Vertex> &vertex_map, int tag, const std::string &file_name, int line_size) {
    // std::unordered_map<int, Vertex> vertex_map;

    std::vector<std::string> lines;
    lines.reserve(line_size);
    if (!fileToLines(lines, file_name)) {
        return false;
    }

    std::string args[4];
    for (auto &line : lines) {
        size_t pos = 0;
        size_t prev = 0;
        size_t index = 0;
        while ((pos = line.find_first_of(',', prev)) != std::string::npos) {
            if (pos > prev) {
                if (pos - prev == 1)
                    break;
                args[index++] = line.substr(prev, pos - prev);
            }
            prev = pos + 1;
        }
        if (prev < line.size()) {
            args[index++] = line.substr(prev);
        }

        int id = std::stoi(args[0]);
        Vertex vertex(tag, id, args[1]);
        vertex_map.emplace(id, std::move(vertex));
        // vertex_map[id]  = vertex;
    }
    return true;
}

bool loadEdge(std::unordered_map<int, std::vector<Edge>> &in_edge_map, std::unordered_map<int, std::vector<Edge>> &out_edge_map, std::unordered_map<int, Vertex> &source_vertex_map, std::unordered_map<int, Vertex> &target_vertex_map, int source_tag, int target_tag, const std::string &file_name, int line_size) {
    std::vector<std::string> lines;
    lines.reserve(line_size);
    if (!fileToLines(lines, file_name)) {
        return false;
    }

    std::string args[10];
    for (auto &line : lines) {
        size_t pos = 0;
        size_t prev = 0;
        size_t index = 0;
        while ((pos = line.find_first_of(',', prev)) != std::string::npos) {
            if (pos > prev) {
                if (pos - prev == 1)
                    break;
                args[index++] = line.substr(prev, pos - prev);
            }
            prev = pos + 1;
        }
        if (prev < line.size()) {
            args[index++] = line.substr(prev);
        }

        // std::cout<<line<<std::endl;
        int source_id = std::stoi(args[0]);
        int target_id = std::stoi(args[1]);
        int amt = static_cast<int>(std::stof(args[3]));
        int strategy_name = args[4].back() - '0';
        int buscode = args[6].back() - '0';
        Edge edge(source_tag, source_id, std::move(source_vertex_map[source_id].name_), target_tag, target_id, std::move(target_vertex_map[target_id].name_), amt, strategy_name, buscode);

        // continue;
        auto ret = in_edge_map.find(target_id);
        if (ret == in_edge_map.end()) {
            std::vector<Edge> edges;
            edges.emplace_back(edge);
            in_edge_map.emplace(target_id, edges);
        } else {
            ret->second.emplace_back(edge);
        }
        ret = out_edge_map.find(source_id);
        if (ret == out_edge_map.end()) {
            std::vector<Edge> edges;
            edges.emplace_back(edge);
            out_edge_map.emplace(source_id, edges);
        } else {
            ret->second.emplace_back(edge);
        }
    }
    return true;
}

bool isLegalPattern(int v0, int v1, int v2, int v3) {
    return (v0 < v1 && v1 < v2) && (v2 < v3 || v3 == v0);
}

class Pattern {
public:
    Pattern(Edge *edge_0, Edge *edge_1, Edge *edge_2) :
        edge_0_(edge_0), edge_1_(edge_1), edge_2_(edge_2) {
    }

    friend struct hash_pattern;
    bool operator==(const Pattern &p) const {
        return (edge_0_->source_name_ == p.edge_0_->source_name_) && (edge_0_->amt_ == p.edge_0_->amt_) && (edge_0_->strategy_name_ == p.edge_0_->strategy_name_) && (edge_0_->buscode_ == p.edge_0_->buscode_) && (edge_1_->source_name_ == p.edge_1_->source_name_) && (edge_1_->amt_ == p.edge_1_->amt_) && (edge_1_->strategy_name_ == p.edge_1_->strategy_name_) && (edge_1_->buscode_ == p.edge_1_->buscode_) && (edge_2_->source_name_ == p.edge_2_->source_name_) && (edge_2_->amt_ == p.edge_2_->amt_) && (edge_2_->strategy_name_ == p.edge_2_->strategy_name_) && (edge_2_->buscode_ == p.edge_2_->buscode_) && (edge_2_->target_name_ == p.edge_2_->target_name_);
    }
    Edge *edge_0_;
    Edge *edge_1_;
    Edge *edge_2_;
};

struct hash_pattern {
    size_t operator()(const Pattern &p) const {
        return std::hash<std::string>()(p.edge_0_->source_name_) ^ std::hash<int>()(p.edge_0_->amt_) ^ std::hash<int>()(p.edge_0_->strategy_name_) ^ std::hash<int>()(p.edge_0_->buscode_) ^ std::hash<std::string>()(p.edge_1_->source_name_) ^ std::hash<int>()(p.edge_1_->amt_) ^ std::hash<int>()(p.edge_1_->strategy_name_) ^ std::hash<int>()(p.edge_1_->buscode_) ^ std::hash<std::string>()(p.edge_2_->source_name_) ^ std::hash<int>()(p.edge_2_->amt_) ^ std::hash<int>()(p.edge_2_->strategy_name_) ^ std::hash<int>()(p.edge_2_->buscode_) ^ std::hash<std::string>()(p.edge_2_->target_name_);
    }
};
// struct equal_pattern {
//     bool operator()(const Pattern &p1, const Pattern &p2) const {
//         return (p1.edge_0_->source_name_ == p2.edge_0_->source_name_) && (p1.edge_0_->amt_ == p2.edge_0_->amt_) && (p1.edge_0_->strategy_name_ == p2.edge_0_->strategy_name_) && (p1.edge_0_->buscode_ == p2.edge_0_->buscode_) && (p1.edge_1_->source_name_ == p2.edge_1_->source_name_) && (p1.edge_1_->amt_ == p2.edge_1_->amt_) && (p1.edge_1_->strategy_name_ == p2.edge_1_->strategy_name_) && (p1.edge_1_->buscode_ == p2.edge_1_->buscode_) && (p1.edge_2_->source_name_ == p2.edge_2_->source_name_) && (p1.edge_2_->amt_ == p2.edge_2_->amt_) && (p1.edge_2_->strategy_name_ == p2.edge_2_->strategy_name_) && (p1.edge_2_->buscode_ == p2.edge_2_->buscode_) && (p1.edge_2_->target_name_ == p2.edge_2_->target_name_);
//     }
// };

int main(int, char **) {
    std::string data_dir = "../data/";
    std::ios::sync_with_stdio(false);
    std::cout << "Hello, world!\n";
    std::unordered_map<int, Vertex> account_map;
    std::unordered_map<int, Vertex> card_map;

    auto start_time = std::chrono::steady_clock::now();
    loadVertex(account_map, 1, data_dir + "account", 800000);
    loadVertex(card_map, 1, data_dir + "card", 600000);
    auto end_time = std::chrono::steady_clock::now();
    auto duration_time = std::chrono::duration<double>(end_time - start_time);
    std::string out_time = std::to_string(duration_time.count());
    std::cout << "load vertex cost：" << out_time << std::endl;

    std::cout << account_map.size() << std::endl;
    std::cout << card_map.size() << std::endl;

    std::unordered_map<int, std::vector<Edge>> account_to_account_in_edge_map;
    std::unordered_map<int, std::vector<Edge>> account_to_account_out_edge_map;
    std::unordered_map<int, std::vector<Edge>> account_to_card_in_edge_map;
    std::unordered_map<int, std::vector<Edge>> account_to_card_out_edge_map;

    start_time = std::chrono::steady_clock::now();
    loadEdge(account_to_account_in_edge_map, account_to_account_out_edge_map, account_map, account_map, 1, 1, data_dir + "account_to_account", 6010512);
    loadEdge(account_to_card_in_edge_map, account_to_card_out_edge_map, account_map, card_map, 1, 2, data_dir + "account_to_card", 3410191);
    end_time = std::chrono::steady_clock::now();
    duration_time = std::chrono::duration<double>(end_time - start_time);
    out_time = std::to_string(duration_time.count());
    std::cout << "load edge cost：" << out_time << std::endl;

    std::cout << account_to_account_in_edge_map.size() << std::endl;
    std::cout << account_to_account_out_edge_map.size() << std::endl;
    std::cout << account_to_card_in_edge_map.size() << std::endl;
    std::cout << account_to_card_out_edge_map.size() << std::endl;

    std::unordered_map<Pattern, int, hash_pattern> pattern_map;

    size_t cnt = 0;
    size_t index = 0;
    std::cout << "begin" << std::endl;
    for (auto &[vertex_1_id, edge_1_candidates] : account_to_account_out_edge_map) {
        ++index;
        if (index > 1000)
            break;
        auto vertex_1_name = account_map[vertex_1_id].name_;

        auto ret = account_to_account_in_edge_map.find(vertex_1_id);
        if (ret == account_to_account_in_edge_map.end()) {
            continue;
        }
        auto edge_0_candidates = ret->second;
        // std::cout << "edge_0: " << edge_0_candidates.size() << std::endl;
        // std::cout << "edge_1: " << edge_1_candidates.size() << std::endl;
        for (auto &edge_1 : edge_1_candidates) {
            auto vertex_2_id = edge_1.target_id_;
            auto vertex_2_name = edge_1.target_name_;
            // std::cout << edge_1.toString() << std::endl;
            ret = account_to_account_out_edge_map.find(vertex_2_id);
            if (ret == account_to_account_out_edge_map.end()) {
                continue;
            }
            auto edge_2_candidates = ret->second;
            // std::cout << "edge_2: " << edge_2_candidates.size() << std::endl;

            for (auto &edge_0 : edge_0_candidates) {
                for (auto &edge_2 : edge_2_candidates) {
                    // std::cout << edge_0.toString() << edge_1.toString() << edge_2.toString() << std::endl;
                    // auto vertex_0_id = edge_0.source_id_;
                    auto vertex_0_name = edge_0.source_name_;
                    // auto vertex_3_id = edge_2.target_id_;
                    auto vertex_3_name = edge_2.target_name_;
                    Pattern pattern(&edge_0, &edge_1, &edge_2);

                    auto patter_ret = pattern_map.find(pattern);
                    if (patter_ret == pattern_map.end()) {
                        pattern_map.emplace(pattern, 1);
                    } else {
                        pattern_map.emplace(pattern, patter_ret->second + 1);
                    }

                    // if (vertex_0_id==vertex_1_id || vertex_0_id==vertex_2_id || vertex_1_id==vertex_2_id || vertex_1_id==vertex_3_id)
                }
            }
        }
    }
    std::cout << "complex: " << cnt << std::endl;
    std::cout << pattern_map.size() << std::endl;
}
