
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main()
{
    // Create shared memory
    int shmid = shmget(1234, sizeof(int), 0666 | IPC_CREAT);

    // Attach shared memory
    int *traffic = (int*) shmat(shmid, NULL, 0);

    // Create FIFO
    mkfifo("traffic_fifo", 0666);

    while (1)
    {
        int count;

        cout << "\nEnter vehicle count (-1 to exit): ";
        cin >> count;

        if (count == -1)
            break;

        // Store vehicle count in shared memory
        *traffic = count;

        cout << "Vehicle count stored: " << *traffic << endl;

        // Open FIFO for reading
        int fd = open("traffic_fifo", O_RDONLY);

        char signal[100];

        read(fd, signal, sizeof(signal));

        cout << "Traffic Signal: " << signal << endl;

        close(fd);
    }

    // Detach shared memory
    shmdt(traffic);

    return 0;
}
