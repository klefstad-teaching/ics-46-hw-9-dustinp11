#include "ladder.h"
#include <algorithm>
#include <unordered_map>

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl; }


void error(string word1, string word2, string msg)
{
    cerr << msg << endl;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    if (abs(static_cast<int>(str1.size() - str2.size())) > d)
        return false;
        
    // case 1 - equal length
    if (str1.size() == str2.size()) {
        int diff = 0;
        for (size_t i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i]) {
                ++diff;
                if (diff > d)
                    return false;
            }
        }
        return diff <= d;
    } else {
        
        // case 2 - lengths off by 1
        const string& s = (str1.size() < str2.size()) ? str1 : str2;
        const string& t = (str1.size() < str2.size()) ? str2 : str1;
        
        size_t i = 0, j = 0;
        int diff = 0;
        for (; i < s.size() && j < t.size();) 
        {
            if (s[i] != t[j]) {
                ++diff;
                if (diff > d) return false;
                ++j;
            } else {
                ++i; ++j;
            }
        }
        
        return diff <= d;
    }
}


bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    vector<string> first_word({begin_word});
    ladder_queue.push(first_word);
    
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> curr_ladder = ladder_queue.front(); // current parital ladder
        string last_word = curr_ladder.back(); // last word in partial ladder
        ladder_queue.pop();


        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = curr_ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end_word) return new_ladder; 
                    
                    ladder_queue.push(new_ladder);
                }
            }
            
        }
    }
    
    return {};
}


void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
    string word; 
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty()) cout << "No word ladder found."; 
    else {
        cout << "Word ladder found: "; 
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << " ";
        }
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("awake", "sleep", word_list).size() == 8);

}

