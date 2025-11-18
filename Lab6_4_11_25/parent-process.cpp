#include <iostream>
#include <unistd.h>   // for fork(), execvp()
#include <sys/wait.h> // for wait()
#include <cstdlib>    // for exit()

using namespace std;

int main()
{
    cout << "Program started (PID: " << getpid() << ")\n";

    // Step 1: Create a new process using fork()
    pid_t pid = fork();

    if (pid < 0)
    {
        cerr << " fork() failed!" << endl;
        exit(1);
    }
    else if (pid == 0)
    {
        // ============================
        // 🔸 CHILD PROCESS SECTION
        // ============================
        cout << "\nInside Child Process:\n" ;
        cout << "   Child PID: " << getpid() << endl;
        cout << "   Parent PID (of child): " << getppid() << endl;

        // Prepare command for execvp()
        char *args[] = {"ls", "-l", NULL};

        cout << "   Child is about to execute 'ls -l' using execvp()...\n" ;

        // Step 2: Replace child process image with "ls -l"
        execvp("ls", args);

        // If execvp() returns, it failed
        perror("execvp failed");
        exit(1);
    }
    else
    {
        // ============================
        // 🔹 PARENT PROCESS SECTION
        // ============================
        cout << "\n Inside Parent Process:" << endl;
        cout << "   Parent PID: " << getpid() << endl;
        cout << "   Created Child with PID: " << pid << endl;

        cout << "   Parent is waiting for the child to finish..." << endl;

        // Step 3: Wait for the child to finish
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            cout << "   Child finished normally with exit code: " << WEXITSTATUS(status) << endl;
        }
        else
        {
            cout << "   Child terminated abnormally!" << endl;
        }

        cout << "   Parent process resumes after child finishes." << endl;
    }

    cout << "\nProgram ending (PID: " << getpid() << ")" << endl;

    return 0;
}
