#ifndef MLFW_MATRIX_H
#define MLFW_MATRIX_H

#include <memory>
#include <string>

#include "types.h"

namespace mlfw
{

class Vector;

class Matrix
{
private:

    dimension_t rows;
    dimension_t cols;

    std::unique_ptr<double[]> data;

public:

    // ==========================================
    // Constructors / Destructor
    // ==========================================

    Matrix(
        dimension_t rows,
        dimension_t cols
    );

    Matrix(
        const Matrix& other
    );

    Matrix& operator=(
        const Matrix& other
    );

    Matrix(
        Matrix&& other
    ) noexcept;

    Matrix& operator=(
        Matrix&& other
    ) noexcept;

    ~Matrix() = default;

    // ==========================================
    // Element Access
    // ==========================================

    double get(
        index_t row,
        index_t col
    ) const;

    void set(
        index_t row,
        index_t col,
        double value
    );

    // ==========================================
    // Matrix Style Access
    // A(1,2) = 10;
    // ==========================================

    double& operator()(
        index_t row,
        index_t col
    );

    const double& operator()(
        index_t row,
        index_t col
    ) const;

    // ==========================================
    // Dimensions
    // ==========================================

    dimension_t getRows() const;

    dimension_t getCols() const;

    // ==========================================
    // Fill
    // Equivalent of:
    // mlfw_mat_double_fill(...)
    // ==========================================

    void fill(
        double value
    );

    void fill(
        index_t from_row,
        index_t from_col,
        index_t to_row,
        index_t to_col,
        double value
    );

    // ==========================================
    // Copy Region
    // Equivalent of:
    // mlfw_mat_double_copy(...)
    // ==========================================

    void copyTo(
        Matrix& target,
        index_t target_row,
        index_t target_col,
        index_t source_from_row,
        index_t source_from_col,
        index_t source_to_row,
        index_t source_to_col
    ) const;

    // ==========================================
    // Submatrix Extraction
    // NumPy style slicing
    // ==========================================

    Matrix slice(
        index_t from_row,
        index_t from_col,
        index_t to_row,
        index_t to_col
    ) const;

    // ==========================================
    // Column Extraction
    // Equivalent of:
    // create_column_vec(...)
    // ==========================================

    Vector column(
        index_t column_index
    ) const;

    // ==========================================
    // Raw Memory Access
    // ==========================================

    double* raw();

    const double* raw() const;

    // ==========================================
    // CSV Loader
    // Equivalent of:
    // mlfw_mat_double_from_csv(...)
    // ==========================================

    static Matrix fromCSV(
        const std::string& file_name
    );
};

}

#endif