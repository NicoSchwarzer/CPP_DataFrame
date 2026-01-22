
#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <stdexcept>
#include <variant>
#include <algorithm>

class DataFrame {

public:

	//to allow flexibility in data type for each column
	using Cell = std::variant<int, double, std::string, bool>;


	// No Constructed, using unordered map to store data

	// Adding a column
	// but allowing a data type - as in Pandas - so using std::string in data type declaratrion
	// Passing column vector by reference - avoiding unnecessary copying in memory 
	template <typename T>
	void add_column(std::string col_name, std::vector<T>& column) {

		columns_.push_back(col_name);
		cols_ = columns_.size();
		shape_.second = cols_;

		if (df_.empty()) {
			rows_ = column.size();
			shape_.first = rows_;

		}
		else if (rows_ != column.size()) {
			throw std::invalid_argument("Column size does not match existing DataFrame columns.");
		}

		std::vector<Cell> col_cells(column.begin(), column.end());
		df_[col_name] = col_cells;


	}


	// Getter for shape
	std::pair<int, int> get_shape() const {
		return shape_;
	}

	// Getter for columns (vector containing column names)
	const std::vector <std::string>& get_columns()  {
		return columns_;
	}

	// Getter for a column
	const std::vector<Cell>& get_column(const std::string& col_name) {
		auto it = df_.find(col_name);
		if (it == df_.end()) {
			throw std::invalid_argument("Column not found in DataFrame.");
		}
		return it -> second; // it = iterator, i.e. pointer to the pair <string, vector>
	}




	// LOC-alike getter function
	Cell loc(const std::string col_name, size_t row) {
		if (row > rows_) {
			throw std::out_of_range("Row index out of range.");
		}
		else if (std::find(columns_.begin(), columns_.end(), col_name) == columns_.end()) {
			throw std::out_of_range("Column Name cannot be found.");
		}
		else {
			return df_[col_name][row];
		}
	}



	// Modification using .loc
	void modify_by_loc(std::string& col_name, size_t row, auto new_value) {
		Cell new_value_cell = new_value; // converting to Cell type
		if (row > rows_) {
			throw std::out_of_range("Row index out of range.");
		}
		else if (std::find(columns_.begin(), columns_.end(), col_name) == columns_.end()) {
			throw std::out_of_range("Column Name cannot be found.");
		}
		// checking if valid data type 
		else if (new_value_cell.index() != df_[col_name][0].index()) {
			throw std::out_of_range("Wrong data type, does not match corresponding column.");
		} else {
			df_[col_name][row] = new_value_cell;
		}
		}

	// ILOC-alike getter function 
	Cell iloc(size_t row, size_t col) {
		if (row > rows_ && col > cols_) {
			throw std::out_of_range("Row and column index out of range.");
		}
		else if (row > rows_) {
			throw std::out_of_range("Row index out of range.");
		}
		else if (col > cols_) {
			throw std::out_of_range("Column index out of range.");
		}
		else {

		}
		const std::string& col_name = columns_[col];
		return df_[col_name][row];
	}

	// Modification using .iloc
	void modify_by_iloc(size_t row, size_t col, auto new_value) {
		Cell new_value_cell = new_value; // converting to Cell type
		if (row > rows_) {
			throw std::out_of_range("Row index out of range.");
		}
		else if (col > cols_) {
			throw std::out_of_range("Column index out of range.");
			// checking if valid data type 
		} else {
			const std::string& col_name = columns_[col];
			if (new_value_cell.index() != df_[col_name][0].index()) {
				throw std::out_of_range("Wrong data type, does not match corresponding column.");
			}
			else {
				df_[col_name][row] = new_value_cell;
			}
		}
		}

	

private:

	// declaring df_ as unordered map structure, the backbone of the dataframe 
	/// https://en.cppreference.com/w/cpp/container/unordered_map.html

	std::unordered_map <std::string, std::vector<Cell> > df_;


	size_t rows_ = 0;
	size_t cols_ = 0;
	std::vector <std::string> columns_;

	// Pandas - alike 'shape', not using tuple since its not editable, but pair 
	std::pair  <int, int> shape_ = { 0,0 };

};


