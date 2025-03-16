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
    // 2) outer loop over str1 (i) and inner loop over str2 (j)
    // 3) compute curr[j] as min of:
    //  - prev[j - 1] (if the current char of str1 matches str2)
    //  - curr[j - 1] + 1 (if we have to insert a character to current substring of str2 to get to str1)
    //  - prev[j] + 1 (if we have to delete character from str2[:j] to get to str1[:i])
    // 4) swap prev and curr 

    int l1 = str1.length(), l2 = str2.length();
    if (abs(l1 - l2) > d) return false;
    if (l1 > l2) return edit_distance_within(str2, str1, d);
    vector<int> prev(l1 + 1);
    for (int i = 0; i <= l1; i++) prev[i] = i;  
    vector<int> curr_row(l1 + 1);
    for (int char2 = 1; char2 <= l2; char2++) {
        curr_row[0] = char2; 
        int min_edit = char2;  
        for (int i = 1; i <= l1; i++) {
            int cost = str1[i - 1] != str2[char2 - 1], deletion = prev[i] + 1, insertion = curr_row[i-1] + 1, replace= prev[i-1] + cost;
            curr_row[i] = min({deletion, insertion, replace});
            min_edit = min(min_edit, curr_row[i]);
        }
        if (min_edit > d) return false;
        swap(prev, curr_row);
    } 
    return prev[l1] <= d;
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
                    
                    if (word == end_word) {cout << endl; for (auto e: new_ladder) cout << e << " "; cout<<endl; return new_ladder;} 
                    
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

    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

