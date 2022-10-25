#ifndef __DBSCAN_HPP__
#define __DBSCAN_HPP__

#include <vector>
#include <array>
#include <pure_simd/pure_simd.hpp>
#include "kdtree/StaticKDTree.hpp"

// Created by José Ignacio Huby Ochoa

namespace psmd = pure_simd;

template <typename value_t, std::size_t DIM>
std::vector<std::size_t> dbscan(std::vector<psmd::vector<value_t, DIM>> const &rows, value_t const sqRadius, std::size_t minClusterSize)
{
    std::vector<std::size_t> res;
    res.reserve(rows.size() / 100);
    StaticKDTree<value_t, DIM> kdtree();
    return res;
}

#endif