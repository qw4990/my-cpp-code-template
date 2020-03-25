#include "defines.h"

// Calculate the next vector used by KMP Algorithm.
// str:  a b a b a b z a b a b a b a
// next: 0 0 1 2 3 4 0 1 2 3 4 5 6 ?
void kmp_next(VEC<char> &str, VEC<int> &next) {
    int n = str.size();
    next.resize(n-1);
    next[0] = 0;
    int max_len = 0;
    FOR(i, 1, n-1) {
        while (max_len > 0 && str[i] != str[max_len])
            max_len = next[max_len - 1];
        if (str[max_len] == str[i]) max_len++;
        next[i] = max_len;
    }
}

// The KMP Algorithm.
// str:         a b a b a b z a b a b a b
// substr:      a b a
// position:    0   2         7   9
void kmp(VEC<char> &str, VEC<char> &substr, VEC<int> &position) {
    VEC<int> next;
    kmp_next(substr, next);
    position.clear();
    int n = str.size(), max_len = 0;
    REP(i, n) {
        while (max_len > 0 && str[i] != substr[max_len])
            max_len = next[max_len - 1];
        if (str[i] == substr[max_len]) max_len ++;
        if (max_len == substr.size()) {
            position.push_back(i - substr.size() + 1);
            max_len = next[max_len - 1];
        }
    }
}

// Manacher algorithm is used to calculate palindrome strings.
// All int elements in the original str vectors should be larger than 0.
// If the input str is "a b c c b c a", then the output are:
//  manastr: ^ a # b # c # c # b # c # a # $
//  manapal: 0 0 0 1 0 1 4 1 0 3 0 1 0 1 0 0
void manacher(VEC<char> &str, VEC<char> &manastr, VEC<int> &manapal) {
    // prepare
    manastr.clear();
    manastr.push_back('^');
    FOREACH(x, str) {
        manastr.push_back(x);
        manastr.push_back('#');
    }
    manastr.push_back('$');
    
    // calculate manapal
    int n = manastr.size();
    manapal.resize(n);
    int center = 0, right = 0;
    FOR(i, 1, n-1) {
        int i_mirror = 2 * center - i;
        if (right > i) manapal[i] = min(right - i, manapal[i_mirror]);
        else manapal[i] = 0;
        
        while (manastr[i + 1 + manapal[i]] == manastr[i - 1 - manapal[i]])
            manapal[i]++;
        
        if (i + manapal[i] > right) {
            center = i;
            right = i + manapal[i];
        }
    }
}