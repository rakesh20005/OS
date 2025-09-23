#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct Process
{
    int pid, arrival, burst, remaining, completion, turnaround, waiting, response;
    bool started;
};
int main()
{
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<Process> p(n);
    for (int i = 0; i < n; i++){
        p[i].pid = i + 1;
        cout << "Enter arrival time of P" << p[i].pid << ": ";
        cin >> p[i].arrival;
        cout << "Enter burst time of P" << p[i].pid << ": ";
        cin >> p[i].burst;
        p[i].remaining = p[i].burst;
        p[i].started = false;
    }

    queue<int> readyQueue;
    int curr_time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;
    vector<bool> inQueue(n, false);

    sort(p.begin(), p.end(), [](Process &a, Process &b){ 
        return a.arrival < b.arrival; });

    for (int i = 0; i < n; i++){
        if (p[i].arrival <= curr_time)
        {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }
    int prev_idx = -1, context_switching = 0;
    while (completed < n){
        if (!readyQueue.empty())
        {
            int idx = readyQueue.front();
            readyQueue.pop();
            if (prev_idx != -1 && prev_idx != idx)
                context_switching++;
            prev_idx = idx;

            Process &proc = p[idx];

            if (!proc.started){
                proc.response = curr_time - proc.arrival;
                proc.started = true;
            }

            int exec_time = min(quantum, proc.remaining);
            proc.remaining -= exec_time;
            curr_time += exec_time;

            for (int i = 0; i < n; i++){
                if (!inQueue[i] && p[i].arrival <= curr_time && p[i].remaining > 0)
                {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            if (proc.remaining == 0){
                proc.completion = curr_time;
                proc.turnaround = proc.completion - proc.arrival;
                proc.waiting = proc.turnaround - proc.burst;
                total_turnaround += proc.turnaround;
                total_waiting += proc.waiting;
                completed++;
            }
            else{
                readyQueue.push(idx);
            }
        }
        else{
            curr_time++;
            for (int i = 0; i < n; i++){
                if (!inQueue[i] && p[i].arrival <= curr_time && p[i].remaining > 0){
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
        }
    }

    sort(p.begin(), p.end(), [](Process &a, Process &b)
         { return a.completion < b.completion; });

    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (auto &proc : p)
    {
        cout << "P" << proc.pid << "\t"
             << proc.arrival << "\t"
             << proc.burst << "\t"
             << proc.completion << "\t\t"
             << proc.turnaround << "\t\t"
             << proc.waiting << "\t"
             << proc.response << "\n";
    }
    cout << "\nNo.of context switching: " << context_switching;

    cout << "\nAverage Waiting Time: " << total_waiting / n;
    cout << "\nAverage Turnaround Time: " << total_turnaround / n << "\n";

    return 0;
}
