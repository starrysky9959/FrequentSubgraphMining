<!--
 * @Author: starrysky9959 starrysky9651@outlook.com
 * @Date: 2022-11-18 00:51:11
 * @LastEditors: starrysky9959 starrysky9651@outlook.com
 * @LastEditTime: 2022-11-20 15:26:48
 * @Description:  
-->
# Frequent Subgraph Mining on Attributed Graph

## Questions and DataSet
题目和数据集链接：[https://www.datafountain.cn/competitions/586/datasets](https://www.datafountain.cn/competitions/586/datasets)

数据集较大, 不通过Git上传. 请将从官网下载的`bdci_data.tar.gz`解压后移动至`data/`目录下.
数据集规模: |V|=1.4M, |E|=9.4M

## Project
```
├── README.md
├── data                            # 数据集目录
│   ├── account
│   ├── account_to_account
│   ├── account_to_card
│   ├── card
│   └── schema.txt
├── result_demo.json                # 标准答案
└── src                             # 源码
    ├── Graph.py
    └── LoadData.py
```

## Run

```bash
git clone <project_url>
cd <project_name>
python3 src/LoadData.py
```