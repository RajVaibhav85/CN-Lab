
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    // Create shared memory
    int shmid = shmget(1234, sizeof(int), 0666 | IPC_CREAT);

    // Attach shared memory
    int *vehicle_count = (int *)shmat(shmid, NULL, 0);

    // Create named pipe
    mkfifo("traffic_fifo", 0666);

    // Open FIFO for writing
    int fd = open("traffic_fifo", O_WRONLY);

    int count;
    char signal[20];

    for(int i = 0; i < 5; i++)
    {
        printf("\nEnter number of vehicles: ");
        scanf("%d", &count);

        // Store count in shared memory
        *vehicle_count = count;

        // Decide traffic signal
        if(count < 10)
            strcpy(signal, "GREEN");
        else if(count <= 20)
            strcpy(signal, "YELLOW");
        else
            strcpy(signal, "RED");

        // Send signal through FIFO
        write(fd, signal, strlen(signal) + 1);

        printf("Vehicle count stored: %d\n", count);
        printf("Signal command sent: %s\n", signal);
    }

    close(fd);
    shmdt(vehicle_count);

    unlink("traffic_fifo");

    return 0;
}
