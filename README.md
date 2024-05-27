# Bank_System_SQLite
#Overview
This C++ program implements a simple banking system using SQLite for data storage. It provides functionalities for user registration, login, depositing funds, and transferring funds. The system ensures secure user interactions and data integrity through input validation and database operations.

key Functionalities
#Database Connection:

Establishes a connection to a SQLite database named database.db.
Retrieves user information from the users table.
#Input Validation:

Ensures user inputs are valid for email format, password strength, and card details.
#User Registration:

Collects user details (username, password, email, card number, CVV, card expiration date).
Validates inputs and checks for duplicate emails or card numbers.
Registers new users by inserting their details into the users and Cards tables.
#User Login:

Prompts users for their email and password.
Authenticates users against stored credentials in the users table.
#Deposit Funds:

Allows users to deposit money using their own card or another card.
Updates the user's balance in the database.
#Transfer Funds:

Enables users to transfer funds to another user by specifying the recipient's email.
Validates recipient details and updates both users' balances accordingly.
#Summary:
The program efficiently handles user registration, authentication, and financial transactions while ensuring data validity and security. It leverages SQLite for persistent storage and provides a user-friendly interface for managing banking operations.
