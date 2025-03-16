#include "ladder.h"
#include <algorithm>

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl; }


void error(string word1, string word2, string msg)
{
    cerr << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    // idea of this algorithm:
    // 1) initalize: prev (length str2 + 1 = m + 1), curr (length str2 + 1 = m + 1)
    // where on the ith loop, prev[j] represents the minimum distance from str1[:i] to str2[:j]
    // 2) outer loop over str1 (i) and inner loop over str2 (j) within bounds:
    // [max(1, i - d), min(m, i + d)]
    // 3) compute curr[j] as min of:
    //  - prev[j - 1] (if the current char of str1 matches str2)
    //  - curr[j - 1] + 1 (if we have to insert a character to current substring of str2 to get to str1)
    //  - prev[j] + 1 (if we have to delete character from str2[:j] to get to str1[:i])
    // 4) swap prev and curr 


    int l1 = str1.size(), l2 = str2.size();
    if (abs(l1 - l2) > d) return false;

    vector<int> prev(l2 + 1);
    vector<int> curr(l2 + 1);

    for (int i = 0; i <= l2; ++i) prev[i] = i; 

    for (int char1 = 1; char1 <= l1; ++char1) {
        curr[0] = char1;

        for (int char2 = max(1, char1 - d); char2 <= min(l2, char1 + d); ++char2) {
            // we want to limit bounds to be between char1 - d and char1 + d to ensure we dont exceed edit threshold
            // but we also need to make sure char2 is within bounds, so intialize to max of 1 and char1 - d and loop until min of l2 and char1 + d
            if (str1[char1 - 1] == str2[char2 - 1]) { curr[char1] = prev[char2 - 1]; continue;}
            else {
                int deletion_cost = prev[char2] + 1;
                int insertion_cost = curr[char2 - 1] + 1;
                int substitution_cost = prev[char2 - 1] + 1;
                curr[char2] = min({deletion_cost, insertion_cost, substitution_cost});
            }
        }
        swap(prev, curr);
    }
    return prev[l2] <= d;
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

        for (string word : word_list) {
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
    if (ladder.empty()) cout << "No word ladder found." << endl;
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
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

    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

