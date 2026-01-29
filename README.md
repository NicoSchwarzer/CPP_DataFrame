# C++ DataFrame

Forgive me, the readme file is not as extensive as it ought to be! This projecz is a simple C++ project that implements a **Pandas-like DataFrame** using `std::unordered_map` and `std::variant` to store columns with different data types. Includes functionality to read CSV files and inspect the data.

---
Pandas-alike funcitonalities include adding columns wihtout knowing the data type a priori, changing columns and/or values  using .loc() or .iloc(), indexing and setting the index, maniulating headers and some more - check it out :)

## Project Structure

CPP_DataFrame/

├── main.cpp           
├── CPP_DataFrame.cpp
├── CPP_DataFrame.h
└── example_data.csv   # Sample CSV to populate the DataFrame
