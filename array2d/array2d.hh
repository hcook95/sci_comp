#ifndef ARRAY2D_HH
#define ARRAY2D_HH
#include <valarray> // valarray is used for underlying storage: https://www.cplusplus.com/reference/valarray/valarray



/* This is a partial implementation of a class representing a 2-dimensional array. Your job is to finish implementing
 * it. There are "TODO" comments explaining what needs to be done and placeholders labeled with "WRONG" to make it easy
 * to figure out what still needs to be fixed.
 * 
 * This implementation uses a 1D valarray to represent a 2D array, so you have to index manually. To get the first
 * element of the ith row, use the `i*n`th cell of the valarray. To get the jth cell of the ith row, use the `i*n+j`th.
 */



template <class T>
class Array2D {
    // Members
    int m, n;
    std::valarray<T> data;

public:
    // Read-only accessors
    const int &rows = m;
    const int &cols = n;

    // Constructors (default no-argument, move, and copy constructors, and destructor, should be fine)
    // Using a size
    Array2D(const int rows, const int cols): m{rows}, n{cols}, data(rows*cols) {}
    // Using a data pointer and a size
    Array2D(const T *const data, const int rows, const int cols): m{rows}, n{cols}, data(data, rows*cols) {}
    // TODO: implement this copy constructor
    Array2D(const Array2D &other): /* WRONG */ m{other.m}, n{other.n}, data{other.data} {}

    // Overload the assignment operator
    void operator=(const Array2D &other) {
        m = other.m; // class methods have access to the private elements of other instances of the class
        n = other.n;
        data.resize(other.data.size());
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                data[i*cols + j] = other.data[i*cols + j];
        // TODO: set `n` and `data` to the correct values
        // HINT: you need to resize `data` to the size of `other.data` before assigning it; see "copy assignment" at
        //       https://www.cplusplus.com/reference/valarray/valarray/operator=/#description to understand why.
    }

    // Overload the call operator to take a pair of indices and return the corresponding cell of data
    T &operator()(const int i, const int j) {return data[i*cols + j];}

    const T &operator()(const int i, const int j) const {return data[i*cols + j];}

    // Overload the index operator
    auto operator[](const int i) {return begin(data)+i*cols;}

    const auto operator[](const int i) const {return begin(data)+i*cols;}

    // Swap this Array2D with another
    friend void swap(Array2D &x, Array2D &y) {std::swap(x, y);}
};



#endif
