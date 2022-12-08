/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-22 13:00:59
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-11-26 15:49:31
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
#include "Graph.h"
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
    std::getline(fin, line); // skip the first line
    while (std::getline(fin, line)) {
        lines.emplace_back(line);
    }
    fin.close();
    return true;
}

bool loadGraph(std::string &&file_name, Graph &graph) {
    std::vector<std::string> lines;
    // lines.reserve(line_size);
    if (!fileToLines(lines, file_name)) {
        return false;
    }

    std::string args[4];
    for (auto &line : lines) {
        // int pos = 0;
        int prev = -1;
        size_t index = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == ' ') {
                args[index++] = line.substr(prev + 1, i - prev - 1);
                prev = i;
            }
        }
        if (prev < line.size()) {
            args[index++] = line.substr(prev + 1);
        }

        char type = args[0][0];
        if (type == 'v') {
            graph.addVertex(std::stoi(args[1]), std::stoi(args[2]));
        } else {
            std::cout << "edge" << std::endl;
            graph.addEdge(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]));
        }
    }
    return true;
}

int main(int, char **) {
    std::ios::sync_with_stdio(false);

    Graph graph;
    auto start_time = std::chrono::steady_clock::now();
    loadGraph("../data/sample", graph);
    auto end_time = std::chrono::steady_clock::now();
    auto duration_time = std::chrono::duration<double>(end_time - start_time);
    std::string out_time = std::to_string(duration_time.count());

    std::cout << "load graph cost：" << out_time << '\n';
    std::cout << graph.vertexSize() << '\n';

    for (auto &[k, v] : graph.vertex_map_) {
        std::cout << k << " " << v.in_edges_.size() << '\n';
        if (!v.out_edges_.empty()) {
            std::cout << v.out_edges_.begin()->second.begin()->toString() << '\n';
        }
    }

    std::cout << std::endl;
}