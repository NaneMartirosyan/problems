#include <iostream>
#include <list>
#include <string>

using namespace std;

class hashTable {
private:
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups];  

public:
    bool is_Empty() const {
        int sum=0;
        for (int i = 0; i < hashGroups; i++) {
            sum += table[i].size();
        }
        return sum == 0;
    }

    int hashFunction(int key) {
        return key % hashGroups;
    }

    void Insert(int key, string value) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        bool keyExists = false;

        for (auto& kv : cell) {
            if (kv.first == key) {
                kv.second = value;
                keyExists = true;
                cout << "[INFO] Key exists. Value replaced.\n";
                break;
            }
        }

        if (!keyExists) {
            cell.emplace_back(key, value);
            cout << "[INFO] Pair (" << key << ", " << value << ") inserted.\n";
        }
    }

    void remove(int key) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        auto it = cell.begin();
        bool keyFound = false;

        for (; it != cell.end(); it++) {
            if (it->first == key) {
                keyFound = true;
                it = cell.erase(it);
                cout << "[INFO] Pair with key " << key << " removed.\n";
                break;
            }
        }

        if (!keyFound) {
            cout << "[WARN] Key " << key << " not found. Pair not removed.\n";
        }
    }

    string search_(int key) {
        int hashValue = hashFunction(key);
        auto& cell = table[hashValue];
        for (auto& kv : cell) {
            if (kv.first == key) {
                return kv.second;
            }
        }
        return "[ERROR] Key not found";
    }

    void display() {
        for (int i = 0; i < hashGroups; i++) {
            if (!table[i].empty()) {
                cout << "Group " << i << ": ";
                for (auto& kv : table[i]) {
                    cout << "(" << kv.first << ", " << kv.second << ") ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    hashTable ht;
    if (ht.is_Empty()) {
        cout << "Hash Table is empty.\n";
    } else {
        cout << "Hash Table is not empty.\n";
    }

    ht.Insert(101, "Alice");
    ht.Insert(102, "Bob");
    ht.Insert(103, "Charlie");
    ht.Insert(103, "Dave");  
    ht.display();

    cout << "Searching for key 102: " << ht.search_(102) << endl;
    cout << "Searching for key 105: " << ht.search_(105) << endl; 

    ht.remove(102);
    ht.display();

    if (ht.is_Empty()) {
        cout << "Hash Table is empty.\n";
    } else {
        cout << "Hash Table is not empty.\n";
    }

    return 0;
}
