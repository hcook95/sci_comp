#include "array2d.hh"
#include <iostream>

int main()
{
    size_t m = 5, n = 8;
    // Array2D<int> a{m, n};
    // for (size_t i=0; i<m; i++)
    //     for (size_t j=0; j<n; j++)
    //         a(i, j) = 1 + 2 * i; // consecutive odd numbers; n of them sum to n^2

    int d[m*n];
    for (size_t i=0; i<m*n; i++) d[i] = i; // each cell is the index of the underlying valarray
    Array2D<int> b{d, m, n};

    
    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            std::cout << "i: " << i << "\tj: " << j << "\tval: " << b[i][j] << "\n";
    
    // REQUIRE(a(0, 0) == 1);
    // REQUIRE(a(m-1, n-1) == 1*2*m-1);
}