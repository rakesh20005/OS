#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>   // for fork(), execvp(), getpid()
#include <sys/wait.h> // for waitpid()
#include <cstdlib> 
using namespace std;

struct Semaphore {
    int value;
    queue<int> suspendedList;
};

// Global vectors to track execution and child processes
vector<int> executionOrder;
vector<int> processesWithChild;

// Wait (P) operation
void waitProcess(int id, Semaphore &s) {
    s.value--;
    if (s.value < 0) {
        s.suspendedList.push(id);
        cout << "Process " << id << " is suspended (waiting for semaphore).\n";
    } else {
        cout << "Process " << id << " acquired semaphore.\n";
    }
}

// Signal (V) operation
void signalProcess(Semaphore &s) {
    s.value++;
    if (s.value <= 0 && !s.suspendedList.empty()) {
        int resumedId = s.suspendedList.front();
        s.suspendedList.pop();
        cout << "Process " << resumedId << " is resumed from suspended list.\n";
    }
}

// Main program
int main() {
    int n; // number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    int sysCallCount;
    cout << "Enter number of processes having system calls: ";
    cin >> sysCallCount;

    vector<int> sysCallProcs(sysCallCount);
    cout << "Enter process IDs having system calls: ";
    for (int i = 0; i < sysCallCount; ++i)
        cin >> sysCallProcs[i];

    int batchSize;
    cout << "Enter number of processes per batch: ";
    cin >> batchSize;

    Semaphore sem;
    sem.value = 1; // binary semaphore


    // Iterate through batches
    for (int i = 1; i <= n; i += batchSize) {
        cout << "\n Starting batch from process " << i << " \n";
        vector<int> batch;

        // Collect current batch of processes
        for (int j = i; j < i + batchSize && j <= n; ++j) {
            batch.push_back(j);
        }

        // Step 1: Execute system call processes (child processes)
        for (int pid : batch) {
            bool isSystemCall = false;
            for (int sysId : sysCallProcs) {
                if (pid == sysId) {
                    isSystemCall = true;
                    break;
                }
            }

            if (isSystemCall) {
                waitProcess(pid, sem);

                pid_t childPid = fork();
                if (childPid == 0) {
                    // Child process
                    cout << "[Child] System call executed by process " << pid
                         << " (PID: " << getpid() << ")\n";
                    sleep(1); // simulate system call execution
                    exit(0);
                } else if (childPid > 0) {
                    // Parent process waits for child to finish
                    waitpid(childPid, NULL, 0);
                    signalProcess(sem);
                    executionOrder.push_back(pid);
                    processesWithChild.push_back(pid);
                } else {
                    cerr << "Fork failed for process " << pid << endl;
                }
            }
        }

        // Step 2: Execute remaining (non-system-call) processes
        cout << "\nExecuting remaining (non-system-call) processes\n";
        for (int pid : batch) {
            bool isSystemCall = false;
            for (int sysId : sysCallProcs) {
                if (pid == sysId) {
                    isSystemCall = true;
                    break;
                }
            }

            if (!isSystemCall) {
                waitProcess(pid, sem);
                cout << "Regular process " << pid << " executed (PID: " << getpid() << ").\n";
                sleep(1); // simulate some work
                signalProcess(sem);
                executionOrder.push_back(pid);
            }
        }
    }

    cout << "\nExecution complete \n";

    // Print final execution order
    cout << "\n Process Execution Order \n";
    for (size_t i = 0; i < executionOrder.size(); ++i) {
        cout << executionOrder[i];
        if (i < executionOrder.size() - 1)
            cout << " -> ";
    }
    cout << "\n";

    // Print processes with child processes (system calls)
    cout << "\n Processes with Child Processes (System Calls) \n";
    if (processesWithChild.empty()) {
        cout << "None\n";
    } else {
        for (int pid : processesWithChild)
            cout << "Process " << pid << " created a child process.\n";
    }


    return 0;
}
