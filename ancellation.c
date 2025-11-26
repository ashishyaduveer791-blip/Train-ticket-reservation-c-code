#include <stdio.h>
#include <string.h>
#define MAX_TICKETS 10
int main()
{
    int booked[MAX_TICKETS] = {0}; // 0 = free, 1 = booked
    char names[MAX_TICKETS][50] = {""};
    int choice;
    while (1)
    {
        printf("\n=== Ticket Booking System ===\n");
        printf("1. Book Ticket\n2. Cancel Ticket\n3. View Tickets\n0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        if (choice == 1)
        {
            int t;
            printf("Tickets status:\n");
            for (int i = 0; i < MAX_TICKETS; i++)
                printf("Ticket %d: %s\n", i + 1, booked[i] ? "Booked" : "Available");
            printf("Enter ticket number to book: ");
            scanf("%d", &t);
            if (t < 1 || t > MAX_TICKETS || booked[t - 1])
            {
                printf("Invalid ticket or already booked.\n");
            }
            else
            {
                printf("Enter your name: ");
                scanf("%s", names[t - 1]); // simple input
                booked[t - 1] = 1;
                printf("Ticket %d booked for %s!\n", t, names[t - 1]);
            }
        }
        else if (choice == 2)
        {
            int t;
            printf("Tickets status:\n");
            for (int i = 0; i < MAX_TICKETS; i++)
                printf("Ticket %d: %s\n", i + 1, booked[i] ? "Booked" : "Available");
            printf("Enter ticket number to cancel: ");
            scanf("%d", &t);
            if (t < 1 || t > MAX_TICKETS || !booked[t - 1])
            {
                printf("Invalid ticket or not booked.\n");
            }
            else
            {
                booked[t - 1] = 0;
                names[t - 1][0] = '\0';
                printf("Ticket %d has been cancelled.\n", t);
            }
        }
        else if (choice == 3)
        {
            printf("Tickets status:\n");
            for (int i = 0; i < MAX_TICKETS; i++)
                printf("Ticket %d: %s\n", i + 1, booked[i] ? "Booked" : "Available");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
