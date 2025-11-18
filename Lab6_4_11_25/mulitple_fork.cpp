#include <iostream>
#include <unistd.h>   // for fork(), execvp()
#include <sys/wait.h> // for wait()
#include <cstdlib>    // for exit()
using namespace std;

int main()
{
    cout << "Program started (Parent PID: " << getpid() << ")\n";

    const int N = 3; // Number of child processes you want
    pid_t pids[N];   // To store child PIDs

    for (int i = 0; i < N; ++i)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            cerr << " fork() failed at iteration " << i << endl;
            exit(1);
        }
        else if (pid == 0)
        {
            // ============================
            // 🔸 CHILD PROCESS SECTION
            // ============================
            cout << "\nChild Process " << i + 1 << " created.\n";
            cout << "   Child PID: " << getpid() << endl;
            cout << "   Parent PID: " << getppid() << endl;

            // Prepare command for execvp()
            char *args[] = {(char *)"ls", (char *)"-l", NULL};

            cout << "   Child " << i + 1 << " is executing 'ls -l'...\n";
            execvp("ls", args);

            // If execvp fails
            perror("execvp failed");
            exit(1);
        }
        else
        {
            // Parent process
            pids[i] = pid;
            cout << " Parent (PID: " << getpid() << ") created Child "
                 << i + 1 << " with PID " << pid << endl;
        }
    }

    // ============================
    // 🔹 PARENT WAITS FOR ALL CHILDREN
    // ============================
    cout << "\n Parent waiting for all children to finish...\n";

    for (int i = 0; i < N; ++i)
    {
        int status;
        waitpid(pids[i], &status, 0);

        if (WIFEXITED(status))
        {
            cout << "Child " << i + 1 << " (PID " << pids[i]
                 << ") exited with code " << WEXITSTATUS(status) << endl;
        }
        else
        {
            cout << " Child " << i + 1 << " (PID " << pids[i]
                 << ") terminated abnormally." << endl;
        }
    }

    cout << "\nAll children finished. Parent (PID: " << getpid() << ") exiting.\n";
    return 0;
}
