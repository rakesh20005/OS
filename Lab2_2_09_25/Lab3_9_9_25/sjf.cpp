#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> 
using namespace std;
struct Process{
int pid,arrival,burst,completion,turnaround,waiting,response;
bool completed;
};
int main(){
    int n;
    cout<<"enter No.of processes\n";
    cin>>n;
   vector<Process>p(n);
   
   for(int i=0;i<n;i++){
    p[i].pid=i+1;
    cout<<"enter arrival time of "<<""<<p[i].pid<<":";
    cin>>p[i].arrival;
    cout<<"enter burst time of "<<p[i].pid<<":";
    cin>>p[i].burst;
    p[i].completed=0;
   }
   
   int curr_time=0,proc_completed=0;
   float total_wait=0,total_turnaround=0;
  while(proc_completed<n){
    int idx=-1;
    int min_burst=INT_MAX;
    for(int i=0;i<n;i++){
        if(!p[i].completed &&p[i].arrival<=curr_time){
            if(p[i].burst<min_burst){
                min_burst=p[i].burst;
                idx=i;
            }else if(p[i].burst==min_burst){
                if(p[i].arrival<p[idx].arrival){
                    idx=i;
                }
            }
        }
       
    }
     if(idx!=-1){
            Process &proc=p[idx];
            proc.response=curr_time-proc.arrival;
            curr_time+=proc.burst;
            proc.completion=curr_time;
            proc.turnaround=proc.completion-proc.arrival;
            proc.waiting=proc.turnaround-proc.burst;
              proc.completed=1;
            proc_completed++;
            total_turnaround+=proc.turnaround;
            total_wait+=proc.waiting;
          
        }else{
            curr_time++;//cpu idle
        }

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