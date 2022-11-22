/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-22 13:03:58
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-11-22 21:09:58
 * @Description:  
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

class Vertex {
public:
    Vertex() = default;
    Vertex(int tag, int id, std::string &name) :
        tag_(tag), id_(id), name_(std::move(name)) {
    }
    Vertex(Vertex &&v) = default;
    Vertex(const Vertex &v) = default;
    // Vertex(Vertex &&v) {
    //     std::cout << "move constructor called" << std::endl;
    //     tag_ = v.tag_;
    //     id_ = v.id_;
    //     name_ = v.name_;
    //     v.name_ = nullptr;
    // }

    ~Vertex() = default;

    int tag_;
    int id_;
    std::string name_;
    std::string toString() {
        return "(" + std::to_string(tag_) + ", " + std::to_string(id_) + ", " + name_ + ")";
    }
    // std::unordered_map<int, Vertex> loadVertex(const std::string &file_name, const std::string &tag);
};