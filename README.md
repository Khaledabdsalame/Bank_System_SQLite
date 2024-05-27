# Bank_System_SQLite
# Overview
This C++ program implements a simple yet robust banking system that uses SQLite for data storage. The system allows users to register, log in, deposit funds, and transfer funds securely. Key features include input validation, secure user authentication, and database operations to maintain data integrity.

Key Functionalities
# Database Connection:

Setup: The program connects to a SQLite database named database.db using the SQLite C++ API.
Data Retrieval: It retrieves existing user information from the users table upon startup to ensure real-time data management.
# Input Validation:

Email Validation: Ensures the provided email address follows a valid format.
Password Validation: Checks that the password meets certain criteria (e.g., length, inclusion of letters and numbers).
Card Details Validation: Validates card number format, CVV length, and expiration date format.
Unique Check: Ensures that the email and card number are unique and not already registered in the database.
# User Registration:

Input Collection: Collects details such as username, password, email, card number, CVV, and expiration date.
Validation and Duplication Check: Validates the input details and checks for existing records with the same email or card number.
Database Insertion: Inserts validated user details into the users and Cards tables in the database.
# User Login:

Authentication: Prompts users for their email and password, then verifies these credentials against the records in the users table.
Session Management: Upon successful login, the user is granted access to further functionalities like depositing and transferring funds.
# Deposit Funds:

Self and External Deposits: Users can deposit funds using their registered card or any other valid card.
Database Update: The user's balance is updated in the database. For external card deposits, additional validation of card details is performed.
# Transfer Funds:

Recipient Verification: Users can transfer funds to another registered user by providing the recipient's email.
Fund Transfer: The system validates the recipient's existence and updates the balances of both the sender and the recipient in the database accordingly.
Code Structure
# Main Function:

Initializes the SQLite database connection.
Calls the menu function to start the user interaction loop.
# Helper Functions:

database(): Connects to the SQLite database and retrieves user information.
valid_email(std::string): Validates the email format.
valid_password(std::string): Checks the password criteria.
valid_number(std::string): Ensures the input is numeric.
valid_date(std::string): Validates the date format for card expiration.
register_user(): Handles user registration, including input validation and database insertion.
login(): Authenticates the user by checking the provided credentials against the database.
menu(): Displays the main menu and directs users to various functions based on their choices.
deposit(): Manages the deposit process, including updating the user's balance.
transfer(): Handles the transfer of funds between users.
User Interaction Flow
Start: User is prompted to either log in or register.
Registration: If chosen, the user is guided through the registration process, including input validation and database checks.
Login: Authenticated users can access the main menu.
Main Menu:
Deposit Funds: User can deposit funds using their registered card or another valid card.
Transfer Funds: User can transfer funds to another registered user.
Exit: User can exit the application, ending the session.
# Summary
The program provides a comprehensive and secure banking system with essential functionalities for user management and financial transactions. It leverages SQLite for persistent storage and ensures data integrity through rigorous input validation and secure authentication mechanisms. The modular design and clear separation of concerns make it a reliable and extendable solution for basic banking operations.






