class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Build graph using a min-heap to pick lexicographically smallest destination first
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj;
        for (const auto& ticket : tickets) {
            adj[ticket[0]].push(ticket[1]);
        }

        vector<string> itinerary;
        dfs("JFK", adj, itinerary);

        // Reverse to get the correct chronological order
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }

private:
    void dfs(const string& airport, 
             unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& adj, 
             vector<string>& itinerary) {
        
        while (!adj[airport].empty()) {
            string next_airport = adj[airport].top();
            adj[airport].pop(); // Remove the edge after traversing
            dfs(next_airport, adj, itinerary);
        }
        
        // Push node after visiting all available outgoing paths (backtracking order)
        itinerary.push_back(airport);
    }
};