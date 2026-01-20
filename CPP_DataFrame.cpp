
#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <stdexcept>
#include <variant>


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


