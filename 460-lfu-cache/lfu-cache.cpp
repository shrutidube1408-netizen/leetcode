#include <unordered_map>
#include <list>

class LFUCache {
private:
    int cap;
    int minFreq;
    
    // key -> {val, freq}
    std::unordered_map<int, std::pair<int, int>> keyToValFreq;
    // key -> iterator in list of keys for that frequency
    std::unordered_map<int, std::list<int>::iterator> keyToIter;
    // freq -> list of keys with this frequency (LRU order)
    std::unordered_map<int, std::list<int>> freqToList;

    void updateFreq(int key) {
        int freq = keyToValFreq[key].second;
        freqToList[freq].erase(keyToIter[key]);

        if (freqToList[freq].empty()) {
            freqToList.erase(freq);
            if (minFreq == freq) {
                minFreq++;
            }
        }

        keyToValFreq[key].second++;
        freqToList[freq + 1].push_front(key);
        keyToIter[key] = freqToList[freq + 1].begin();
    }

public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}
    
    int get(int key) {
        if (keyToValFreq.find(key) == keyToValFreq.end()) return -1;
        updateFreq(key);
        return keyToValFreq[key].first;
    }
    
    void put(int key, int value) {
        if (cap <= 0) return;

        if (keyToValFreq.find(key) != keyToValFreq.end()) {
            keyToValFreq[key].first = value;
            updateFreq(key);
            return;
        }

        if (keyToValFreq.size() >= cap) {
            int evictKey = freqToList[minFreq].back();
            freqToList[minFreq].pop_back();
            if (freqToList[minFreq].empty()) {
                freqToList.erase(minFreq);
            }
            keyToValFreq.erase(evictKey);
            keyToIter.erase(evictKey);
        }

        keyToValFreq[key] = {value, 1};
        freqToList[1].push_front(key);
        keyToIter[key] = freqToList[1].begin();
        minFreq = 1;
    }
};