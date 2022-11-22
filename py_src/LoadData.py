"""
Author: starrysky9959 starrysky9651@outlook.com
Date: 2022-11-20 15:43:19
LastEditors: starrysky9959 starrysky9651@outlook.com
LastEditTime: 2022-11-21 00:11:31
Description:  
"""
"""
Author: starrysky9959 starrysky9651@outlook.com
Date: 2022-11-18 01:08:38
LastEditors: starrysky9959 starrysky9651@outlook.com
LastEditTime: 2022-11-18 21:14:49
Description:  
"""
from numba import jit
# from .Graph import Edge
import numpy as np

data_dir = "data/"

Edge = np.dtype(
    [
        ("source_tag", np.unicode_, 8),
        ("source_id", np.int32),
        ("source_name", np.unicode_, 4),
        ("target_tag", np.unicode_, 8),
        ("target_id", np.int32),
        ("target_name", np.unicode_, 4),
        ("amt", np.int32),
        ("strategy_name", np.int8),
        ("buscode", np.int8),
    ]
)

Vertex = np.dtype(
    [
        ("tag", np.unicode_, 8),
        ("id", np.int32),
        ("name", np.unicode_, 4),
    ]
)


# @jit
def load_vertex(file_name, tag, max_size=10000000):
    vertex_map = {}
    with open(data_dir + file_name, "r") as f:
        line = f.readline()
        # print(tag)
        while (line is not None) and (line != "") and (max_size > 0):
            max_size -= 1
            args = line.split(",")
            vertex_id = int(args[0])
            vertex = np.array(
                (
                    tag,
                    vertex_id,
                    args[1],
                ),
                dtype=Vertex,
            )
            # print(vertex)
            # break
            # vertex = Vertex(tag, vertex_id, args[1])
            # print(vertex)
            vertex_map[vertex_id] = vertex  # vertex
            line = f.readline()

    return vertex_map


# @jit
def load_edge(
    file_name, source_tag, target_tag, source_map, target_map, max_size=10000000
):
    """
    # example data in every line:
    # 684821,434860,1590492254126,5.0,strategy_name-4,1590492251120278,buscode3,,,,,,
    # here are some useful attributes
    # args[0]: source_id, int
    # args[1]: target_id, int
    # args[3]: raw amt, float -> must convert to int
    # args[4]: strategy_name, str -> may convert to int, range in [1,2,3]
    # args[6]: buscode, str -> may convert to int, range in [1,2,3,4]
    """

    edge_map = {}
    edge_map_by_property = {}
    in_edges_map = {}
    out_edges_map = {}
    with open(data_dir + file_name, "r") as f:
        source_id, target_id = 0, 0
        amt, strategy_name, buscode = 0, 0, 0
        line = f.readline()
        while (line is not None) and (line != "") and (max_size > 0):
            max_size -= 1
            args = line.split(",")
            source_id = int(args[0])
            target_id = int(args[1])
            # print(source_map[source_id])
            source_name = source_map[source_id]["name"].item(0)
            target_name = target_map[target_id]["name"].item(0)
            # print(source_name)
            # print(type(source_name))
            amt = int(float(args[3]))
            strategy_name = int(args[4][-1])
            buscode = int(args[6][-1])
            edge = np.array(
                (
                    source_tag,
                    source_id,
                    source_name,
                    target_tag,
                    target_id,
                    target_name,
                    amt,
                    strategy_name,
                    buscode,
                ),
                dtype=Edge,
            )

            in_edges = in_edges_map.get(target_id, [])
            in_edges.append(edge)
            in_edges_map[target_id] = in_edges
            # in_edges.append(edge)
            out_edges = out_edges_map.get(source_id, [])
            out_edges.append(edge)
            out_edges_map[source_id] = out_edges
            # out_edges.append(edge)

            # if source_name in edge_map:
            #     edge_map[source_name].append(edge)
            # else:
            #     edge_map[source_name] = [edge]

            # name_key = (source_name, target_name)
            # propery_key = (amt, strategy_name, buscode)
            # if name_key in edge_map_by_property:
            #     if propery_key in edge_map_by_property[name_key]:
            #         edge_map_by_property[name_key][propery_key].append(edge)
            #     else:
            #         edge_map_by_property[name_key][propery_key] = [edge]
            # else:
            #     edge_map_by_property[name_key] = {propery_key: [edge]}
            # if propery_key in edge_map_by_property:
            #     edge_map_by_property[propery_key].append(edge)
            # else:
            #     edge_map_by_property[propery_key] = [edge]
            # edge_list.append(edge)
            line = f.readline()

    return in_edges_map, out_edges_map


