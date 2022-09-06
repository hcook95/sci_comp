#include "array2d.hh"
#include <iostream>

using namespace std;

int main()
{
    size_t m = 5, n = 8;
    int data_a[m*n];
    int data_b[(m/2)*(n/2)];

    for (int i = 0; i < m*n; i++)
        data_a[i] = i;

    int j = (m/2)*(n/2)-1;
    for (int i = 0; i < (m/2)*(n/2); i++)
    {
        cout << j << endl;
        data_b[i] = j--; //counts down to zeros
    }

    cout << endl;

    

    Array2D<int> a{data_a, m, n};
    Array2D<int> b{data_b, m/2, n/2};
    swap(a, b);

    // sizes are correctly swapped
    // REQUIRE(a.rows == m/2);
    // REQUIRE(a.cols == n/2);

    // REQUIRE(b.rows == m);
    // REQUIRE(b.cols == n);

    // // elements are correctly swapped 
    int k = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cout << b(i, j) << endl;
    //         REQUIRE(b(i, j) == k++);

    cout << endl;

    k = (m/2)*(n/2)-1;
    for (int i = 0; i < m/2; i++)
        for (int j = 0; j < n/2; j++)
            cout << a(i, j) << endl;
    //         REQUIRE(a(i, j) == k--); //counts down from 0
    return 0;
}