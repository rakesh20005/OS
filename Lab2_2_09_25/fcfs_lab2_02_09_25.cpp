#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival, burst;
    int completion, turnaround, waiting,response;
};

int main() {
    int n;
    cout << "No.of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Arrival time of P" << p[i].pid << ": ";
        cin >> p[i].arrival;
        cout << "Burst time of P" << p[i].pid << ": ";
        cin >> p[i].burst;
    }

    sort(p.begin(), p.end(), [](Process &a, Process &b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;
    float total_wait = 0, total_turnaround = 0;

    for (auto &proc : p) {
        if (current_time < proc.arrival)
            current_time = proc.arrival;

        proc.completion = current_time + proc.burst;
        proc.turnaround = proc.completion - proc.arrival;
        proc.waiting = proc.turnaround - proc.burst;
        proc.response= current_time-proc.arrival;

        current_time = proc.completion;

        total_wait += proc.waiting;
        total_turnaround += proc.turnaround;
    }

    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (auto &proc : p) {
        cout << "P" << proc.pid << "\t"
             << proc.arrival << "\t"
             << proc.burst << "\t"
             << proc.completion << "\t\t"
             << proc.turnaround << "\t\t"
             << proc.waiting << "\t"
             <<proc.response<< "\n";
    }
    cout << "\nAverage Waiting Time: " << total_wait / n;
    cout << "\nAverage Turnaround Time: " << total_turnaround / n << "\n";

    return 0;
}
