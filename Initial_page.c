#include <stdio.h>
#include <stdlib.h>
struct user {
    char* user;
    char* pass;
};
void bank_details()
{
    //this will have the code to print the history of how much bank holded and holds rightnow
}
void user_verification()
{
    //this will ask the user for his username and password
    //this will call a function onyl after varification which will result in many options like the initial page for further tasks.
}
void add_users()
{
    //this will ask for user's actual name, password, address, phone no. , email and all the basic details.
    //and also will generate a unique id for the user which will be displayed to the user for his later on login.
    //this will call some different fucntions to do the all the process
}
int main() {
    int a;
    char b;
    char state_bank = 'y';
    while (state_bank == 'y') {
#ifdef __unix__
        system("clear");
#elif _WIN32
        system("cls");
#endif
        // At the very first page our system will ask if we want users details
        // or banks details
        printf("1. Banks Daily Uphold \n");
        printf("2. User Details \n");
        printf("3. Add Users \n");
        printf("4. Exit \n");
        printf("Enter a suitable option : ");
        scanf("%d", &a);

        switch (a) {
        case 1: bank_details();
            break;
        case 2: user_verification();
            break;
        case 3: add_users();
            break;
        case 4: add_users();
            state_bank = 'n';
            break;
        default:
            printf("Invalid Input : please try Again(Enter to Continue...)");
            scanf("%c",&b);
        }
    }
    return 0;
}