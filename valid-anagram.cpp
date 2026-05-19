class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;

        unordered_map<char, int> count;

        for (int i = 0; i < s.size(); i++) {
            count[s[i]]++;   // +1 for each element of s
            count[t[i]]--;   // -1 for each element of t
        }

        for (auto& pair : count) {
            if (pair.second != 0) return false;
        }
        return true; // if all counts == 0 --> anagram
    }
};
