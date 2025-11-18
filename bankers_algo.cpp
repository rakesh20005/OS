#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 5, m = 3;
    vector<vector<int>> alloc = {
        {0, 0, 1},  // P0
        {3, 0, 0},  // P1
        {1, 0, 1},  // P2
        {2, 3, 2},  // P3
        {0, 0, 3}}; // P4

    vector<vector<int>> max_need = {
        {7, 6, 3},
        {3, 2, 2},
        {8, 0, 2},
        {2, 1, 2},
        {5, 2, 3}};

    // ✔ Example that gives a safe sequence
    vector<int> total_resource = {20, 25, 27};

    vector<vector<int>> req;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        for (int j = 0; j < m; j++)
        {
            int req_resource = max_need[i][j] - alloc[i][j];
            temp.push_back(req_resource);
        }
        req.push_back(temp);
    }

    vector<int> avai(m);
    for (int j = 0; j < m; j++)
    {
        int t = 0;
        for (int i = 0; i < n; i++)
        {
            t += alloc[i][j];
        }
        avai[j] = total_resource[j] - t;
    }

    vector<int> safeSequence;
    vector<bool> executed(n, 0);
    bool isdone = 0;

    while (!isdone)
    {
        bool progress = false;

        for (int i = 0; i < n; i++)
        {
            if (executed[i])
                continue;

            bool isSatisfied = 1;
            for (int j = 0; j < m; j++)
            {
                if (req[i][j] > avai[j])
                    isSatisfied = 0;
            }

            if (isSatisfied)
            {
                safeSequence.push_back(i);
                executed[i] = 1;

                for (int j = 0; j < m; j++)
                {
                    avai[j] += alloc[i][j];
                }

                progress = true;
            }
        }

        if (safeSequence.size() == n)
            isdone = 1;

        if (!progress)
            break;
    }

    if (safeSequence.size() == n)
    {
        cout << "SAFE SEQUENCE: ";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << safeSequence[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "DEADLOCK OCCURED\n";
    }

    return 0;
}
