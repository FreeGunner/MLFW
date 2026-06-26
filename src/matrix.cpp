#include "mlfw/math/matrix.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace mlfw
{

// =====================================================
// Constructor
// Equivalent:
// mlfw_mat_double_create_new()
// =====================================================

Matrix::Matrix(dimension_t rows, dimension_t cols){

    if(rows == 0 || cols == 0){
        throw std::invalid_argument("Matrix dimensions must be greater than zero");
    }

    this->rows = rows;
    this->cols = cols;

    const size_t total_elements = static_cast<size_t>(rows) * cols;

    data = std::make_unique<double[]>(total_elements);

    std::memset(data.get(), 0, sizeof(double) * total_elements);
}

// =====================================================
// Copy Constructor
// =====================================================

Matrix::Matrix(const Matrix& other){
    rows = other.rows;
    cols = other.cols;

    const size_t total_elements = static_cast<size_t>(rows) * cols;

    data = std::make_unique<double[]>(total_elements);

    std::memcpy(data.get(),other.data.get(),sizeof(double) * total_elements);
}

// =====================================================
// Copy Assignment
// =====================================================

Matrix& Matrix::operator=(
    const Matrix& other
)
{
    if(this == &other){
        return *this;
    }

    rows = other.rows;
    cols = other.cols;

    const size_t total_elements = static_cast<size_t>(rows) * cols;

    data = std::make_unique<double[]>(total_elements);

    std::memcpy(data.get(),other.data.get(),sizeof(double) * total_elements);

    return *this;
}

// =====================================================
// Move Constructor
// =====================================================

Matrix::Matrix(
    Matrix&& other
) noexcept
{
    rows = other.rows;
    cols = other.cols;

    data = std::move(
        other.data
    );

    other.rows = 0;
    other.cols = 0;
}

// =====================================================
// Move Assignment
// =====================================================

Matrix& Matrix::operator=(
    Matrix&& other
) noexcept
{
    if(this == &other)
    {
        return *this;
    }

    rows = other.rows;
    cols = other.cols;

    data = std::move(
        other.data
    );

    other.rows = 0;
    other.cols = 0;

    return *this;
}

// =====================================================
// get()
// Equivalent:
// mlfw_mat_double_get()
// =====================================================

double Matrix::get(
    index_t row,
    index_t col
) const
{
    if(row >= rows)
    {
        throw std::out_of_range(
            "Row index out of range"
        );
    }

    if(col >= cols)
    {
        throw std::out_of_range(
            "Column index out of range"
        );
    }

    return data[
        row * cols + col
    ];
}

// =====================================================
// set()
// Equivalent:
// mlfw_mat_double_set()
// =====================================================

void Matrix::set(
    index_t row,
    index_t col,
    double value
)
{
    if(row >= rows)
    {
        throw std::out_of_range(
            "Row index out of range"
        );
    }

    if(col >= cols)
    {
        throw std::out_of_range(
            "Column index out of range"
        );
    }

    data[
        row * cols + col
    ] = value;
}

// =====================================================
// operator()
// Enables:
//
// A(1,2) = 10;
// =====================================================

double& Matrix::operator()(
    index_t row,
    index_t col
)
{
    if(row >= rows || col >= cols)
    {
        throw std::out_of_range(
            "Matrix index out of range"
        );
    }

    return data[
        row * cols + col
    ];
}

const double& Matrix::operator()(
    index_t row,
    index_t col
) const
{
    if(row >= rows || col >= cols)
    {
        throw std::out_of_range(
            "Matrix index out of range"
        );
    }

    return data[
        row * cols + col
    ];
}

// =====================================================
// getRows()
// Equivalent:
// mlfw_mat_double_get_dimensions()
// =====================================================

dimension_t Matrix::getRows() const
{
    return rows;
}

// =====================================================
// getCols()
// Equivalent:
// mlfw_mat_double_get_dimensions()
// =====================================================

dimension_t Matrix::getCols() const
{
    return cols;
}

// =====================================================
// fill entire matrix
// =====================================================

void Matrix::fill(
    double value
)
{
    const size_t total =
        static_cast<size_t>(rows) * cols;

    for(size_t i=0;i<total;i++)
    {
        data[i] = value;
    }
}

// =====================================================
// fill sub-region
// Equivalent:
// mlfw_mat_double_fill()
// =====================================================

void Matrix::fill(
    index_t from_row,
    index_t from_col,
    index_t to_row,
    index_t to_col,
    double value
)
{
    if(from_row > to_row)
    {
        return;
    }

    if(from_col > to_col)
    {
        return;
    }

    if(to_row > rows)
    {
        to_row = rows;
    }

    if(to_col > cols)
    {
        to_col = cols;
    }

    for(index_t r=from_row;r<to_row;r++)
    {
        for(index_t c=from_col;c<to_col;c++)
        {
            data[
                r*cols+c
            ] = value;
        }
    }
}

// =====================================================
// raw()
// =====================================================

double* Matrix::raw()
{
    return data.get();
}

const double* Matrix::raw() const
{
    return data.get();
}

// =====================================================
// fromCSV()
// Equivalent:
// mlfw_mat_double_from_csv()
// =====================================================

Matrix Matrix::fromCSV(
    const std::string& file_name
)
{
    std::ifstream file(
        file_name
    );

    if(!file)
    {
        throw std::runtime_error(
            "Unable to open CSV file"
        );
    }

    std::vector<
        std::vector<double>
    > rows_data;

    std::string line;

    while(
        std::getline(
            file,
            line
        )
    )
    {
        std::stringstream ss(line);

        std::string cell;

        std::vector<double> row;

        while(
            std::getline(
                ss,
                cell,
                ','
            )
        )
        {
            row.push_back(
                std::stod(cell)
            );
        }

        rows_data.push_back(
            row
        );
    }

    if(rows_data.empty())
    {
        throw std::runtime_error(
            "CSV is empty"
        );
    }

    dimension_t row_count =
        rows_data.size();

    dimension_t col_count =
        rows_data[0].size();

    Matrix result(
        row_count,
        col_count
    );

    for(index_t r=0;r<row_count;r++)
    {
        for(index_t c=0;c<col_count;c++)
        {
            result(
                r,
                c
            ) =
            rows_data[r][c];
        }
    }

    return result;
}

}