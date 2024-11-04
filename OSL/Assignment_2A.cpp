#include <iostream>
#include <unistd.h>  // For fork(), getpid(), getppid()
#include <sys/types.h>  // For pid_t
#include <cstdlib>  // For exit()

using namespace std;

int main() {
    pid_t pid = fork();  // Fork a new process

    if (pid > 0) {  // Parent process
        sleep(3);  // Parent sleeps for 2 seconds
        cout << "\nParent process is terminated!!" << endl;
    } else if (pid == 0) {  // Child process
        cout << "\nChild Before Sleep!!" << endl;
        cout << "Child process id: " << getpid() << endl;
        cout << "Parent process id: " << getppid() << endl;

        sleep(2);  // Child sleeps for 5 seconds

        cout << "\nChild After Sleep!!" << endl;
        cout << "Child process id: " << getpid() << endl;
        cout << "Parent process id: " << getppid() << endl;
    } else {  // If fork fails
        cerr << "Fork failed!" << endl;
        exit(1);
    }

    return 0;
}
