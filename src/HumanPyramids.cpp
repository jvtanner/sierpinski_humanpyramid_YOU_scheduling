#include "HumanPyramids.h"
#include "Testing/HumanPyramidTests.h"
#include "strlib.h"
#include "error.h"
#include "grid.h"
using namespace std;

const int kWeight = 160;

double recursiveFunction(int row, int col, int pyramidHeight, Grid<int>& table);

//Wrapper function
double weightOnBackOf(int row, int col, int pyramidHeight) {
    Grid<int> table(row, col);
//    if (!table.inBounds(row, col)){
//        error("Out of bounds");
//    }
    return recursiveFunction(row, col, pyramidHeight, table);
}

/* Intakes a pyramid of people, each with a wieght of 160.
 * User specifies the height of the pyramid.
 * Checks to make sure that everything is in bounds, and
 * then calculates the weight being supported by each person
 */
double recursiveFunction(int row, int col, int pyramidHeight, Grid<int>& table){
    if (row == 0 && col == 0){
        return 0;
    }
    //Memoization step. Comparing all requests with this table first to avoid calculation.
    else if (table[row][col] != 0){
        return table[row][col];
    }
    else {
        int weightBack = 0;
        if (table.inBounds(row - 1, col - 1)){
            weightBack += (recursiveFunction(row - 1, col - 1, pyramidHeight, table) + kWeight) / 2;
        }
        if (table.inBounds(row - 1, col)){
            weightBack += (recursiveFunction(row - 1, col, pyramidHeight, table) + kWeight) / 2;
        }
        table[row][col] = weightBack;
        return weightBack;
    }
}






/* * * * * * Test Cases * * * * * */

ADD_TEST("Check the topmost person in the pyramid with nothing on shoulders.") {
    EXPECT_EQUAL(weightOnBackOf(0,0,3), 0);
}





/* * * * * * Test cases from the starter files below this point. * * * * * */

ADD_TEST("Provided Test: Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

ADD_TEST("Provided Test: Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

ADD_TEST("Provided Test: Warning! The next test will hang if you haven't implemented memoization.") {
    // Nothing to see here, folks. Move along...
}

ADD_TEST("Provided Test: Function returns a value, even for someone deep in the pyramid.") {
    /* This will take a LONG time to complete if memoization isn't implemented.
                 * We're talking "heat death of the universe" amounts of time. :-)
                 */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
             * very small and very large cases, etc.
             */
