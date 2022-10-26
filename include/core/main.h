#ifndef _MAIN_H_
#define _MAIN_H_

#include <cstdio>
#include <cstdlib>
#include <vector>
#include "hello/hello.h"
#include "core/random.h"
#include "core/measure.h"
#include "csv/rapidcsv.h"
#include "clustering/dbscan.hpp"
#include "pure_simd/pure_simd.hpp"

template <typename T>
using RowTable = std::vector<T>;

template <typename T, std::size_t DIM>
using Vector = pure_simd::vector<T, DIM>;

int main(int argc, char **argv);

#endif