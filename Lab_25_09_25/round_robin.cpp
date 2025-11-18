
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct process{
    int pid, at, bt, rt, wt, tat;
};

int main(){
    int n, tq;
    cout << "Enter no. of processes: ";
    cin >> n;
    process p[n];
    cout << "Enter time quantum: ";
    cin >> tq;

    for(int i = 0; i < n; i++){
        p[i].pid = i + 1;
        cout << "Enter arrival time for P" << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Enter burst time for P" << p[i].pid << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
    }
    
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(p[i].at > p[j].at){
                swap(p[i].pid, p[j].pid);
                swap(p[i].at,p[j].at);
                swap(p[i].bt,p[j].bt);
            }
        }
    }

    queue<int> q; 
    int time = 0;
    int completed = 0;
    int idx = 0; 

    while(completed < n){
       
        while(idx < n && p[idx].at <= time){
            q.push(idx);
            idx++;
        }

        if(q.empty()){
            time++;
            continue;
        }

        int curr = q.front();
        q.pop();

 
        int etime = min(tq, p[curr].rt);
        p[curr].rt = p[curr].rt- etime;
        time = time+ etime;

    
        if(p[curr].rt == 0){
            completed++;
            p[curr].tat = time - p[curr].at;
            p[curr].wt = p[curr].tat - p[curr].bt;
        } else {
            q.push(curr);
        }
    }

    cout << "\nPID\tArrival\tBurst\tTurnaround\tWaiting\n";
    for(auto &proc : p){
        cout << "P" << proc.pid << "\t"
             << proc.at << "\t"
             << proc.bt << "\t"
             << proc.tat << "\t"
             << proc.wt << "\n";
    }

    return 0;
}














