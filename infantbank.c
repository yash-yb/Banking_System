#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear()
{
	system("clear");
}
 

int global = 0;

int password(void);

int main(void)
{	
	int balance = 5000, dep, with, input;
	char yn = 'n';
	
	password();

if(global == 1)	
{
	do
	{ 
	//bank main menu
		clear();
		printf("Welcome To San Bank's High Tech E-Banking System!!\nWhat do you want to do today?\n1.Check Balance(type 1)\n2.Withdraw(type 2)\n3.Deposit Cash(type 3)\n");
		scanf("%i", &input);
		
	// loop for valid input 
		while(input < 1 || input > 3 )
		{
			printf("\033[31mOops!! Invalid input. Try again.\033[0m\n");
			scanf("%i", &input);
		}		
	// main block for banking
		switch(input)
		{	
		//check balance
			case 1:
				clear();
				printf("||Check Balance Window||\nCurrent Balance = %i INR.\n", balance);
				printf("-------------------------------------------------------------------------------------\n");
				break;
		//withdraw
			case 2:
				clear();
				printf("||Withdraw Window||\nEnter the amount you want to withdraw.\n");
				scanf("%i", &with);
				while(with <= 0)
				{
					printf("The withdrawal amount is invalid. Try again\n");
					scanf("%i", &with);
				}
				if(with > balance)
				{
					printf("Sorry, Your Current Account Balance is insufficient.\n");
				}
				else
				{
					printf("Withdrawal Successfull!!\n");
					balance -= with;
					printf("Current Balance = %i INR\n", balance);
				}
				printf("-------------------------------------------------------------------------------------\n");
				break;
		//deposit
			case 3:
				clear();
				printf("||Deposit Window||\nEnter the amount you want to deposit.\n");
				scanf("%i", &dep);
				
				while(dep <= 0)
				{
					printf("The deposit amount is invalid. Try again\n");
					scanf("%i", &dep);
				}
				
				balance += dep;
				printf("Current Balance = %i INR\n", balance);
				printf("-------------------------------------------------------------------------------------\n");
				break;
		}
		printf("Do you want return to the main menu? (y for main menu/n to exit)\n");
		scanf(" %c", &yn);
		
		printf("-------------------------------------------------------------------------------------\n");
	}
	while ( yn == 'y');
	printf("Thank you for using San Bank's High Tech E-Banking System.Have a nice day!!\n");
}
}

// password code block
int password(void)
{
	char usrnmlist[3][30] =  {"a","b","snehal"}, iusrnm[1][30];
	char pswrd[3][30] = { "1234","2345","sne26san" } ,ipswrd[1][30];
	int try = 5,f = 0,p = 0;
	printf("Enter the username\n");
	scanf("%s", iusrnm[0]);
	
	//username section
	
	for(int i = 0; i < 3; i++)
	{
		if(strcmp(usrnmlist[i], iusrnm[0]) == 0)
		{
			f = 1;
			p = i;
			break;
		}
	}
	if(f == 0)
	{
		printf("\033[31mUsername not found.\033[0m\n");
		return 0;
	}
	
	//psswrd section
	clear();
	printf("Username Detected.\nEnter the password.\n");
	scanf("%s", ipswrd[0]);
	
	while( strcmp(pswrd[p], ipswrd[0]) != 0 && try > 0)
	{	
		printf("\033[31mWrong Password !! Please enter the password again.\033[0m\n");
	 	scanf("%s", ipswrd[0]);
	 	try--;
	 	clear();
	 	printf("You have %i tries remaining.\n", try);
	}
	if(try == 0)
	{
		clear();
		printf("\033[31mAuthentication failed. Contact the bank for more details. (CODE 0)\033[0m\n");
		global = 0;
	}
	else
	{
	clear();
	global = 1;
	}
	return 0;
}
	
