"""
Author: starrysky9959 starrysky9651@outlook.com
Date: 2022-11-18 00:55:56
LastEditors: starrysky9959 starrysky9651@outlook.com
LastEditTime: 2022-11-18 01:03:13
Description:  
"""


class Vertex:
    # enable __slost__, disable __dict__
    # this operation will save some memory
    # reference: https://blog.csdn.net/allenalex/article/details/54318836
    __slots__ = ["tag", "id", "name"]

    def __init__(self, tag, id: int, name) -> None:
        self.tag = tag
        self.id = id
        self.name = name

    def __str__(self) -> str:
        return "{{ tag: {0}, id: {1}, name: {2} }}".format(self.tag, self.id, self.name)


class Edge:
    __slots__ = [
        "source_tag",
        "source_id",
        "target_tag",
        "target_id",
        "amt",
        "strategy_name",
        "buscode",
    ]

    def __init__(
        self, source_tag, source_id, target_tag, target_id, amt, strategy_name, buscode
    ) -> None:
        self.source_tag = source_tag
        self.source_id = source_id
        self.target_tag = target_tag
        self.target_id = target_id
        # self.raw_amt = float(raw_amt)
        self.amt = amt
        self.strategy_name = strategy_name
        self.buscode = buscode

    def __str__(self) -> str:
        return "{{ source_tag: {0}, source_id: {1}, target_tag: {2}, target_id: {3}, amt: {5}, strategy_name: {6}, buscode: {7} }}".format(
            self.source_tag,
            self.source_id,
            self.target_tag,
            self.target_id,
            # self.raw_amt,
            self.amt,
            self.strategy_name,
            self.buscode,
        )
