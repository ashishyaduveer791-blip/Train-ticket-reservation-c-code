#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AC3_SEATS 70
#define SL_SEATS 72
#define CC_SEATS 60

int ac3Seats[AC3_SEATS];
int slSeats[SL_SEATS];
int ccSeats[CC_SEATS];

void initSeats()
{
    memset(ac3Seats, 0, sizeof(ac3Seats));
    memset(slSeats, 0, sizeof(slSeats));
    memset(ccSeats, 0, sizeof(ccSeats));

    int ac3Booked[] = {2, 3, 7, 8, 9, 10, 25, 26, 27, 44, 45, 52};
    int slBooked[] = {1, 5, 6, 12, 18, 19, 20, 33, 34, 50, 51, 70};
    int ccBooked[] = {3, 4, 5, 22, 23, 24, 25, 40, 41, 42, 58, 59};

    for (int i = 0; i < sizeof(ac3Booked) / sizeof(int); i++)
        ac3Seats[ac3Booked[i] - 1] = 1;
    for (int i = 0; i < sizeof(slBooked) / sizeof(int); i++)
        slSeats[slBooked[i] - 1] = 1;
    for (int i = 0; i < sizeof(ccBooked) / sizeof(int); i++)
        ccSeats[ccBooked[i] - 1] = 1;
}

int *getSeatArray(const char *className, int *size)
{
    if (strcasecmp(className, "AC3") == 0)
    {
        *size = AC3_SEATS;
        return ac3Seats;
    }
    if (strcasecmp(className, "SL") == 0)
    {
        *size = SL_SEATS;
        return slSeats;
    }
    if (strcasecmp(className, "CC") == 0)
    {
        *size = CC_SEATS;
        return ccSeats;
    }
    return NULL;
}

int countAvailable(int *seats, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
        if (seats[i] == 0)
            count++;
    return count;
}

int findContiguous(int *seats, int size, int n)
{
    int run = 0;
    for (int i = 0; i < size; i++)
    {
        if (seats[i] == 0)
            run++;
        else
            run = 0;
        if (run == n)
            return i - n + 1;
    }
    return -1;
}

int main(int argc, char **argv)
{
    initSeats();

    if (argc == 1)
    {
        printf("Seat availability:\n");
        printf("AC3: %d/%d\n", countAvailable(ac3Seats, AC3_SEATS), AC3_SEATS);
        printf("SL:  %d/%d\n", countAvailable(slSeats, SL_SEATS), SL_SEATS);
        printf("CC:  %d/%d\n", countAvailable(ccSeats, CC_SEATS), CC_SEATS);
        printf("Usage: %s <CLASS> <N> [--contiguous]\n", argv[0]);
        return 0;
    }

    if (argc < 3)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    int requested = atoi(argv[2]);
    if (requested <= 0)
    {
        printf("Invalid number of seats\n");
        return 1;
    }

    int contiguous = (argc >= 4 && strcmp(argv[3], "--contiguous") == 0);
    int size;
    int *seats = getSeatArray(argv[1], &size);
    if (!seats)
    {
        printf("Unknown class %s\n", argv[1]);
        return 1;
    }
    if (requested > size)
    {
        printf("Request exceeds total seats\n");
        return 1;
    }

    int available = countAvailable(seats, size);
    if (contiguous)
    {
        int start = findContiguous(seats, size, requested);
        if (start >= 0)
        {
            printf("YES: seats ");
            for (int i = 0; i < requested; i++)
                printf("%d ", start + i + 1);
            printf("available in %s\n", argv[1]);
        }
        else
        {
            printf("NO: need %d contiguous seats, only %d free\n", requested, available);
        }
    }
    else
    {
        if (available >= requested)
        {
            printf("YES: seats available in %s. Suggested seats: ", argv[1]);
            for (int i = 0, j = 0; i < size && j < requested; i++)
            {
                if (seats[i] == 0)
                {
                    printf("%d ", i + 1);
                    j++;
                }
            }
            printf("\n");
        }
        else
        {
            printf("NO: need %d seats, only %d free\n", requested, available);
        }
    }
    return 0;
}
