#include <stdio.h>
#include <string.h>

//structure for our database can be expanded
struct usrlist
{
	char usrnm[30];
	unsigned long hashed;
};

int userlen;

// the hashing function
unsigned long
    hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

struct usrlist u[100];

int global = 0;

int main(void)
{
	struct usrlist u[100];
	
	strcpy(u[0].usrnm, "Sanskar123");
	u[0].hashed = hash("Sanskar123");

	strcpy(u[1].usrnm, "Atharva123");
	u[1].hashed = hash("Atharva123");

	strcpy(u[2].usrnm, "Kunal123");
	u[2].hashed = hash("Kunal123");

	strcpy(u[3].usrnm, "Yash123");
	u[3].hashed = hash("Yash123");

	userlen = 3;

	for (int i = 0; i < 4; i++)
	{
		printf("%s\n%lu\n", u[i].usrnm, u[i].hashed);
	}
}

//username adding 

int addu()
{
	char temp[100];

	printf("Enter your username you want to add:\n");
	scanf("%s", u[userlen + 1].usrnm);

	userlen++;

	printf("Enter the new password for username: \n");
	scanf("%s", temp);
	

}