#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

#define MAX_SINGLE_ROOMS 20
#define MAX_DOUBLE_ROOMS 10
#define MAX_SUIT_ROOMS 5


struct Customer {
    char name[50];
    int age;
    long long int number;
    char mail[50];
    struct Address {
        char house_appartment[50];
        char street[20];
        char city[20];
        char state[50];
        int pincode[7];
    } address;
};

void displayCustomerInfo(struct Customer customer) {
    printf("\nName: %s\n", customer.name);
    printf("Age: %d\n", customer.age);
    printf("Phone Number: %lld\n", customer.number);
    printf("Email: %s\n", customer.mail);
    printf("Address: %s, %s, %s, %s, %s\n", customer.address.house_appartment, customer.address.street, customer.address.city, customer.address.state, customer.address.pincode);
}

typedef struct {
    int roomNumber;
    bool isReserved;
    char status[50];
} Room;

Room single_rooms[MAX_SINGLE_ROOMS];
Room double_rooms[MAX_DOUBLE_ROOMS];
Room suit_rooms[MAX_SUIT_ROOMS];

void initializeRooms() {
    for (int i = 0; i < MAX_SINGLE_ROOMS; i++) {
        single_rooms[i].roomNumber = i + 1;
        single_rooms[i].isReserved = false;
        strcpy(single_rooms[i].status, "Room is Available!");
    }
    for (int i = 0; i < MAX_DOUBLE_ROOMS; i++) {
        double_rooms[i].roomNumber = i + 1;
        double_rooms[i].isReserved = false;
        strcpy(double_rooms[i].status, "Room is Available!");
    }
    for (int i = 0; i < MAX_SUIT_ROOMS; i++) {
        suit_rooms[i].roomNumber = i + 1;
        suit_rooms[i].isReserved = false;
        strcpy(suit_rooms[i].status, "Room is Available!");
    }
}

struct about_room{
    int type;
    int roomNumber;
    int days;
}about_room;

void roomname(int type) {
    if (type == 1) {
        printf("Single Room");
    }
    else if (type == 2) {
        printf("Double Room");
    }
    else if (type == 3) {
        printf("Suit Room");
    }
    else {
        printf("Invalid room type!\n");
    }
}

void displayRooms() {
    printf("Available Rooms:\n\n");
    printf("Single Rooms:\n");
    for (int i = 0; i < MAX_SINGLE_ROOMS; i++) {
        if (!single_rooms[i].isReserved) {
            printf("Room %d\t", single_rooms[i].roomNumber);
        }
    }
    printf("\n\nDouble Rooms:\n");
    for (int i = 0; i < MAX_DOUBLE_ROOMS; i++) {
        if (!double_rooms[i].isReserved) {
            printf("Room %d\t", double_rooms[i].roomNumber);
        }
    }
    printf("\n\nSuit Rooms:\n");
    for (int i = 0; i < MAX_SUIT_ROOMS; i++) {
        if (!suit_rooms[i].isReserved) {
            printf("Room %d\t", suit_rooms[i].roomNumber);
        }
    }
    printf("\n");
}

bool myRoom(struct about_room *about_room, int MAX, Room *rooms_type) {
    if (about_room->roomNumber < 1 || about_room->roomNumber > MAX) {
        printf("Invalid room number!\n");
        return false;
    }

    else if (rooms_type[about_room->roomNumber - 1].isReserved) {
        printf("Room %d is already reserved!\n", about_room->roomNumber);
        return false;
    }

    else {
        printf("For how many days do you want to reserve the room? ");
        scanf("%d", &about_room->days);
        if (about_room->days < 1)
        {
            printf("Invalid number of days!\n");
            return false;
        }
        else if (about_room->days > 10)
        {
            printf("You can reserve a room for a maximum of 10 days!\n");
            return false;
        }
        else
        {
            rooms_type[about_room->roomNumber - 1].isReserved = true;
            printf("Room %d reserved successfully!\n", about_room->roomNumber);
            char status_name[50];
            sprintf(status_name, "Reserved by Customer for %d days!", about_room->days);
            strcpy(rooms_type[about_room->roomNumber - 1].status, status_name);
            return true;
        }
    }
}

bool reserveRoom(struct about_room *about_room) {
    if (about_room->type == 1) {
        return myRoom(about_room, MAX_SINGLE_ROOMS, single_rooms);
    }
    else if (about_room->type == 2) {
        return myRoom(about_room, MAX_DOUBLE_ROOMS, double_rooms);
    }
    else if (about_room->type == 3) {
        return myRoom(about_room, MAX_SUIT_ROOMS, suit_rooms);
    }
    else {
        printf("Invalid room type!\n");
        return false;
    }
}

bool cancelRoom(int roomNumber, int MAX) {
    if (roomNumber < 1 || roomNumber > MAX) {
        printf("Invalid room number!\n");
        return false;
    }

    else if (!single_rooms[roomNumber - 1].isReserved) {
        printf("Room %d is not reserved!\n", roomNumber);
        return false;
    }

    else {
        single_rooms[roomNumber - 1].isReserved = false;
        printf("Reservation for room %d cancelled successfully!\n", roomNumber);
        strcpy(single_rooms[roomNumber - 1].status, "Room is Available now!");
        return true;
    }
}

bool cancelReservation(int roomNumber) {
    if (roomNumber > 1 && roomNumber <= MAX_SINGLE_ROOMS) {
        return cancelRoom(roomNumber, MAX_SINGLE_ROOMS);
    }
    else if (roomNumber > MAX_SINGLE_ROOMS && roomNumber <= MAX_SINGLE_ROOMS + MAX_DOUBLE_ROOMS) {
        return cancelRoom(roomNumber, MAX_DOUBLE_ROOMS);
    }
    else if (roomNumber > MAX_SINGLE_ROOMS + MAX_DOUBLE_ROOMS && roomNumber <= MAX_SINGLE_ROOMS + MAX_DOUBLE_ROOMS + MAX_SUIT_ROOMS) {
        return cancelRoom(roomNumber, MAX_SUIT_ROOMS);
    }
    else {
        printf("Invalid room number!\n");
        return false;
    }
}

struct Bill{
    int cost_perday;
    float without_gst_cost;
    float gst_cost; 
}bill;

void gencost(struct about_room about_room, struct Bill *bill){
    if (about_room.type == 1) {
        bill->cost_perday = 1500;
    }
    else if (about_room.type == 2) {
        bill->cost_perday = 2500;
    }
    else if (about_room.type == 3) {
        bill->cost_perday = 5000;
    }
    else {
        printf("Invalid room type!\n");
    }
    bill->without_gst_cost = bill->cost_perday * about_room.days;
    bill->gst_cost = bill->cost_perday * about_room.days * 1.18;
}

void genBill(struct about_room about_room, struct Bill bill, struct Customer customer) {
    printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    printf("Customer Name      : %s\n", customer.name);
    printf("Customer Age       : %d\n", customer.age);
    printf("Customer Phone No  : %lld\n", customer.number);
    printf("Customer Email     : %s\n", customer.mail);
    printf("Customer Address   : %s, %s, %s, %s, %s\n", customer.address.house_appartment, customer.address.street, customer.address.city, customer.address.state, customer.address.pincode);
    printf("Room Type          : "); roomname(about_room.type); printf("\n");
    printf("No. of days stayed : %d\n", about_room.days);
    printf("Room cost per day  : %d\n", bill.cost_perday);
    printf("Cost (without gst) : %.f\n", bill.without_gst_cost);
    printf("Final Cost         : %.f\n", bill.gst_cost);
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
}

bool payment(struct Customer customer) {
    char pay[5];
    printf("Would you like to make the payment right now? (y/n): ");
    scanf("%s", pay);
    if (strcmp(pay, "y") == 0) {
        printf("\nHow you wanna pay ?\n1. Credit Card\n2. Debit Card\n3. UPI\n4. Net Banking\nEnter your choice: ");
        int p_choice;
        scanf("%d", &p_choice);
        switch (p_choice)
        {
        case 1:
            printf("Enter your Credit Card number: ");
            long long int cc_number;
            scanf("%lld", &cc_number);
            printf("Enter the CVV: ");
            int cvv;
            scanf("%d", &cvv);
            printf("Enter the expiry date (MM/YY): ");
            char expiry[6];
            scanf("%s", expiry);
            FILE *pi;
            pi = fopen("payment_info.csv", "a");
            fprintf(pi, "%s,Credit Card,%lld,%d,%s\n", customer.name,cc_number, cvv, expiry);
            fclose(pi);
            printf("Enter the OTP send at your phone number linked to your credit card\n");
            int otp;
            scanf("%d", &otp);
            if (otp == 1234) {
                return true;
            }
            else {
            printf("OTP Incorrect!\n");
            printf("Payment unsuccessful!\n");
            }
            break;
        case 2:
            printf("Enter your Debit Card number: ");
            long long int dc_number;
            scanf("%lld", &dc_number);
            printf("Enter the CVV: ");
            int cvv2;
            scanf("%d", &cvv2);
            printf("Enter the expiry date (MM/YY): ");
            char expiry2[6];
            scanf("%s", expiry2);
            FILE *pi2;
            pi2 = fopen("payment_info.csv", "a");
            fprintf(pi2, "%s,Debit Card,%lld,%d,%s\n", customer.name,dc_number, cvv2, expiry2);
            fclose(pi2);
            printf("Enter the OTP send at your phone number linked to your debit card\n");
            int otp2;
            scanf("%d", &otp2);
            if (otp2 == 1234) {
                return true;
            }
            else {
            printf("OTP Incorrect!\n");
            printf("Payment unsuccessful!\n");
            }
            break;
        case 3:
            printf("\nUPI ID: continentalhotel@upi\n");
            printf("Enter the OTP send at your phone number linked to your UPI ID\n");
            int otp3;
            scanf("%d", &otp3);
            if (otp3 == 1234) {
                return true;
            }
            else {
            printf("OTP Incorrect!\n");
            printf("Payment unsuccessful!\n");
            }
            break;
        case 4:
            printf("Enter your Net Banking ID: ");
            char netbank[50];
            scanf("%s", netbank);
            printf("Enter the password: ");
            char pass[50];
            scanf("%s", pass);
            printf("Enter the OTP send at your phone number linked to your Net Banking ID\n");
            int otp4;
            FILE *pi3;
            pi3 = fopen("payment_info.csv", "a");
            fprintf(pi3, "%s,Bank Details,%s,%s\n", customer.name,netbank, pass);
            fclose(pi3);
            scanf("%d", &otp4);
            if (otp4 == 1234) {
                return true;
            }
            else {
            printf("OTP Incorrect!\n");
            printf("Payment unsuccessful!\n");
            }
            break;
        default:
            break;
        }
    }
    else if (strcmp(pay, "n") == 0) {
        printf("Payment cancelled!\n");
        return false;
    }
    else {
        printf("Invalid choice! Payment cancelled!\n");
        return false;
    }
}

void take_feedback() {
    char yn2[5];
    printf("Would you like to provide feedback? (y/n): ");
    scanf("%s", yn2);
    if (strcmp(yn2, "y") == 0) {
        FILE *fp;
        fp = fopen("Feedback.txt", "a");
        char feedback[100];
        printf("Please provide your feedback in Single Line: ");
        scanf(" %[^\n]%*c", feedback);
        fprintf(fp, "%s\n\n", feedback);
        fclose(fp);
        printf("\n");
        printf("Thank you for your feedback!\n");
    }
    else if (strcmp(yn2, "n") == 0) {
        printf("\n");
        printf("Thank you for using our service!\n");
    }
    else {
        printf("\n");
        printf("Invalid choice! Thank you for using our service!\n");
    }
}

void displayRooms_withStatus() {
    printf("\nSingle Rooms:\n");
    for (int i = 0; i < MAX_SINGLE_ROOMS; i++) {
        if (single_rooms[i].isReserved) {
            printf("Room %d: Reserved\n", single_rooms[i].roomNumber);
            printf("Status: %s\n", single_rooms[i].status);
        }
        else {
            printf("Room %d: Available\n", single_rooms[i].roomNumber);
            printf("Status: %s\n", single_rooms[i].status);
        }
    }
    printf("\nDouble Rooms:\n");
    for (int i = 0; i < MAX_DOUBLE_ROOMS; i++) {
        if (double_rooms[i].isReserved) {
            printf("Room %d: Reserved\n", double_rooms[i].roomNumber);
            printf("Status: %s\n", double_rooms[i].status);
        }
        else {
            printf("Room %d: Available\n", double_rooms[i].roomNumber);
            printf("Status: %s\n", double_rooms[i].status);
        }
    }
    printf("\nSuit Rooms:\n");
    for (int i = 0; i < MAX_SUIT_ROOMS; i++) {
        if (suit_rooms[i].isReserved) {
            printf("Room %d: Reserved\n", suit_rooms[i].roomNumber);
            printf("Status: %s\n", suit_rooms[i].status);
        }
        else {
            printf("Room %d: Available\n", suit_rooms[i].roomNumber);
            printf("Status: %s\n", suit_rooms[i].status);
        }
    }

}

void changeRoomStatus(int max_room, Room *rooms_type) {
    printf("Enter the room number to change the status: ");
    int roomnum;
    char status[50];
    scanf("%d", &roomnum);
    if (roomnum > 1 && roomnum <= max_room) {
        rooms_type[roomnum - 1].isReserved = !rooms_type[roomnum - 1].isReserved;
        if (rooms_type[roomnum - 1].isReserved) {
            printf("Room %d status changed to reserved!\n", roomnum);
            scanf("%s", rooms_type[roomnum - 1].status);
        }
        else {
            printf("Room %d status changed to available!\n", roomnum);
            strcpy(rooms_type[roomnum - 1].status, "Room is Available now!");
        }
    }
    else {
        printf("Invalid room number!\n");
    }
}

void adminPortal() {
    char username[20];
    char password[20];

    printf("\nADMIN PORTAL\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if ((strcmp(username, "hardik") == 0 && strcmp(password, "continental7123") == 0) || (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)) {
        printf("\nWelcome, %s!\n", username);
        printf("\nRoom Status:\n");
        displayRooms_withStatus();
        printf("\nWould you Like to change the status of any room? (y/n): ");
        char yn[5];
        scanf("%s", yn);
        if (strcmp(yn, "y") == 0) {
            printf("Enter the room type to change the status: ");
            int roomtype;
            scanf("%d", &roomtype);
            if (roomtype < 1 || roomtype > 3) {
                printf("Invalid room type!\n");
            }
            else if (roomtype == 1) {
                changeRoomStatus(MAX_SINGLE_ROOMS, single_rooms);
            }
            else if (roomtype == 2) {
                changeRoomStatus(MAX_DOUBLE_ROOMS, double_rooms);
            }
            else if (roomtype == 3) {
                changeRoomStatus(MAX_SUIT_ROOMS, suit_rooms);
            }
            else {
                printf("Invalid room type!\n");
            }
        }
        else if (strcmp(yn, "n") == 0) {
            printf("Returning to Main Menu...\n");
        }
        else {
            printf("Invalid choice! Returning to Main Menu...\n");
        }
    }
    else {
        printf("Invalid credentials! Access denied.\n");
    }
}

int main() {
    int choice;
    struct Customer customer;
    struct about_room about_room;
    initializeRooms();
    char yn[5];
    int sucess_pay;

    SetConsoleOutputCP(CP_UTF8);
    printf("\n");
    printf("       \\        / |‾‾‾ |    |‾‾‾ |‾‾‾|   /\\  /\\   |‾‾‾\n");
    printf("        \\  /\\  /  |——  |    |    |   |  /  \\/  \\  |——\n");
    printf("         \\/  \\/   |___ |___ |___ |___| /        \\ |___\n");
    printf("\n");
    printf("               ‾‾|‾‾ |‾‾‾|   ‾‾|‾‾ |   | |‾‾‾\n");
    printf("                 |   |   |     |   |———| |——\n");
    printf("                 |   |___|     |   |   | |___\n");
    printf("\n");
    printf("|‾‾‾ |‾‾‾| |\\  | ‾‾|‾‾ ‾‾|‾‾ |\\  | |‾‾‾ |\\  | ‾‾|‾‾   /\\   |\n");
    printf("|    |   | | \\ |   |     |   | \\ | |——  | \\ |   |    /__\\  |\n");
    printf("|___ |___| |  \\|   |   __|__ |  \\| |___ |  \\|   |   /    \\ |___\n");
    printf("\n");
    printf("                 |   | |‾‾‾| ‾‾|‾‾ |‾‾‾ |\n");
    printf("                 |———| |   |   |   |——  |\n");
    printf("                 |   | |___|   |   |___ |___\n");
    printf("\n");

    while (true) {

        printf("\nMenu:\n1. Customer info\n2. Display available rooms\n3. Reserve a room\n4. Cancel Reservation\n5. Generate Bill\n6. Payment\n7. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                scanf(" %[^\n]%*c", customer.name);
                printf("Enter customer age: ");
                scanf("%d", &customer.age);
                printf("Enter customer phone number: ");
                scanf("%lld", &customer.number);
                printf("Enter customer email: ");
                scanf("%s", customer.mail);
                printf("Enter customer address as follows: ");
                printf("\n\tHouse/Apartment: ");
                scanf(" %[^\n]%*c", customer.address.house_appartment);
                printf("\tStreet/Colony: ");
                scanf(" %[^\n]%*c", customer.address.street);
                printf("\tCity: ");
                scanf("%s", customer.address.city);
                printf("\tState: ");
                scanf("%s", customer.address.state);
                printf("\tPincode: ");
                scanf("%s", &customer.address.pincode);
                
                displayCustomerInfo(customer);
                break;
            case 2:
                displayRooms();
                break;
            case 3:
                printf("Room types available: \n1. Single Room\n2. Double Room\n3. Suit Room\nEnter your choice: ");
                scanf("%d", &about_room.type);
                printf("Enter the room number to reserve: ");
                scanf("%d", &about_room.roomNumber);
                reserveRoom(&about_room);
                break;
            case 4:
                printf("Enter the room number to cancel reservation: ");
                scanf("%d", &about_room.roomNumber);
                cancelReservation(about_room.roomNumber);
                break;
            case 5:
                gencost(about_room, &bill);
                genBill(about_room, bill, customer);
                break;
            case 6:
                sucess_pay = payment(customer);
                if (sucess_pay) {printf("Payment successful!\n");}
                break;
            case 7:
                printf("Are you sure you want to exit the Menu? (y/n): ");
                scanf("%s", yn);
                if (strcmp(yn, "y") == 0) {
                    take_feedback();
                    return 0;
                }
                else if (strcmp(yn, "n") == 0) {
                    printf("Returning to Main Menu...\n");
                }
                else {
                    printf("Invalid choice! Returning to Main Menu...\n");
                }
                break;
            case 100:
                adminPortal();
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }
}