// https://www.geeksforgeeks.org/dsa/the-celebrity-problem/

class Solution {
public:
    // celebrity = everyone knows him but he knows no one
    int findCelebrity(int n) {

        // Initialize the candidate for celebrity to 0
        int candidate = 0;

        // The first loop is to find a candidate who might be the celebrity.
        for (int i = 1; i < n; ++i) {

            // If the candidate knows 'i', then 'candidate' can't be a celebrity.
            // 'i' might be the celebrity.
            if (knows(candidate, i)) {
                candidate = i;
            }
        }

        // to confirm whether the candidate is celebrity
        for (int i = 0; i < n; ++i) {
            if (candidate != i && (knows(candidate, i) || !knows(i, candidate))) {
                return -1; // no such celebrity
            }
        }

        return candidate;
    }
};
