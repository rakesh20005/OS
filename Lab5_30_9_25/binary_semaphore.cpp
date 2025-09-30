#include <iostream>
#include <queue>
using namespace std;

struct binary_semaphore
{
    int value;
    queue<int>suspended_list;
   
};
void wait(int id,binary_semaphore &s){
    if(s.value==1){
        s.value=0;
        cout << "Process " << id << " is running.\n";
    }else{
       s.suspended_list.push(id);
       cout << "Process " << id << " is added to suspended list.\n";
    }
}
void signal(binary_semaphore &s){
    if(s.suspended_list.empty()){
        s.value=1;
      cout << " suspendedList is empty.\n";
    }else{
        int resumedId=s.suspended_list.front();
        s.suspended_list.pop();
        cout << "Process " << resumedId << " is resumed.\n";
    }
}
int  main()
{
    binary_semaphore s;
    s.value=1;
     wait(1,s);  
    wait(2,s);  
    wait(3,s);
    wait(4,s);
    signal(s); 
    signal(s); 
    signal(s); 
    signal(s);
    return 0;
}
