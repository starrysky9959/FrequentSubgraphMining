"""
Author: starrysky9959 starrysky9651@outlook.com
Date: 2022-11-18 01:08:38
LastEditors: starrysky9959 starrysky9651@outlook.com
LastEditTime: 2022-11-18 21:14:49
Description:  
"""
from Graph import Edge, Vertex


data_dir = "data/"


def load_vertex(file_name, tag):
    vertex_map = {}
    with open(data_dir + file_name, "r") as f:
        line = f.readline()
        while (line is not None) and (line != ""):
            args = line.split(",")
            vertex = Vertex(tag, args[0], args[1])
            # print(vertex)
            vertex_map[args[0]] = vertex
            line = f.readline()

    return vertex_map


def load_edge(file_name, source_tag, target_tag):
    edge_map = {}
    with open(data_dir + file_name, "r") as f:
        line = f.readline()
        while (line is not None) and (line != ""):
            args = line.split(",")
            edge = Edge(
                source_tag, args[0], target_tag, args[1], args[3], args[4], args[6]
            )
            # print(edge)
            if args[0] in edge_map:
                edge_map[args[0]].append(edge)
            else:
                edge_map[args[0]] = [edge]
            
            # edge_list.append(edge)
            line = f.readline()

    return edge_map


account_map = load_vertex("account", "account")
card_map = load_vertex("card", "card")
account_to_account_list = load_edge("account_to_account", "account", "account")
account_to_card_list = load_edge("account_to_card", "account", "card")
print(
    "vertex size: {}, edge size: {}".format(
        len(account_map) + len(card_map),
        len(account_to_account_list) + len(account_to_card_list),
    )
)

for ()