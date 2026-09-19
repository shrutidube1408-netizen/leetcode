class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> events;
        for (const auto& b : buildings) {
            events.push_back({b[0], -b[2]}); // Start point (negative height)
            events.push_back({b[1], b[2]});  // End point (positive height)
        }

        sort(events.begin(), events.end());

        vector<vector<int>> result;
        multiset<int> heights = {0};
        int prev_max = 0;

        for (const auto& [x, h] : events) {
            if (h < 0) {
                heights.insert(-h);
            } else {
                heights.erase(heights.find(h));
            }

            int curr_max = *heights.rbegin();
            if (curr_max != prev_max) {
                result.push_back({x, curr_max});
                prev_max = curr_max;
            }
        }

        return result;
    }
};