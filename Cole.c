// By Mohd Mehandi = 612415106
// And Niosh Mate = 612415101
// Student of COEP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_COAL_TYPES 6


// Structures
typedef struct
{
    char type[20];
    int quantity;
} Coal;

typedef struct Truck
{
    int id;
    struct Truck *next;
} Truck;



// Global Variables
Coal coalYard[MAX_COAL_TYPES]; // Array of Coal structures (different types of coal)
int coalCount = 0;

Truck *front = NULL, *rear = NULL; // Queue ke start aur end (waiting trucks ke liye)
Truck *parkingHead = NULL;         // Parking area ka Linked List ka head.



// Function Declarations
void addCoalType();
void addOrSubtractCoal();
void viewYard();
void enqueueTruck();
void parkTruckFromQueue();
void removeTruckByID();
void displayQueue();
void displayParking();
int countTrucks(Truck *head);



// Functions

// Function 1: Add New Coal Type
void addCoalType()
{
    if (coalCount >= MAX_COAL_TYPES)
    {
        printf("\nCoal Yard Full! Can't add more types.\n");
        return;
    }
    printf("\nEnter Coal Type Name: ");
    scanf("%s", coalYard[coalCount].type);
    printf("Enter Quantity (tons): ");
    scanf("%d", &coalYard[coalCount].quantity);
    coalCount++;
    printf("Coal Type Added Successfully!\n");
}



// Function 2: Add or Subtract Quantity
void addOrSubtractCoal()
{
    char type[20];
    int qty, choice;
    printf("\nEnter Coal Type: ");
    scanf("%s", type);
    for (int i = 0; i < coalCount; i++)
    {
        if (strcmp(coalYard[i].type, type) == 0)
        {
            printf("1. Add Quantity\n2. Subtract Quantity\nEnter Choice: ");
            scanf("%d", &choice);
            printf("Enter Quantity: ");
            scanf("%d", &qty);

            if (choice == 1)
                coalYard[i].quantity += qty;
            else if (choice == 2)
            {
                if (coalYard[i].quantity >= qty)
                    coalYard[i].quantity -= qty;
                else
                {
                    printf("Not enough coal available!\n");
                    return;
                }
            }
            printf("Updated Quantity: %d tons\n", coalYard[i].quantity);
            return;
        }
    }
    printf("Coal Type Not Found!\n");
}



// Function 3: View Yard Status
void viewYard()
{
    printf("\n===== COAL YARD STATUS =====\n");

    if (coalCount == 0)
        printf("No coal types added yet.\n");
    else
    {
        for (int i = 0; i < coalCount; i++)
            printf("%d. %s - %d tons\n", i + 1, coalYard[i].type, coalYard[i].quantity);
    }

    printf("\nTrucks in Parking:\n");
    if (parkingHead == NULL)
        printf("   No Trucks Parked.\n");
    else
        displayParking();

    printf("\nTrucks in Queue:\n");
    displayQueue();

    printf("\nTotal Trucks in Parking: %d", countTrucks(parkingHead));
    printf("\nTotal Trucks in Queue: %d", countTrucks(front));
    printf("\nTotal Trucks in Yard: %d\n", countTrucks(parkingHead) + countTrucks(front));
}



// Function 4: Add Truck to Queue
void enqueueTruck()
{
    Truck *newTruck = (Truck *)malloc(sizeof(Truck));
    printf("\nEnter Truck ID: ");
    scanf("%d", &newTruck->id);
    newTruck->next = NULL;

    if (rear == NULL)
        front = rear = newTruck;
    else
    {
        rear->next = newTruck;
        rear = newTruck;
    }
    printf("Truck %d added to Queue!\n", newTruck->id);
}



// Function 5: Move Truck from Queue to Parking

void parkTruckFromQueue()
{
    if (front == NULL)
    {
        printf("\nNo Trucks in Queue to Park!\n");
        return;
    }
    Truck *temp = front;
    front = front->next;
    if (front == NULL)
        rear = NULL;

    temp->next = parkingHead;
    parkingHead = temp;
    printf("Truck %d moved to Parking from Queue.\n", temp->id);
}



// Function 6: Remove Truck from Parking by ID
void removeTruckByID()
{
    if (parkingHead == NULL)
    {
        printf("\nNo Trucks in Parking!\n");
        return;
    }

    int id;
    printf("\nEnter Truck ID to Remove from Parking: ");
    scanf("%d", &id);

    Truck *temp = parkingHead, *prev = NULL;

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Truck ID %d not found in Parking!\n", id);
        return;
    }

    if (prev == NULL)
        parkingHead = temp->next;
    else
        prev->next = temp->next;

    printf("Truck %d removed from Parking.\n", id);
    free(temp);
}



// Function 7: Display Queue
void displayQueue()
{
    Truck *temp = front;
    if (!temp)
    {
        printf("   None\n");
        return;
    }
    while (temp)
    {
        printf("   Truck ID: %d\n", temp->id);
        temp = temp->next;
    }
}



// Function 8: Display Parking
void displayParking()
{
    Truck *temp = parkingHead;
    if (!temp)
    {
        printf("   No Trucks Parked.\n");
        return;
    }
    while (temp)
    {
        printf("   Truck ID: %d\n", temp->id);
        temp = temp->next;
    }
}



// Function 9: Count Trucks
int countTrucks(Truck *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}



// Main Function
int main()
{
    int choice;
    printf("\n===== COAL YARD MANAGEMENT SYSTEM =====\n");

    while (1)
    {
        printf("\n---------------------------\n");
        printf("1. Add New Coal Type\n");
        printf("2. Add/Subtract Coal Quantity\n");
        printf("3. View Yard Status\n");
        printf("4. Add Truck to Yard\n");
        printf("5. Move Truck from Yard to Parking by ID\n");
        printf("6. Remove Truck from Parking by ID\n");
        printf("7. View Trucks in Parking\n");
        printf("8. Exit\n");
        printf("---------------------------\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addCoalType();
            break;
        case 2:
            addOrSubtractCoal();
            break;
        case 3:
            viewYard();
            break;
        case 4:
            enqueueTruck();
            break;
        case 5:
            parkTruckFromQueue();
            break;
        case 6:
            removeTruckByID();
            break;
        case 7:
            displayParking();
            break;
        case 8:
            printf("Exiting Program...\n");
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}