/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-22 16:08:36
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-11-22 23:52:20
 * @Description:  
 */
#include <string>
class Edge {
public:
    Edge(int source_tag,
         int source_id,
         std::string &&source_name,
         int target_tag,
         int target_id,
         std::string &&target_name,
         int amt,
         int strategy_name,
         int buscode) :
        source_tag_(source_tag),
        source_id_(source_id), source_name_(source_name),
        target_tag_(target_tag), target_id_(target_id), target_name_(target_name),
        amt_(amt), strategy_name_(strategy_name), buscode_(buscode) {
    }

    Edge(const Edge &) = default;
    Edge(Edge &&) = default;
    ~Edge() = default;

    std::string toString() {
        return "(" + std::to_string(source_tag_) + ", " + std::to_string(source_id_) + ", " + source_name_ + ", " + std::to_string(target_tag_) + ", " + std::to_string(target_id_) + ", " + target_name_ + ", " + std::to_string(amt_) + ", " + std::to_string(strategy_name_) + ", " + std::to_string(buscode_) + ")";
    }
    int source_tag_;
    int source_id_;
    std::string source_name_;
    int target_tag_;
    int target_id_;
    std::string target_name_;
    int amt_;
    int strategy_name_;
    int buscode_;
};