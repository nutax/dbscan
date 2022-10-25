#ifndef __STATIC_KD_TREE__
#define __STATIC_KD_TREE__

// Created by José Ignacio Huby Ochoa

#include <array>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "pure_simd/pure_simd.hpp"

namespace pure_simd = psmd;

template <typename value_t, std::size_t DIM>
class StaticKDTree
{
private:
    std::vector<psmd::vector<value_t, DIM>> const &vectors;
    std::vector<std::size_t> indexes;

    void buildRecursive(std::size_t const from, std::size_t const to, std::size_t const depth)
    {
        if (to >= from)
            return;

        std::size_t const axis = depth % DIM;
        std::sort(indexes.begin() + from, indexes.begin() + to, [axis, &vectors](auto i, auto j)
                  { return vectors[i][axis] < vectors[j][axis]; });

        std::size_t const median = (from + to) / 2;

        buildRecursive(vectors, indexes, from, median, depth + 1);
        buildRecursive(vectors, indexes, median + 1, to, depth + 1);
    }

    void inSqRadiusRecursive(std::vector<std::size_t> &res, psmd::vector<value_t, DIM> const &vector, value_t const &sqRadius, std::size_t const capacity, std::size_t const from, std::size_t const to, std::size_t depth)
    {
        if (to >= from)
            return;
        if (res.size() == capacity)
            return;

        std::size_t const axis = depth % DIM;
        std::size_t const median = (from + to) / 2;

        std::size_t const &index = indexes[median];
        psmd::vector<value_t, DIM> const &vnode = vectors[index];

        value_t const &partition = vnode[axis];
        value_t const &partValue = vector[axis];
        value_t const partDiff = partValue - partition;
        value_t const partSqDist = partDiff * partDiff;

        if (partSqDist > sqRadius)
            return;

        value_t sqDist = 0;
        for (std::size_t i = 0; i < DIM; ++i)
        {
            value_t const diff = vector[i] - vnode[i];
            sqDiff += diff * diff;
        }

        if (sqDist <= sqRadius)
            res.push_back(index);

        inSqRadiusRecursive(res, vector, sqRadius, capacity, from, median, depth + 1);
        inSqRadiusRecursive(res, vector, sqRadius, capacity, median + 1, to, depth + 1);
    }

public:
    StaticKDTree(std::vector<psmd::vector<value_t, DIM>> const &vectors) : vectors{vectors}
    {

        for (std::size_t i = 0; i < indexes.size(); ++i)
            indexes[i] = i;

        buildRecursive(from, to, 0);
    }

    std::vector<std::size_t> inSqRadius(psmd::vector<value_t, DIM> const &vector, value_t const &sqRadius, std::size_t const capacity)
    {
        std::vector<std::size_t> res;
        res.reserve(capacity);
        inSqRadiusRecursive(res, vector, sqRadius, capacity, 0, vectors.size(), 0);
        return res;
    }
};

#endif