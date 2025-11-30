#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define DATA_FILE "bank_data.txt"

// --- HASH FUNCTION (djb2) ---
// This converts a string password into a unique number
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// Struct to hold user data
struct user {
    int id;
    char username[50];
    unsigned long password_hash; // Changed from char array to unsigned long
    char full_name[50];
    char address[100];
    long long phone;
    float balance;
};

struct user database[MAX_USERS];
int user_count = 0;

// --- UTILITY FUNCTIONS ---

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void strip_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// --- FILE HANDLING ---

void save_data() {
    FILE *file = fopen(DATA_FILE, "w");
    if (file != NULL) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%d\n", database[i].id);
            fprintf(file, "%s\n", database[i].username);
            // Save the HASH (number), not the password
            fprintf(file, "%lu\n", database[i].password_hash); 
            fprintf(file, "%s\n", database[i].full_name);
            fprintf(file, "%s\n", database[i].address);
            fprintf(file, "%lld\n", database[i].phone);
            fprintf(file, "%.2f\n", database[i].balance);
        }
        fclose(file);
    } else {
        printf("Error: Could not save data!\n");
    }
}

void load_data() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file != NULL) {
        user_count = 0;
        
        while (fscanf(file, "%d", &database[user_count].id) != EOF) {
            
            fscanf(file, "%s", database[user_count].username);
            // Read the HASH number
            fscanf(file, "%lu", &database[user_count].password_hash);
            
            fgetc(file); // Consume newline

            fgets(database[user_count].full_name, 50, file);
            strip_newline(database[user_count].full_name);

            fgets(database[user_count].address, 100, file);
            strip_newline(database[user_count].address);

            fscanf(file, "%lld", &database[user_count].phone);
            fscanf(file, "%f", &database[user_count].balance);
            
            user_count++;
        }
        fclose(file);
        printf("System: Loaded %d users.\n", user_count);
    }
}

// --- CORE FUNCTIONS ---

void user_dashboard(int user_index) {
    int choice;
    float amount;
    int logged_in = 1;

    while (logged_in) {
        #ifdef __unix__
            system("clear");
        #elif _WIN32
            system("cls");
        #endif

        printf("\n--- WELCOME %s ---\n", database[user_index].full_name);
        printf("Account ID: %d\n", database[user_index].id);
        printf("Current Balance: $%.2f\n", database[user_index].balance);
        printf("------------------------\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. View Profile Details\n");
        printf("4. Logout\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                if(amount > 0) {
                    database[user_index].balance += amount;
                    save_data();
                    printf("Deposit successful! New Balance: $%.2f\n", database[user_index].balance);
                } else {
                    printf("Invalid amount.\n");
                }
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                if(amount > 0 && amount <= database[user_index].balance) {
                    database[user_index].balance -= amount;
                    save_data();
                    printf("Withdrawal successful! New Balance: $%.2f\n", database[user_index].balance);
                } else {
                    printf("Insufficient funds or invalid amount.\n");
                }
                break;
            case 3:
                printf("\n--- Profile ---\n");
                printf("Name: %s\n", database[user_index].full_name);
                printf("Address: %s\n", database[user_index].address);
                printf("Phone: %lld\n", database[user_index].phone);
                break;
            case 4:
                logged_in = 0;
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
        if(logged_in) {
            printf("\nPress Enter to continue...");
            clear_input_buffer();
            getchar();
        }
    }
}

void bank_details() {
    float total_holdings = 0;
    printf("\n--- BANK ADMIN REPORT ---\n");
    printf("Total Registered Users: %d\n", user_count);
    
    for(int i = 0; i < user_count; i++) {
        total_holdings += database[i].balance;
    }
    
    printf("Total Bank Holdings: $%.2f\n", total_holdings);
    printf("-------------------------\n");
    printf("Press Enter to return to main menu...");
    clear_input_buffer();
    getchar();
}

void user_verification() {
    char input_user[50];
    char input_pass[50];
    unsigned long input_hash;
    int found = 0;

    if (user_count == 0) {
        printf("\nNo users registered yet.\n");
        printf("Press Enter to continue...");
        clear_input_buffer();
        getchar();
        return;
    }

    printf("\n--- USER LOGIN ---\n");
    printf("Username: ");
    scanf("%s", input_user);
    printf("Password: ");
    scanf("%s", input_pass);

    // Convert the input password to a hash immediately
    input_hash = hash((unsigned char*)input_pass);

    for (int i = 0; i < user_count; i++) {
        // Compare the username string AND the password hash number
        if (strcmp(database[i].username, input_user) == 0 && 
            database[i].password_hash == input_hash) {
            
            found = 1;
            printf("Login Successful!\n");
            user_dashboard(i); 
            break;
        }
    }

    if (!found) {
        printf("Invalid Username or Password.\n");
        printf("Press Enter to continue...");
        clear_input_buffer();
        getchar();
    }
}

void add_users() {
    char temp_pass[50]; // Temporary storage for password input

    if (user_count >= MAX_USERS) {
        printf("Bank storage full!\n");
        return;
    }

    struct user newUser;
    newUser.id = 1000 + user_count; 
    newUser.balance = 0.0; 

    printf("\n--- REGISTER NEW USER ---\n");
    printf("Enter Username (no spaces): ");
    scanf("%s", newUser.username);
    
    printf("Enter Password (no spaces): ");
    scanf("%s", temp_pass);
    
    // Hash the password immediately. We do NOT store the plain text 'temp_pass'
    newUser.password_hash = hash((unsigned char*)temp_pass);

    clear_input_buffer(); 
    
    printf("Enter Full Name: ");
    fgets(newUser.full_name, 50, stdin);
    strip_newline(newUser.full_name);
    
    printf("Enter Address: ");
    fgets(newUser.address, 100, stdin);
    strip_newline(newUser.address);

    printf("Enter Phone Number: ");
    scanf("%lld", &newUser.phone);

    database[user_count] = newUser;
    user_count++;
    
    save_data();

    printf("\nUser Registered Successfully! ID: %d\n", newUser.id);
    printf("Press Enter to continue...");
    clear_input_buffer();
    getchar();
}

int main() {
    int a;
    char state_bank = 'y';

    load_data();
    
    while (state_bank == 'y') {
        #ifdef __unix__
            system("clear");
        #elif _WIN32
            system("cls");
        #endif

        printf("\n=== BANKING SYSTEM MAIN MENU ===\n");
        printf("1. Banks Daily Uphold (Admin View)\n");
        printf("2. User Login\n");
        printf("3. Add Users (Register)\n");
        printf("4. Exit\n");
        printf("Enter a suitable option: ");
        
        if (scanf("%d", &a) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            getchar();
            continue;
        }

        switch (a) {
        case 1: 
            bank_details();
            break;
        case 2: 
            user_verification();
            break;
        case 3: 
            add_users();
            break;
        case 4: 
            printf("Exiting system. Goodbye!\n");
            state_bank = 'n';
            break;
        default:
            printf("Invalid Input. Press Enter to Continue...");
            clear_input_buffer();
            getchar();
        }
    }
    return 0;
}