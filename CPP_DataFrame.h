#ifndef CPP_DataFrame_H
#define CPP_DataFrame_H

#include <vector>
#include <unordered_map>
#include <variant>
#include <string>
#include <utility>
#include <stdexcept>
#include <algorithm>

class DataFrame {
public:
    using Cell = std::variant<int, double, std::string, bool>;

    void add_column(std::string col_name, std::vector<Cell>& column);
    void set_index(std::vector<Cell>& new_index);

    std::pair<int, int> get_shape() const;
    std::vector<Cell> get_index();
    const std::vector<std::string>& get_columns();
    const std::vector<Cell>& get_column(const std::string& col_name);

    Cell loc(const std::string col_name, size_t row);
    Cell iloc(size_t row, size_t col);

private:
    std::unordered_map<std::string, std::vector<Cell>> df_;
    size_t rows_ = 0;
    size_t cols_ = 0;
    std::vector<std::string> columns_;
    std::vector<Cell> index_;
    std::pair<int, int> shape_ = { 0, 0 };

public:
    // ⬇️ TEMPLATE METHODS MUST COME AFTER MEMBER DECLARATIONS ⬇️

    template <typename T>
    void modify_by_loc(std::string& col_name, size_t row, T new_value) {
        Cell new_value_cell = new_value;

        if (row > rows_) {
            throw std::out_of_range("Row index out of range.");
        }
        else if (std::find(columns_.begin(), columns_.end(), col_name) == columns_.end()) {
            throw std::out_of_range("Column Name cannot be found.");
        }
        else if (new_value_cell.index() != df_[col_name][0].index()) {
            throw std::out_of_range("Wrong data type, does not match corresponding column.");
        }
        else {
            df_[col_name][row] = new_value_cell;
        }
    }

    template <typename T>
    void modify_by_iloc(size_t row, size_t col, T new_value) {
        Cell new_value_cell = new_value;

        if (row > rows_) {
            throw std::out_of_range("Row index out of range.");
        }
        else if (col > cols_) {
            throw std::out_of_range("Column index out of range.");
        }
        else {
            const std::string& col_name = columns_[col];
            if (new_value_cell.index() != df_[col_name][0].index()) {
                throw std::out_of_range("Wrong data type, does not match corresponding column.");
            }
            else {
                df_[col_name][row] = new_value_cell;
            }
        }
    }
};

#endif
