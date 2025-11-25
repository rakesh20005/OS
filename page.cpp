#include <bits/stdc++.h>
using namespace std;

// ---------------- FIFO ----------------
int FIFO(vector<int> pages, int frames) {
    unordered_set<int> s;
    vector<int> q;
    int faults = 0;

    for (int page : pages) {
        if (s.size() < frames) {
            if (s.find(page) == s.end()) {
                s.insert(page);
                q.push_back(page);
                faults++;
            }
        } else {
            if (s.find(page) == s.end()) {
                s.erase(q[0]);
                q.erase(q.begin());
                s.insert(page);
                q.push_back(page);
                faults++;
            }
        }
    }
    return faults;
}

// ---------------- LRU ----------------
int LRU(vector<int> pages, int frames) {
    unordered_set<int> s;
    unordered_map<int, int> lastUsed;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (s.size() < frames) {
            if (s.find(page) == s.end()) {
                s.insert(page);
                faults++;
            }
        } else {
            if (s.find(page) == s.end()) {
                int lru = pages[i];
                int mn = INT_MAX;

                for (auto p : s) {
                    if (lastUsed[p] < mn) {
                        mn = lastUsed[p];
                        lru = p;
                    }
                }

                s.erase(lru);
                s.insert(page);
                faults++;
            }
        }
        lastUsed[page] = i;
    }
    return faults;
}

// ---------------- OPTIMAL ----------------
int Optimal(vector<int> pages, int frames) {
    unordered_set<int> s;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (s.size() < frames) {
            if (s.find(page) == s.end()) {
                s.insert(page);
                faults++;
            }
        } else {
            if (s.find(page) == s.end()) {
                int farthest = i, replace = -1;

                for (auto p : s) {
                    int j;
                    for (j = i + 1; j < pages.size(); j++)
                        if (pages[j] == p) break;

                    if (j > farthest) {
                        farthest = j;
                        replace = p;
                    }
                }

                if (replace == -1) replace = *s.begin();
                s.erase(replace);
                s.insert(page);
                faults++;
            }
        }
    }
    return faults;
}

// ---------------- MRU ----------------
int MRU(vector<int> pages, int frames) {
    unordered_set<int> s;
    unordered_map<int, int> lastUsed;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (s.size() < frames) {
            if (s.find(page) == s.end()) {
                s.insert(page);
                faults++;
            }
        } else {
            if (s.find(page) == s.end()) {
                int mru = pages[i];
                int mx = -1;

                for (auto p : s) {
                    if (lastUsed[p] > mx) {
                        mx = lastUsed[p];
                        mru = p;
                    }
                }

                s.erase(mru);
                s.insert(page);
                faults++;
            }
        }
        lastUsed[page] = i;
    }
    return faults;
}

// ---------------- MAIN ----------------
int main() {
    int n, frames, choice;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> frames;

    cout << "\n1. FIFO\n2. LRU\n3. Optimal\n4. MRU\nChoose Algorithm: ";
    cin >> choice;

    switch (choice) {
        case 1: cout << "FIFO Page Faults = " << FIFO(pages, frames); break;
        case 2: cout << "LRU Page Faults = " << LRU(pages, frames); break;
        case 3: cout << "Optimal Page Faults = " << Optimal(pages, frames); break;
        case 4: cout << "MRU Page Faults = " << MRU(pages, frames); break;
        default: cout << "Invalid choice";
    }

    cout << endl;
    return 0;
}