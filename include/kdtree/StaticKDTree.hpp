#ifndef __STATIC_KD_TREE__
#define __STATIC_KD_TREE__

// Created by José Ignacio Huby Ochoa

#include <array>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "core/debug.h"
#include "pure_simd/pure_simd.hpp"

namespace psmd = pure_simd;

template <typename value_t, std::size_t DIM>
class StaticKDTree
{
private:
    std::vector<psmd::vector<value_t, DIM>> const &vectors;
    std::vector<std::size_t> indexes;

    void buildRecursive(std::size_t const from, std::size_t const to, std::size_t const depth)
    {
        if (from >= to)
            return;

        std::size_t const axis = depth % DIM;
        std::sort(indexes.begin() + from, indexes.begin() + to, [axis, this](auto i, auto j)
                  { return this->vectors[i][axis] < this->vectors[j][axis]; });

        std::size_t const median = (from + to) / 2;

        buildRecursive(from, median, depth + 1);
        buildRecursive(median + 1, to, depth + 1);
    }

    void inSqRadiusRecursive(std::vector<std::size_t> &res, psmd::vector<value_t, DIM> const &vector, value_t const &sqRadius, std::size_t const capacity, std::size_t const from, std::size_t const to, std::size_t const depth, value_t const lower_bound)
        const
    {

        if (from >= to)
        {
            return;
        }

        if (res.size() == capacity)
        {
            // printf("hello!!!!\n");
            return;
        }

        std::size_t const axis = depth % DIM;
        std::size_t const median = (from + to) / 2;

        std::size_t const &index = indexes[median];
        psmd::vector<value_t, DIM> const &vnode = vectors[index];

        value_t const &partition = vnode[axis];
        value_t const &partValue = vector[axis];
        value_t const partDiff = partValue - partition;
        value_t const partSqDist = partDiff * partDiff;

        // printf("Part: %f\n", partSqDist);

        if (partSqDist > sqRadius)
            return;

        value_t sqDist = 0;
        for (std::size_t i = 0; i < DIM; ++i)
        {
            value_t const diff = vector[i] - vnode[i];
            sqDist += diff * diff;
        }

        // printf("Full: %f\n", sqDist);

        if (sqDist <= sqRadius)
            res.push_back(index);

        inSqRadiusRecursive(res, vector, sqRadius, capacity, from, median, depth + 1, partSqDist);
        inSqRadiusRecursive(res, vector, sqRadius, capacity, median + 1, to, depth + 1, partSqDist);
    }

public:
    StaticKDTree(std::vector<psmd::vector<value_t, DIM>> const &vectors) : vectors{vectors}
    {
        indexes.resize(vectors.size());
        for (std::size_t i = 0; i < indexes.size(); ++i)
            indexes[i] = i;

        buildRecursive(0, vectors.size(), 0);
    }

    std::vector<std::size_t> inSqRadius(psmd::vector<value_t, DIM> const &vector, value_t const &sqRadius, std::size_t const capacity) const
    {
        std::vector<std::size_t> res;
        res.reserve(capacity);
        inSqRadiusRecursive(res, vector, sqRadius, capacity, 0, vectors.size(), 0, 0);
        return res;
    }
};

#endif