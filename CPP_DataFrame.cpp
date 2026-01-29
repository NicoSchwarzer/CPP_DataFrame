#include "CPP_DataFrame.h"
#include <algorithm>  // for std::find
#include <stdexcept>  // for exceptions

// add_column
void DataFrame::add_column(std::string col_name, std::vector<Cell>& column) {
    columns_.push_back(col_name);
    cols_ = columns_.size();
    shape_.second = cols_;

    if (df_.empty()) {
        rows_ = column.size();
        shape_.first = rows_;
        for (size_t i = 0; i < rows_; i++) {
            index_.push_back(static_cast<int>(i));
        }
    }
    else if (rows_ != column.size()) {
        throw std::invalid_argument("Column size does not match existing DataFrame columns.");
    }

    df_[col_name] = column;
}

// set_index
void DataFrame::set_index(std::vector<Cell>& new_index) {
    if (new_index.size() != rows_) {
        throw std::invalid_argument("New index size does not match number of rows in DataFrame.");
    }
    index_ = new_index;
}

// get_shape
std::pair<int, int> DataFrame::get_shape() const {
    return shape_;
}

// get_index
std::vector<DataFrame::Cell> DataFrame::get_index() {
    return index_;
}

// get_columns
const std::vector<std::string>& DataFrame::get_columns() {
    return columns_;
}

// get_column
const std::vector<DataFrame::Cell>& DataFrame::get_column(const std::string& col_name) {
    auto it = df_.find(col_name);
    if (it == df_.end()) {
        throw std::invalid_argument("Column not found in DataFrame.");
    }
    return it->second;
}

// loc
DataFrame::Cell DataFrame::loc(const std::string col_name, size_t row) {
    if (row >= rows_) {
        throw std::out_of_range("Row index out of range.");
    }
    if (std::find(columns_.begin(), columns_.end(), col_name) == columns_.end()) {
        throw std::out_of_range("Column Name cannot be found.");
    }
    return df_[col_name][row];
}

// iloc
DataFrame::Cell DataFrame::iloc(size_t row, size_t col) {
    if (row >= rows_ && col >= cols_) {
        throw std::out_of_range("Row and column index out of range.");
    }
    if (row >= rows_) {
        throw std::out_of_range("Row index out of range.");
    }
    if (col >= cols_) {
        throw std::out_of_range("Column index out of range.");
    }
    const std::string& col_name = columns_[col];
    return df_[col_name][row];
}
