#include "core/main.h"

template <typename float_t, std::size_t DIM>
void test(char const *file, float_t sqRadius, std::size_t minClusterSize)
{
    rapidcsv::Document doc(file, rapidcsv::LabelParams(-1, -1));
    std::size_t const rows = doc.GetColumn<float_t>(0).size();
    RowTable<Vector<float_t, DIM>> table(rows);
    for (std::size_t row = 0; row < rows; ++row)
    {
        std::vector<float_t> const vec = doc.GetRow<float_t>(row);
        for (std::size_t col = 1; col <= DIM; ++col)
        {
            table[row][col] = vec[col];
        }
    }
    std::vector<std::size_t> labels = dbscan(table, sqRadius, minClusterSize);
    std::vector<std::size_t> frs(rows, 0);
    for (auto label : labels)
    {
        frs[label] += 1;
    }
    for (auto fr : frs)
    {
        if (fr)
            std::printf("%u  ", fr);
    }
    std::printf("\n");
}

int main(int argc, char **argv)
{
    rand_seed(0);
    CHECK_TIME("Hola", test<double, 4>("data/pca.csv", 125, 3));
    hello();
    return EXIT_SUCCESS;
}