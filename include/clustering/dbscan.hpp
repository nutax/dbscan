#ifndef __DBSCAN_HPP__
#define __DBSCAN_HPP__

#include <vector>
#include <array>
#include <pure_simd/pure_simd.hpp>
#include "kdtree/StaticKDTree.hpp"

// Created by José Ignacio Huby Ochoa

namespace psmd = pure_simd;

void dbscanDFS(auto kdtree, auto rows, auto sqRadius, auto minClusterSize, auto curr, auto visited, auto labels, auto cluster)
{
    auto neighbors = kdtree.inSqRadius(rows[curr], sqRadius, minClusterSize);
    if (neighbors.size() <= minClusterSize)
        return;

    for (auto const &neighbor : neighbors)
    {
        if (neighbor == curr)
        {
            labels[neighbor] = cluster;
            continue;
        }
        if (!(visited[neighbor]))
        {
            visited[neighbor] = true;
            labels[neighbor] = cluster;
            dbscanDFS(kdtree, rows, sqRadius, minClusterSize, neighbor, visited, labels, cluster);
        }
    }
}

template <typename value_t, std::size_t DIM>
std::vector<std::size_t> dbscan(std::vector<psmd::vector<value_t, DIM>> const &rows, value_t const sqRadius, std::size_t minClusterSize)
{
    std::vector<std::size_t> labels(rows.size(), 0);
    std::vector<bool> visited(rows.size(), false);

    StaticKDTree<value_t, DIM> kdtree(rows);

    std::size_t cluster = 1;
    for (std::size_t i = 0; i < rows.size(); ++i)
    {
        if (!(visited[i]))
        {
            visited[i] = true;
            dbscanDFS(kdtree, rows, sqRadius, minClusterSize, i, visited, labels, cluster);
            cluster += 1;
        }
    }

    return labels;
}

#endif