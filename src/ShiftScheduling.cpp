/*This function takes in a set of available shifts as well as the availability
 * of a given employee, and returns the optimum schedule that maximizes profit
 * while staying in the bounds of the max hours of the employee.
 */

#include "ShiftScheduling.h"
#include "Testing/ShiftSchedulingTests.h"
#include "vector.h"
#include "error.h"
using namespace std;

bool noOverlapsWithSchedule(Shift given, HashSet<Shift> schedule);

HashSet<Shift> whichIsHigher(HashSet<Shift> one, HashSet<Shift> two);

/*Takes a collection of all available shifts and builds the optimum schedule
 * within the constraints of total hours of the employee.
 */

HashSet<Shift> recursiveFunction(const HashSet<Shift>& shifts, const HashSet<Shift>& chosen, int maxHours) {
    HashSet<Shift> with;
    if (maxHours < 0){
        error("Please enter positive number of hours");
    }
    /*Base case*/
    if (shifts.isEmpty()){
        return chosen;
    } else {
        Shift shift = shifts.first();
        HashSet<Shift> remaining = shifts - shift;
        if (lengthOf(shift) <= maxHours && noOverlapsWithSchedule(shift, chosen)) {
            with = recursiveFunction(remaining, chosen + shift, maxHours - lengthOf(shift));
        }
        HashSet<Shift> without = recursiveFunction(remaining, chosen, maxHours);
        return whichIsHigher(with, without);
    }
}

//Compares the value between two schedules and returns the greater of the two
HashSet<Shift> whichIsHigher(HashSet<Shift> one, HashSet<Shift> two) {
    int result_one = 0;
    int result_two = 0;

    for (Shift shift: one) {
        result_one += valueOf(shift);
    }
    for (Shift shift: two) {
        result_two += valueOf(shift);
    }
    if (result_one > result_two) {
        return one;
    } else {
        return two;
    }
}

//another helper function which checks whether given shift conflicts with any shift within schedule
bool noOverlapsWithSchedule(Shift given, HashSet<Shift> schedule) {
    for (Shift shift : schedule){
        if (overlapsWith(shift, given)) {
            return false;
        }
    }
    return true;
}

//Wrapper function
HashSet<Shift> highestValueScheduleFor(const HashSet<Shift>& shifts, int maxHours) {
    HashSet<Shift> chosen;
    return recursiveFunction(shifts, chosen, maxHours);
}


/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

ADD_TEST("Rejects negative hours input.") {
    HashSet<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT_ERROR(highestValueScheduleFor(shifts, -5));
}




/* * * * * * Test cases from the starter files below this point. * * * * * */

/* This nice utility function lets you call highestValueScheduleFor, passing in
 * a Vector of shifts rather than a Set. This makes it a bit easier to test things.
 * You shouldn't need this function outside of these test cases.
 */
HashSet<Shift> asSet(const Vector<Shift>& shifts) {
    HashSet<Shift> result;
    for (Shift s: shifts) {
        result += s;
    }
    return result;
}

ADD_TEST("Provided Test: Pick a shift you do have time for.") {
    HashSet<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT(highestValueScheduleFor(shifts, 24).size() == 1);
    EXPECT(highestValueScheduleFor(shifts, 24) == shifts);
}

ADD_TEST("Provided Test: Don't pick a shift you don't have time for.") {
    HashSet<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT(highestValueScheduleFor(shifts, 3).isEmpty());
}

ADD_TEST("Provided Test: Don't pick overlapping shifts.") {
    Vector<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday,  9AM - 5PM, value is 1000
        { Day::MONDAY, 8, 18, 2000 },  // Monday, 10AM - 6PM, value is 2000
    };

    EXPECT(highestValueScheduleFor(asSet(shifts), 100).size() == 1);
    EXPECT(highestValueScheduleFor(asSet(shifts), 100).contains(shifts[1]));
}

ADD_TEST("Provided Test: Passes the example from the handout.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27 *
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28 *
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25 *
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25 *
    };

    /* Get back the solution. */
    HashSet<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

    /* Form the correct answer. It's the starred entries. */
    HashSet<Shift> actualSolution = {
        shifts[0], shifts[1], shifts[2], shifts[14]
    };

    EXPECT(computedSolution == actualSolution);
}
