#include <stdio.h>
#include <string.h>

#define ROWS 4
#define SEATS_PER_ROW 5

typedef struct user {
    char username[20];
    char password[20];
} user;

typedef struct Bus {
    int busNumber;
    char name[50];
    char route[50];
    char destination[50];
    char departureTime[10];
} Bus;

int check_username(char *username) {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    user u;
    while (fread(&u, sizeof(user), 1, fp) == 1) {
        if (strcmp(u.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void register_user() {
    user u;
    printf("Enter a username: ");
    scanf("%s", u.username);
    while (check_username(u.username) == 1) {
        printf("This username already exists. Please try another one.\n");
        printf("Enter a username: ");
        scanf("%s", u.username);
    }
    printf("Enter a password: ");
    scanf("%s", u.password);
    FILE *fp = fopen("users.txt", "a");
    fwrite(&u, sizeof(user), 1, fp);
    fclose(fp);
    printf("Registration successful.\n");
}

int login_user() {
    char username[20];
    char password[20];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    user u;
    int flag = 0;
    while (fread(&u, sizeof(user), 1, fp) == 1) {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            flag = 1;
            break;
        }
    }
    fclose(fp);
    return flag;
}

void displayBusSchedule() {
    Bus buses[] = {
        {1, "Masafa", "Nairobi-Mombasa", "Nairobi", "08:00 AM"},
        {2, "Utalii", "Nairobi-Kisumu", "Kisumu", "09:30 AM"},
        {3, "Dethrone", "Nairobi-Kericho", "Nairobi", "10:45 AM"},
        {4, "Chaser", "Kisumu-Eldoret", "Eldoret", "12:15 PM"},
        {5, "Beatbox", "Kisumu-Mombasa", "City Center", "08:00 AM"},
        {6, "Shuttle", "Mombasa-Migori", "Mombasa", "09:30 AM"},
        {7, "Runner", "Nairobi-Migori", "Mombasa", "10:45 AM"},
        {8, "Burnout", "Nairobi-Nakuru", "Nairobi", "12:15 PM"}
    };

    int numBuses = sizeof(buses) / sizeof(buses[0]);

    printf("Bus Schedule:\n");
    printf("Here are The Available buses\n");
    printf("-------------------------------------------------------------\n");
    printf("Bus Number   Name       Route               Destination       Departure Time\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < numBuses; i++) {
        printf("%-12d %-10s %-18s %-18s %-6s\n", buses[i].busNumber, buses[i].name, buses[i].route, buses[i].destination, buses[i].departureTime);
    }

    printf("-------------------------------------------------------------\n");
    
}

void displaySeatArrangement(int seats[ROWS][SEATS_PER_ROW]) {
    printf("Bus Seat Arrangement:\n");
    printf("  ");
    for (int seatNum = 1; seatNum <= SEATS_PER_ROW; seatNum++) {
        printf("%d ", seatNum);
    }
    printf("\n");

    for (int row = 0; row < ROWS; row++) {
        printf("%d ", row + 1);
        for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) {
            if (seats[row][seatNum] == 0) {
                printf("O ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
}

// Function to get customer details
void getCustomerDetails(char *name, int *age, char *gender, char *destination, char *date, int *ticketNumber) {
    printf("Enter Customer Details:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Age: ");
    scanf("%d", age);
    printf("Gender: ");
    scanf("%s", gender);
    printf("Destination: ");
    scanf("%s", destination);
    printf("Date of Travel: ");
    scanf("%s", date);
    printf("Ticket Number: ");
    scanf("%d", ticketNumber);
}

// Function to print the bus ticket
void printBusTicket(char *name, int age, char *gender, char *destination, char *date, int ticketNumber) {
    printf("\n");
    printf("------------------------------\n");
    printf("|      Modern Bus Ticket      |\n");
    printf("------------------------------\n");
    printf("| Name: %20s  |\n", name);
    printf("| Age: %21d  |\n", age);
    printf("| Gender: %18s  |\n", gender);
    printf("| Destination: %13s  |\n", destination);
    printf("| Date of Travel: %10s  |\n", date);
    printf("| Ticket Number: %12d  |\n", ticketNumber);
    printf("------------------------------\n");
}
// Function to book a seat
int bookSeat(int seats[ROWS][SEATS_PER_ROW], int row, int seat, int *ticketNumber) {
    if (row < 1 || row > ROWS || seat < 1 || seat > SEATS_PER_ROW) {
        printf("Invalid seat selection. Please try again.\n");
        return 0;
    }

    if (seats[row - 1][seat - 1] == 1) {
        printf("Sorry, the seat is already booked. Please choose another seat.\n");
        return 0;
    }

    seats[row - 1][seat - 1] = 1;
    (*ticketNumber) = row * 100 + seat; // Calculate a simple ticket number
    printf("Seat %d-%d has been booked successfully.\n", row, seat);
    return 1;
}

int main() {
    int choice;
    int seats[ROWS][SEATS_PER_ROW] = {0};
    int ticketNumber = 0;
    do {
        printf("Welcome to Silva Coach Bus system.\n");
        printf("Please How do we help you:\n");
        printf("-----------------------------\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. View Available Seats\n");
        printf("4. Enter Booking Details\n");
        printf("5. Exit\n");
        printf("-----------------------------\n");
        printf("Select option >> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                if (login_user()) {
                    printf("Login successful.\n");
                    printf("Welcome  to Silva Coach System\n");
                    // Add further actions after login if needed.
                    displayBusSchedule();
                    int choice2;
					printf("Choose a Bus to Book: ");
					scanf("%d", &choice2);
					if(choice<8){
						displaySeatArrangement(seats);
						int row, seat;
		                printf("Enter row and seat number to book (e.g., 2 3): ");
		                scanf("%d %d", &row, &seat);
		                bookSeat(seats, row, seat, &ticketNumber);
						break;
					}else{
						printf("Sorry try again later!\n");
						break;
					}
                } else {
                    printf("Invalid username or password. Please try again.\n");
                }
                break;
            case 3:
            	displaySeatArrangement(seats);
            	printf("To Make a booking you have to login!\n");
            	break;
            case 4:
                if (ticketNumber == 0) {
                    printf("Please book a seat first to enter booking details.\n");
                } else {
                    char name[50], gender[10], destination[50], date[20];
                    int age;

                    getCustomerDetails(name, &age, gender, destination, date, &ticketNumber);
                    printBusTicket(name, age, gender, destination, date, ticketNumber);
                }
                break;
            case 5:
                printf("Thank you for Visiting Silva Coach Bus system. Welcome again!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (choice != 5);

}
