# Banking_System
This Repo will focus on making a banking system which will be divided into some modules

Please while pushing your code, create a new branch of your name until you are not sure that the module's are bug free and are integrating properly

main key features : 

1.Users :
	1. Creation
	2. Updation
	3. Deletion
	4. Password encryption
	5. Unique Id Creation
	6. A feature by which we can validate user id and password for login
	7. Type of user (Savings, Current) : will be necessary for interest rates and transaction fees

2. Deposit Money : 
	1. Find out How much money to Deposite
	2. Make records of it in a file unique for each user
		a) THe log should contain, date, time, amount deposits into the account and updated balance.
		b) Update the current balance of the account of the account

3. Withdraw Money : 
	1. Which way are we suppose to withdraw
		a) Want it in cash or want to transfer it to a different account of the same system.
		b) Validate the account if we are updating its values
	2. Record the Update in the same file we used for deposit but these logs should be separate for different users.
		(The files format should be the same as mentioned above)

4. Balance Inquiry : 
	1. We should be able to see our bank balance and 
	2. should also have the ability to see the transaction details for the given amount of time (this thing should only be shown if the time transactions hit more than 10 for that account)

5. Account details : 
	1. Should be able to see all the information about that account like address, unique id, (not password), Name, age.
	2. And have the ability to redirect to the Balance inquiry request.

6. For admins : 
	1. We should have the ability to see all the users with only there balance visible in a line.

7. Transactions : 
	1. The user should have the ability to look towards its transactions.
	2. The bank should have a basic idea about how much money it is storing each day of the users in total.
