#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "CPP_DataFrame.cpp" 

using Cell = DataFrame::Cell; // to make vector columns in grow_df function less messy

void grow_df(DataFrame& df, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file");
    }

    
    //line by line 
    //straing with header
    std::string line, col_name;

    std::getline(file, line); // get first line 
    std::stringstream ss_header(line); // into stringstream
    std::vector<std::string> headers;

    while (std::getline(ss_header, col_name, ',')) {
        headers.push_back(col_name); // appending headers 
    }


    // Preparing a vector of Cell vectors for each column
    std::vector<std::vector<Cell>> columns(headers.size());

    // Read each row
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell_str;
        size_t col_index = 0;

        while (std::getline(ss, cell_str, ',')) {
            Cell value;

            // Try to detect type automatically
            if (cell_str == "0" || cell_str == "1") {
                value = (cell_str == "1");  // bool
            }
            else {
                try {
                    value = std::stoi(cell_str); // int
                }
                catch (...) {
                    try {
                        value = std::stod(cell_str); // double
                    }
                    catch (...) {
                        value = cell_str; // fallback to string
                    }
                }
            }

            columns[col_index].push_back(value);
            col_index++;
        }
        for (size_t k = col_index; k < headers.size(); ++k) {
            columns[k].push_back(std::string{}); 
        }
    }

    // 4Add columns to DataFrame
    for (size_t i = 0; i < headers.size(); i++) {
        df.add_column(headers[i], columns[i]);
    }

    file.close();
}

   

int main() {

    DataFrame df;

    // Load CSV file
    grow_df(df, "example_data.csv"); 
    
    // Print shape
    auto shape = df.get_shape();
    std::cout << "DataFrame shape: (" << shape.first << ", " << shape.second << ")" << std::endl;

    // Print headers
    std::cout << "Columns: ";
    for (const auto& col : df.get_columns()) {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    return 0;
}
