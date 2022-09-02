#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "array2d.hh"



// This is a set of tests for the Array2D class. "TODO" comments show which tests you need to implement.



// Sum an Array2D using the call operator
template <typename T>
T arraysum(const Array2D<T> &a) { // `const` is required to test the const version of operator()
    T sum{}; // default-initialized to be type-agnostic
    for (size_t i=0; i<a.rows; i++)
        for (size_t j=0; j<a.cols; j++)
            sum += a(i, j);
    return sum;
}


// TODO: Create a function taking a `const Array2D<T> &` that uses the index operator for use in the index operator test
// HINT: you can copy arraysum, replacing the call to operator() with a call to operator[]
template <typename T>
T arraysum_bracket(const Array2D<T> &a) { // `const` is required to test the const version of operator()
    T sum{}; // default-initialized to be type-agnostic
    for (size_t i=0; i<a.rows; i++)
        for (size_t j=0; j<a.cols; j++)
            sum += a[i][j];
    return sum;
}




TEST_CASE("Public accessors are correct", "[array2d]") {
    Array2D<int> a{1, 2};
    REQUIRE(a.rows == 1);
    REQUIRE(a.cols == 2);
}



TEST_CASE("Call operator works", "[array2d]") {
    // Setting via operator() works
    size_t m = 5, n = 8;
    Array2D<int> a{m, n};
    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            a(i, j) = 1 + 2 * i; // consecutive odd numbers; n of them sum to n^2
    REQUIRE(a(0, 0) == 1);
    REQUIRE(a(m-1, n-1) == 1*2*m-1);

    // Const version of operator() works
    REQUIRE(arraysum(a) == m*m*n); // arraysum takes a `const Array2D &`

    // Accessing via operator() works
    int d[m*n];
    for (size_t i=0; i<m*n; i++) d[i] = i; // each cell is the index of the underlying valarray
    Array2D<int> b{d, m, n};
    REQUIRE(b(0, 0) == 0);
    REQUIRE(b(m/2, n/2) == (m/2)*n+n/2);
    REQUIRE(b(m/2, n-1) == (m/2)*n+n-1);
    REQUIRE(b(m-1, n/2) == (m-1)*n+n/2);
    REQUIRE(b(m-1, n-1) == m*n-1);
}



TEST_CASE("Index operator works", "[array2d]") {
    // TODO: test operator[]; your tests can parallel those of the call operator
    // TODO: check that setting the value of a cell via operator[] works
    // TODO: check that the const version of operator[] works; use the helper function you created above
    // TODO: check that accessing via operator[] works
    // TODO: check that rows can be used independently; for example, something like this should work:
    //       auto row0 = myarr2d[0];
    //       REQUIRE(row0[4] == 4);
    // HINT: this function can closely mirror the call operator test
    
    // Setting via operator[] works
    size_t m = 5, n = 8;
    Array2D<int> a{m, n};
    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            a[i][j] = 1 + 2 * i; // consecutive odd numbers; n of them sum to n^2
    REQUIRE(a[0][0] == 1);
    REQUIRE(a[m-1][n-1] == 1*2*m-1);

    // Const version of operator[]] works
    REQUIRE(arraysum_bracket(a) == m*m*n); // arraysum_bracket takes a `const Array2D &`

    // Accessing via operator[] works
    int d[m*n];
    for (size_t i=0; i<m*n; i++) d[i] = i; // each cell is the index of the underlying valarray
    Array2D<int> b{d, m, n};
    REQUIRE(b[0][0] == 0);
    REQUIRE(b[m/2][n/2] == (m/2)*n+n/2);
    REQUIRE(b[m/2][n-1] == (m/2)*n+n-1);
    REQUIRE(b[m-1][n/2] == (m-1)*n+n/2);
    REQUIRE(b[m-1][n-1] == m*n-1);

    // independently using rows works
    for (size_t i=0; i<m*n; i++) d[i] = i%n; // each cell is the index of the column
    Array2D<int> c{d, m, n};

    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
        {
            auto row = c[i];
            REQUIRE(row[j] == j);
        }
}



TEST_CASE("Array2Ds can be copied and assigned", "[array2d]") {
    // TODO: test Array2D copy constructor and assignment operator
    // TODO: check that creating an array then copying it (e.g. with `auto arr2(arr1);`) works
    // TODO: check that mutating a copied array doesn't mutate the original
    // TODO: check that assigning an already-created array (using `=`) to another array of different size works
    // TODO: check that mutating an assigned array doesn't mutate the original

    // creating and then copying array works
    size_t m = 5, n = 8;
    Array2D<int> a{m, n};
    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            a(i, j) = i * n + j; // each cell is the index of the column
    
    auto a_copy(a);

    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            REQUIRE(a_copy(i, j) == a(i, j));
    

    // mutating copy array doesn't mutate the original
    a_copy(2, 2) = 42;
    REQUIRE(a_copy(2, 2) != a(2, 2));

    // assigning predefined array to another array works
    Array2D<int> a_copy2{2, 2};
    a_copy2 = a;

    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            REQUIRE(a_copy2(i, j) == a(i, j));

    //mutating the assigned array doesn't mutate the original
    a_copy2(2, 2) = 42;
    REQUIRE(a_copy2(2, 2) != a(2, 2));
}



TEST_CASE("Array2Ds can be swapped", "[array2d]") {
    // TODO: test the swapping of an array
    // TODO: check that Array2Ds of differing size can be successfully swapped
    // TODO: check that the `rows` and `cols` of each Array2D are correct after the swap
    // TODO: check that the elements in each Array2D are correct after the swap

    // Swapping arrays of differing sizes work works
    size_t m = 5, n = 8;
    int data_a[m*n];
    int data_b[(m/2)*(n/2)];

    for (int i = 0; i < m*n; i++)
        data_a[i] = i;

    int j = (m/2)*(n/2)-1;
    for (int i = 0; i < (m/2)*(n/2)-1; i++)
        data_b[i] = j--; //counts down to zeros

    

    Array2D<int> a{data_a, m, n};
    Array2D<int> b{data_b, m/2, n/2};
    swap(a, b);

    // sizes are correctly swapped
    REQUIRE(a.rows == m/2);
    REQUIRE(a.cols == n/2);

    REQUIRE(b.rows == m);
    REQUIRE(b.cols == n);

    // elements are correctly swapped 
    int k = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            REQUIRE(b(i, j) == k++);

    k = (m/2)*(n/2)-1;
    for (int i = 0; i < m/2; i++)
        for (int j = 0; j < n/2; j++)
            REQUIRE(a(i, j) == k--); //counts down from 0
}
