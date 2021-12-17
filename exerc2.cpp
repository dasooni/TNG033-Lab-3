/*****************************************
 * Lab 3: exercise 2                      *
 * Anagrams table                         *
 ******************************************/

#include <iostream>
#include <fstream> //ifstream
#include <cassert> //assertion
#include <map> //std::map
#include <string> //std::string
#include <vector> //std::vector
#include <algorithm> //std:sort
#include <set> //std::set
#include <vld.h> //memory leak

// Define a testing function to check the contents of the anagrams table
void test(const std::map<std::string, std::set<std::string>>& p,
    const std::string& file_name);

/*******************************
 * 2. Main function             *
 *******************************/

int main() {
   
    std::string name;
    std::cout << "Text file: ";
    std::cin >> name;

    std::ifstream in_File{ "../code/" + name };

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    //to store the list of anagrams for every subject (sorting a word by alphabet)
    //changed value from string to set after realizing its easier to print like this.
    // set instead of vector as set is ordered, takes unique values.
    std::map<std::string, std::set<std::string>> ana;
    //to store words
    std::vector<std::string> words;

    //iterator for file
    auto fIT = std::istream_iterator<std::string>{ in_File };
    auto eIT = std::istream_iterator<std::string>{};

    //copy contents of the file into words vector
    std::copy(fIT, eIT, back_inserter(words));
   
    std::cout << " Total words in the file: " << words.size() << "\n";

    //lambda to check which words a subject corresponds to and inserts into ana
    auto anagrams = [&ana](const std::string &word) {
        //create a copy of word, subject
        std::string subject = word;
        //sort the subject alphabetically
        std::sort(subject.begin(), subject.end());
        //insert subject and the unmodified word
        ana[subject].insert(word);
    };

    //apply lambda function to words vector in a for_each loop
    std::for_each(words.begin(), words.end(), anagrams);

    //print all anagrams and subject
    std::for_each(ana.begin(), ana.end(), 
        [](const std::pair < std::string, std::set<std::string>>& p) {
        //print number of anagrams for each subject, and subjects
            if (p.second.size() > 1) {
                std::cout << "\n" << p.first << " , n = " << p.second.size() << " : ";

                std::for_each(p.second.begin(), p.second.end(),
                    [](const std::string& s) {
                        //print anagrams for each subject
                        std::cout << " " << s;

                    });
            }
        });

    /* ************** Testing **************** */
    test(ana, name);

}
void test(const std::map<std::string, std::set<std::string>>& p,
    const std::string& file_name) {

    std::ifstream file{ "../code/out_" + file_name };

    assert(bool(file) == true);

    std::vector<std::string> words;

    auto fIT = std::istream_iterator<std::string>{ file };
    auto eIT = std::istream_iterator<std::string>{};

    //copy contents of the file into words vector
    std::copy(fIT, eIT, back_inserter(words));

    std::map<std::string, std::set<std::string>> result;

    auto anagrams = [&result](const std::string& word) {
        //create a copy of word, subject
        std::string subject = word;
        //sort the subject alphabetically
        std::sort(subject.begin(), subject.end());
        //insert subject and the unmodified word
        result[subject].insert(word);
    };

    std::for_each(words.begin(), words.end(), anagrams);

    assert(result == p);
    std::cout << "\nPassed all tests successfully!!\n";    
}
