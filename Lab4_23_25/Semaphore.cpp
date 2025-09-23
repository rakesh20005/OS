#include <iostream>
#include <queue>
using namespace std;

struct Semaphore {
    int value;
    queue<int> suspendedList;

};
int temp=2;
void wait(int id,Semaphore &s) {
        s.value--;
        if (s.value < 0) {
            s.suspendedList.push(id);
            cout << "Process " << id << " is suspended.\n";
        } else {
            temp--;
            cout << "Process " << id << " is running.\n";
            cout<<"temp value is :"<<temp<<"\n";
        }
    }

    void signal(int id,Semaphore &s) {
        s.value++;
        if (s.value <= 0) {
            if (!s.suspendedList.empty()) {
                int resumedId = s.suspendedList.front();
                s.suspendedList.pop();
                cout << "Process " << resumedId << " is resumed.\n";
            }
        }else{
            temp++;
            cout << "Process " << id << " is in suspendedList.\n";
            cout<<"temp value is :"<<temp<<"\n";
        }
    }
int main() {
    Semaphore s;
    s.value = 1;

    wait(1,s);  
    wait(2,s);  
    signal(1,s); 
    signal(2,s);  

    return 0;
}
