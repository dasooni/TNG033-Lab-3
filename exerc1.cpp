/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm>  //std:copy
#include <vld.h>

/*******************************
 * 1. Declarations              *
 ********************************/

// A function to test the tables created by the program
void test(const std::map<std::string, int>& t, 
    const std::vector<std::pair<std::string, int>>& v,
    const std::string& file_name, int n);

//Display
bool isPunct(char x) {
    //check if character x is a punctiation, the character - and finally line cont. 
    if (ispunct(x) && x != '-' && x != '\'') {
        return true;
    }
    return false;
}

//sort by frequency, descending order
bool sortDe(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    
    if (a.second == b.second) return (a.first < b.first);
    return(a.second > b.second);
}

/*******************************
 * 2. Main function             *
 *******************************/

int main() {
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{"../code/" + name};

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }
    //table that matches words with freq
    std::map<std::string, int> table;
    int counter{0};  // to count total number of words read from the input file
    std::string word; //variable to load in words from file

    //while there are words in the file
    while (in_File >> word) {
        //remove punctuation characters from word string
        word.erase(remove_if(word.begin(), word.end(), ::isPunct), word.end());
        //convert everything to lower case
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        //use [] operator to add word to table map
        ++table[word];
        //increment counter
        ++counter;
    }
    //vector that copies content of table
    std::vector<std::pair<std::string, int>> freq (table.begin(), table.end());
    //sort freq vector according to sortDe function, which sorts words in descending order. 
    std::sort(freq.begin(), freq.end(), ::sortDe);

    /* ************** Testing **************** */

    test(table, freq, name, counter);
}


/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n) {

    std::ifstream file{"../code/out_" + file_name};

    // Test if stream is in good state
    assert(bool(file) == true);

    
    std::map<std::string, int> result1;
    std::string word;
    int counter{0};
    int total{0};

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }
    //--bugfixing..
    std::cout << "Number of unique words in my table =  " << t.size() << "\n\n\n";
    std::cout << "Number of unique words in the test table =  " << result1.size() << "\n\n\n";
    //--bugfixing..
    auto it = t.begin();
    auto it2 = result1.begin();
    int i = 1;
    while (it != t.end() && it2 != result1.end()) {
        if (!(*it == *it2)) {
            std::cout << i << " : " << (*it == *it2) << "\n";
        }
        it++;
        it2++;
        i++;
    }
    //--bugfixing end
    assert(total == n);  // test if total number of words is correct
    assert(t == result1);

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{word, counter});
    }
    assert(v == result2);

    std::cout << "\nPassed all tests successfully!!\n";
}
