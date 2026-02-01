// https://www.hellointerview.com/learn/code/intervals/employee-free-time
class Solution {
public:
    vector<vector<int>> employeeFreeTime(vector<vector<vector<int>>> schedule) {
        vector<vector<int>> allSchedules;
        for(auto empSchedule: schedule) {
            allSchedules.insert(allSchedules.end(), empSchedule.begin(), empSchedule.end());
        }

        vector<vector<int>> mergedSchedules = mergeIntervals(allSchedules);

        vector<vector<int>> ans;
        for(int i = 1; i < mergedSchedules.size(); i++) {
            if(mergedSchedules[i-1][1] < mergedSchedules[i][0]) {
                ans.push_back({mergedSchedules[i-1][1], mergedSchedules[i][0]});
            }
        }
        return ans;
    }
private:
    vector<vector<int>> mergeIntervals(vector<vector<int>> &a) {
        if(a.empty())
            return {};
        
        sort(a.begin(), a.end());

        vector<vector<int>> merged;
        int l = a[0][0], r = a[0][1];
        for(int i = 1; i < a.size(); i++) {
            if(a[i][0] <= r) {
                r = max(r, a[i][1]);
            } else {
                merged.push_back({l, r});
                l = a[i][0];
                r = a[i][1];
            }
        }
        merged.push_back({l, r});
        return merged;
    }
};
