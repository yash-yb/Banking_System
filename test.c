#include <stdio.h>

int global = 0;

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
}