#include "core/main.h"

template <typename float_t, std::size_t DIM>
void test(char const *file, float_t sqRadius, std::size_t minClusterSize)
{
    DEBUG(
        "TEST", "READ_CSV",
        rapidcsv::Document doc(file, rapidcsv::LabelParams(-1, -1));
        std::size_t const rows = doc.GetColumn<float_t>(0).size();
        RowTable<Vector<float_t, DIM>> table(rows);
        for (std::size_t row = 0; row < rows; ++row) {
            std::vector<float_t> const vec = doc.GetRow<float_t>(row);
            for (std::size_t col = 1; col <= DIM; ++col)
            {
                table[row][col] = vec[col];
            }
        });

    DEBUG("TEST", "DBSCAN",
          std::vector<std::size_t> labels = dbscan(table, sqRadius, minClusterSize));

    DEBUG(
        "TEST", "COUNT_RESULTS",
        std::vector<std::size_t> frs(rows, 0);
        for (auto label
             : labels) {
            frs[label] += 1;
        } for (std::size_t row = 0; row < rows; ++row) {
            if (frs[row])
                std::printf("[%u]%u  ", row, frs[row]);
        } std::printf("\n"));
}

int main(int argc, char **argv)
{
    DEBUG("MAIN", "RAND_SEED",
          rand_seed(0));

    DEBUG("MAIN", "TEST",
          CHECK_TIME("LDA",
                     test<float, 4>("data/lda.csv", 1, 2)));

    return EXIT_SUCCESS;
}