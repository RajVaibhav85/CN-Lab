
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main()
{
    // Access shared memory
    int shmid = shmget(1234, sizeof(int), 0666);

    // Attach shared memory
    int *traffic = (int*) shmat(shmid, NULL, 0);

    while (1)
    {
        // Read vehicle count
        int count = *traffic;

        char signal[100];

        // Decide signal based on vehicle count
        if (count <= 10)
            sprintf(signal, "GREEN - 10 seconds");

        else if (count <= 20)
            sprintf(signal, "GREEN - 20 seconds");

        else if (count <= 40)
            sprintf(signal, "GREEN - 30 seconds");

        else
            sprintf(signal, "GREEN - 45 seconds");

        cout << "\nVehicle Count: " << count << endl;
        cout << "Decision: " << signal << endl;

        // Send command through FIFO
        int fd = open("traffic_fifo", O_WRONLY);

        write(fd, signal, sizeof(signal));

        close(fd);
    }

    // Detach shared memory
    shmdt(traffic);

    return 0;
}
