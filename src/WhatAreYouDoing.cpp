/*Returns all emphasis variations of a string*/

#include "WhatAreYouDoing.h"
#include "Testing/WhatAreYouDoingTests.h"
#include "strlib.h"
using namespace std;

#include "WhatAreYouDoing.h"
#include "Testing/WhatAreYouDoingTests.h"
#include "strlib.h"
#include <cctype>
using namespace std;

//Main function holding the recursion, runs through every possible emphasis for each word.
HashSet<string> allEmphasesRec(const Vector<string>& sentence, const string& chosen){
    if (sentence.isEmpty()){
        HashSet<string> collection;
        return collection + chosen;
    }else{
        string first = sentence[0];
        if (isalpha(first[0])){
            HashSet<string> upper = allEmphasesRec(sentence.subList(1), chosen + toUpperCase(first));
            HashSet<string> lower = allEmphasesRec(sentence.subList(1), chosen + toLowerCase(first));
            return upper + lower;
        }else{
            return allEmphasesRec(sentence.subList(1), chosen + first);
        }
    }
}

//Wrapper function. Tokenizes the string input.
HashSet<string> allEmphasesOf(const string& sentence) {
    Vector<string> words = tokenize(sentence);
    return allEmphasesRec(words, "");
}




/* * * * * * Test Cases * * * * * */

ADD_TEST("Handles an Empty String") {
    HashSet<string> expected = {""};

    EXPECT_EQUAL(allEmphasesOf(""), expected);
}




/* * * * * * Test cases from the starter files below this point. * * * * * */

ADD_TEST("Provided Test: Enumerates all options in a simple case.") {
    HashSet<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

ADD_TEST("Provided Test: Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

ADD_TEST("Provided Test: Enumerates all options in a more typical case.") {
    HashSet<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

ADD_TEST("Provided Test: Warning! This next test will hang if you produce duplicate capitalizations.") {
    // Nothing to see here, folks. Move along!
}

ADD_TEST("Provided Test: Recursion doesn't branch on non-word symbols.") {
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    HashSet<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}
