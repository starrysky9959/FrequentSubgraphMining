/*
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-22 16:08:36
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-12-02 00:26:38
 * @Description:  
 */
 
 #pragma once
#include <string>
/*
class Edge {
public:
    Edge(int eid,
         int source_vid,
         int target_vid,
         int elabel) :
        eid_(eid),
        source_vid_(source_vid), target_vid_(target_vid), elabel_(elabel) {
    }

    // Edge(int source_tag,
    //      int source_id,
    //      std::string &&source_name,
    //      int target_tag,
    //      int target_id,
    //      std::string &&target_name,
    //      int amt,
    //      int strategy_name,
    //      int buscode) :
    //     source_tag_(source_tag),
    //     source_id_(source_id), source_name_(source_name),
    //     target_tag_(target_tag), target_id_(target_id), target_name_(target_name),
    //     amt_(amt), strategy_name_(strategy_name), buscode_(buscode) {
    // }

    Edge(const Edge &) = default;
    Edge(Edge &&) = default;
    ~Edge() = default;

    std::string toString() {
        // return "(" + std::to_string(tag_) + ", " + std::to_string(id_) + ", " + name_ + ")";
        return "(" + std::to_string(eid_) + ", " + std::to_string(source_vid_) + ", " + std::to_string(target_vid_) + ", " + std::to_string(elabel_) + ")";
    }
    // std::string toString() {
    //     return "(" + std::to_string(source_tag_) + ", " + std::to_string(source_id_) + ", " + source_name_ + ", " + std::to_string(target_tag_) + ", " + std::to_string(target_id_) + ", " + target_name_ + ", " + std::to_string(amt_) + ", " + std::to_string(strategy_name_) + ", " + std::to_string(buscode_) + ")";
    // }
    // int source_tag_;
    // int source_id_;
    // std::string source_name_;
    // int target_tag_;
    // int target_id_;
    // std::string target_name_;
    // int amt_;
    // int strategy_name_;
    // int buscode_;
    int eid_;
    int source_vid_;
    int target_vid_;
    int elabel_;
};

*/

// 6-Tuple
class Edge {
public:
    Edge(int source_vid,
              int target_vid,
              int source_vlabel,
              int elabel,
              int target_vlabel,
              int direction) :
        source_vid_(source_vid),
        target_vid_(target_vid), source_vlabel_(source_vlabel), elabel_(elabel), target_vlabel_(target_vlabel), direction_(direction) {
    }

    int compareTo(Edge &&other) {
        if (source_vid_ < other.source_vid_) {
            return 1;
        } else if (source_vid_ > other.source_vid_) {
            return -1;
        }

        if (target_vid_ < other.target_vid_) {
            return 1;
        } else if (target_vid_ > other.target_vid_) {
            return -1;
        }

        if (source_vlabel_ < other.source_vlabel_) {
            return 1;
        } else if (source_vlabel_ > other.source_vlabel_) {
            return -1;
        }

        if (elabel_ < other.elabel_) {
            return 1;
        } else if (elabel_ > other.elabel_) {
            return -1;
        }

        if (target_vlabel_ < other.target_vlabel_) {
            return 1;
        } else if (target_vlabel_ > other.target_vlabel_) {
            return -1;
        }

        if (direction_ < other.direction_) {
            return 1;
        } else if (direction_ > other.direction_) {
            return -1;
        }
        return 0;
    }
    int compareTo(Edge &other) {
        return compareTo(other);
    };

    std::string toString() {
        // return "(" + std::to_string(tag_) + ", " + std::to_string(id_) + ", " + name_ + ")";
        return "(" + std::to_string(source_vid_) + ", " + std::to_string(target_vid_) + ", " + std::to_string(source_vlabel_) +", " + std::to_string(elabel_) +", " + std::to_string(target_vlabel_) +", " + std::to_string(direction_) +")";
    }


    int source_vid_;
    int target_vid_;
    int source_vlabel_;
    int elabel_;
    int target_vlabel_;
    int direction_;
};