#ifndef __DBSCAN_HPP__
#define __DBSCAN_HPP__

#include <vector>
#include <array>
#include <pure_simd/pure_simd.hpp>
#include "kdtree/StaticKDTree.hpp"
#include "core/debug.h"

// Created by José Ignacio Huby Ochoa

namespace psmd = pure_simd;

void dbscanDFS(auto &kdtree, auto const &rows, auto const sqRadius, auto const minClusterSize, auto const curr, auto &visited, auto &labels, auto const cluster)
{
    auto neighbors = kdtree.inSqRadius(rows[curr], sqRadius, minClusterSize + 1);
    if (neighbors.size() <= minClusterSize)
        return;
    labels[curr] = cluster;
    for (auto const &neighbor : neighbors)
    {
        if (visited[neighbor] == false)
        {

            visited[neighbor] = true;
            labels[neighbor] = cluster;

            dbscanDFS(kdtree, rows, sqRadius, minClusterSize, neighbor, visited, labels, cluster);
        }
    }
}

template <typename value_t, std::size_t DIM>
std::vector<std::size_t> dbscan(std::vector<psmd::vector<value_t, DIM>> const &rows, value_t const sqRadius, std::size_t const minClusterSize)
{
    DEBUG("DBSCAN", "ARRAYS_INIT",
          std::vector<std::size_t> labels(rows.size(), 0);
          std::vector<bool> visited(rows.size(), false));

    DEBUG("DBSCAN", "KDTREE_BUILD",
          StaticKDTree<value_t, DIM>
              kdtree(rows));

    DEBUG(
        "DBSCAN", "DFS",
        std::size_t cluster = 1;
        for (std::size_t i = 0; i < rows.size(); ++i) {
            if (visited[i] == false)
            {
                visited[i] = true;
                dbscanDFS(kdtree, rows, sqRadius, minClusterSize, i, visited, labels, cluster);
                if (labels[i] > 0)
                {
                    cluster += 1;
                    printf("UIUI!\n");
                }
            }
        });

    return labels;
}

#endif