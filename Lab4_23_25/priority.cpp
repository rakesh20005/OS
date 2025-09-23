#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Process
{
    int pid, arrival, burst, priority;
    int remaining, completion, turnaround, waiting, response;
    bool started;
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter arrival time of P" << p[i].pid << ": ";
        cin >> p[i].arrival;
        cout << "Enter burst time of P" << p[i].pid << ": ";
        cin >> p[i].burst;
        cout << "Enter priority of P" << p[i].pid << ": ";
        cin >> p[i].priority;
        p[i].remaining = p[i].burst;
        p[i].started = false;
        p[i].response = -1;  
    }


    sort(p.begin(), p.end(), [](Process &a, Process &b) {
        return a.arrival < b.arrival;
    });

    int completed = 0, currTime = 0;
    float total_tat = 0, total_wt = 0, total_rt = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MIN; 

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currTime && p[i].remaining > 0) {
                if (p[i].priority >highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest_priority) {
                    if (p[i].arrival < p[idx].arrival) {
                        idx = i;
                    }
                }
            }                                                                           
        }

        if (idx != -1) {
            if (!p[idx].started) {
                p[idx].response = currTime - p[idx].arrival;
                p[idx].started = true;
            }

            p[idx].remaining--;
            currTime++;

            if (p[idx].remaining == 0) {
                completed++;
                p[idx].completion = currTime;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;

                total_tat += p[idx].turnaround;
                total_wt += p[idx].waiting;
                total_rt += p[idx].response;
            }
        }
        else {
            currTime++;
        }
    }
    sort(p.begin(),p.end(),[](Process &a,Process &b){
        return a.completion<b.completion;
    });
    cout << "\nPID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (auto &proc : p) {
        cout << proc.pid << "\t" << proc.arrival<< "\t" << proc.burst << "\t" <<  proc.priority  << "\t\t" 
             << proc.completion << "\t\t" << proc.turnaround << "\t\t" << proc.waiting << "\t" << proc.response << "\n";
    }

    cout << "\nAverage Turnaround Time: " << total_tat / n;
    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Response Time: " << total_rt / n << "\n";

    return 0;
}
