#include <iostream>  // cout, cend
#include <cmath>     // abs, max
#include <vector>    // vector
#include <ranges>    // subrange
#include <algorithm> // fill



// Grid size, initial interior value, and stopping criterion
const int rows = 1024, cols = 1024;
const float eps = 0.01, interiorval = 50;

// Return the cell-by-cell windowed average of current
void update(const auto &current, auto &next) {
    // make a copy of the current grid to store the next
    // auto next{current};
    // iterate over all interior cells, updating next[i][j] to the average of
    // the surrounding cells in current
    for (int i=1; i<rows-1; i++) {
        for (int j=1; j<cols-1; j++) {
            auto left  = current[i][j-1];
            auto right = current[i][j+1];
            auto above = current[i-1][j];
            auto below = current[i+1][j];
            next[i][j] = (left + right + above + below) / 4;
        }
    }
}

// Return the maximum difference between cells of current and next
// float maxabsdiff(const auto &current, const auto &next) {
//     // variable to keep track of the biggest difference we've seen so far
//     float biggest = 0;
//     // iterate over all interior cells, updating biggest as appropriate
//     for (int i=1; i<rows-1; i++) {
//         for (int j=1; j<cols-1; j++) {
//             biggest = std::max(biggest, std::abs(next[i][j]-current[i][j]));
//         }
//     }
//     // return the biggest difference that's been found
//     return biggest;
// }

bool isStable(const auto &current, const auto &next, const float eps) {
    for (int i=1; i<rows-1; i++) {
        for (int j=1; j<cols-1; j++) {
            float diff = std::abs(next[i][j]-current[i][j]);
            if (eps < diff)
                return false;
        }
    }
    return true;
}



int main() {
    // initialize the grid, setting all interior cells to 50
    std::vector current(rows, std::vector(cols, 0.0f));
    for (auto &row: std::ranges::subrange(current.begin()+1, current.end()-1)) {
        std::fill(row.begin()+1, row.end()-1, interiorval);
    } 
    // keep track of iteration count
    int iters = 0;
    // update until stable
    std::vector next(rows, std::vector(cols, 0.0f));
    while(true) {
        // get the grid at the next iteration
        update(current, next);
        if (!isStable(current, next, eps)) {
            // if the grid isn't yet stable, update current and increment iters
            std::swap(next, current);
            iters++;
        } else {
            // if the grid is stable, we're done--break out of the loop
            break;
        }
    }
    // print the iteration count and exit
    std::cout << iters << std::endl;
    return 0;
}