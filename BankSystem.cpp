#include<iostream>
#include<Windows.h>
#include"sqlite/sqlite3.h"
#include <regex> 
#include <list>
using namespace std;
sqlite3* db;
sqlite3_stmt* statment;
int resault;
void connection() {
	if (sqlite3_open("database.db", &db) == SQLITE_OK)
	{
		resault = sqlite3_prepare_v2(db, "SELECT * FROM users;", -1, &statment, NULL);
		sqlite3_step(statment);
		sqlite3_finalize(statment);

	}
	if (resault != SQLITE_OK) {
		cout << "Error :" << sqlite3_errmsg(db);
		exit(0);
	}
	else
	{   
		cout << "Connect...";
		Sleep(1000);
		system("cls");
		cout << "Successfully Connected To The System" << endl;

	}
}
bool _Checker(string To_check,int a) {
	string Num_Text="";
	for (int i =0;i<To_check.length();i++)
	{
		if (To_check[i]>='0'&&To_check[i] <= '9') {
			Num_Text = Num_Text + To_check[i];
		}
	}
	if (Num_Text.length() == a)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool isChar(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}


bool isDigit(const char c)
{
	return (c >= '0' && c <= '9');
}


bool is_valid(string email)
{
	
	if (!isChar(email[0])) {

		return 0;
	}

	int At = -1, Dot = -1;
	int countAt = 0, countDot = 0;
	for (int i = 0;
		i < email.length(); i++) {

		if (email[i] == '@') {
			countAt++;
			At = i;
		}

		else if (email[i] == '.') {
			countDot++;
			Dot = i;
		}
	}


	if (At == -1 || Dot == -1)
		return 0;

	if (At > Dot)
		return 0;
	
	if (countAt > 1 || countDot > 1) {
		return 0;
	}
	return !(Dot >= (email.length() - 1));
}
bool validatePassword(string password)
{

	regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@#$%^&+=])(?=\\S+$).{8,}");

	if (regex_match(password, pattern))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CheakingLogin(string Email, string Password) {
	int resualt = sqlite3_prepare_v2(db, "SELECT Email,Password FROM users", -1, &statment, NULL);
	bool cheak = false;
	if (resault != SQLITE_OK) {
		cout << sqlite3_errcode(db) << endl;
	}
	else
	{
		while (resault = sqlite3_step(statment) == SQLITE_ROW)
		{
			string temp1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 0)));
			list<string> Mails{ temp1 };
			string temp2 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 1)));
			list <string> Passwords{ temp2 };
			for (auto i = Mails.begin();i != Mails.end();++i) {
				for (auto j = Passwords.begin();j != Passwords.end();++j) {
					if ((*i == Email) && (*j == Password))
					{
						cheak = true;
						break;

					}
				}
				
			}
		}
	}
	return cheak;
}


bool checkingCard(string CardNUmber, string Expdate, string CVV) {

	int resualt = sqlite3_prepare_v2(db, "SELECT NumberCard,ExpDate,CVV FROM Cards", -1, &statment, NULL);
	bool cheak_1 = false;
	if (resault != SQLITE_OK) {
		cout << sqlite3_errcode(db) << endl;
	}
	else
	{
		while (resault = sqlite3_step(statment) == SQLITE_ROW)
		{
			string temp1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 0)));
			list<string> Numbers{ temp1 };
			string temp2 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 1)));
			list <string> ExpDates{ temp2 };
			string temp3= std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 2)));
			list <string> cvvs{ temp3 };
			for (string Number : Numbers) {	
				for (string expdate : ExpDates) {
					for (string ccv : cvvs) {
						if (Number==CardNUmber&&expdate==Expdate&&ccv==CVV)
						{
							cheak_1 = true;
							break;
						}
					}
				}
			}
		}
	}
	return cheak_1;
}
bool Itisrepeated(string Email) {

	int resualt = sqlite3_prepare_v2(db, "SELECT Email FROM users", -1, &statment, NULL);
	bool cheak_1 = true;
	if (resault != SQLITE_OK) {
		cout << sqlite3_errcode(db) << endl;
	}
	else
	{
		while (resault = sqlite3_step(statment) == SQLITE_ROW)
		{
			 string temp1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 0)));
			 list <string> Emails = { temp1 };
			 for (string mail : Emails) {
				 if (mail==Email)
				 {
					 cheak_1 = false;
					 break;
				 }
			 }
		}
	}
	return cheak_1;
}
bool itisrepeatedcard(string cardNumber) {
	int resualt = sqlite3_prepare_v2(db, "SELECT NumberCard FROM users", -1, &statment, NULL);
	bool cheak_1 = true;
	if (resault != SQLITE_OK) {
		cout << sqlite3_errcode(db) << endl;
	}
	else
	{
		while (resault = sqlite3_step(statment) == SQLITE_ROW)
		{
			string temp1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 0)));
			list <string> Cards = { temp1 };
			for (string card : Cards) {
				if (cardNumber == card)
				{
					cheak_1 = false;
					break;
				}
			}
		}
	}
	return cheak_1;
}

int main() {
	connection();
	string NumberCard_Info;
	string Name_Info;
	string FamilyName_Info;
	string UserName_Info;
	string UserName_Reg;
	string Password_Reg;
	string NumberCard;
	string UserName;
	string password;
	string Email;
	string Email_Reg;
	string ExpDate;
	string ccv_reg;
	int choise;
	string Joining;
	string Solde;
	string Joining_2;
	string Joining3;
	string Solde_Info;
	string Adress_info;
	string DateOfBirth;
	string passwordtocheack;
	string SoldeBank;
	sqlite3_open("database.db", &db);
start:
	cout << "\n*****************************************";
	cout << "\nSelect 1 To SignIn" ;
	cout << " \nSelcet 2 To LogIn";
	cout << "\n*****************************************"<<endl;

	cin >> choise;
	    switch (choise)
		{
		case 1:
			system("cls");
		 user:
			cout << "Enter Your UserName To Sing In" << endl;
			cin >> UserName_Reg;
			if (UserName_Reg.length() < 8) {
				system("cls");
				cout << "The username must contain at least 8 characters" << endl;
				goto user;
			}
			system("cls");
		  pass:
			cout << "Enter Your Password To Sing In" << endl;
			cin >> Password_Reg;
			if (Password_Reg.length() < 8) {
				system("cls");
				cout << "The Password must contain at least 8 characters" << endl;
				goto pass;
			}
			if (validatePassword(Password_Reg)==false)
			{
				system("cls");
				cout << "Your Password must contain at least (Capital letter,Small letter,Digits,Symbols)" << endl;
				goto pass;
			}
			system("cls");
		   mail:
			cout << "Enter Your Email" << endl;
			cin >> Email_Reg;
			if (is_valid(Email_Reg)==false)
			{
				system("cls");
				cout << "Please Enter a Valid Mail" << endl;
				goto mail;
			}
			if (Itisrepeated(Email_Reg)==false)
			{
				system("cls");
				cout << "This Email Has Been registered"<<endl;
				goto mail;
			}
			system("cls");
		  card:
			cout << "Enter Your Card Number (You must have a bank account with us)" << endl;
			cin >> NumberCard;
			if (_Checker(NumberCard,16)==false|| itisrepeatedcard(NumberCard)==false)
			{
				system("cls");
				cout << "Invalid Number Card" << endl;
				goto card;
			}
			system("cls");
		   exp:
			cout << "Enter The Exp Date (YY/MM)" << endl;
			cin >> ExpDate;
			if (ExpDate[2] != '/'||_Checker(ExpDate,4)==false)
			{
					system("cls");
					cout << "Invalide Exp Date" << endl;
					goto exp;
				
			}
		  system("cls");
		  ccv:
			cout << "Enter Your CVV Code " << endl;
			cin >> ccv_reg;
			if (_Checker(ccv_reg, 3) == false) {
				system("cls");
				cout << "Invalide CVV" << endl;
				goto ccv;
			}
			if (checkingCard(NumberCard,ExpDate,ccv_reg)==false)
			{
				system("cls");
				cout << "Invalid Number Card (You Must Have Account With Us !)" << endl;
				goto card;
			}
			else
			{
				system("cls");
				sqlite3_prepare_v2(db, "INSERT INTO users(User_name,Password,Email) VALUES(?,?,?);", -1, &statment, NULL);
				sqlite3_bind_text(statment, 1, UserName_Reg.c_str(), UserName_Reg.length(), SQLITE_TRANSIENT);
				sqlite3_bind_text(statment, 2, Password_Reg.c_str(), Password_Reg.length(), SQLITE_TRANSIENT);
				sqlite3_bind_text(statment, 3, Email_Reg.c_str(), Email_Reg.length(), SQLITE_TRANSIENT);
				sqlite3_step(statment);
				sqlite3_finalize(statment);
				Joining = "UPDATE users SET NumberCard='" + NumberCard + "',ExpDate='" + ExpDate + "'" + ",CVV='" + ccv_reg + "'" + " WHERE Email='" + Email_Reg + "';";
				sqlite3_prepare_v2(db, Joining.c_str(), -1, &statment, NULL);
				sqlite3_step(statment);
				sqlite3_finalize(statment);
				Solde = "UPDATE users SET Solde=(SELECT Solde FROM Cards WHERE NumberCard='" + NumberCard + "')" + " WHERE Email = '" + Email_Reg + "';";
				sqlite3_prepare_v2(db, Solde.c_str(), -1, &statment, NULL);
				sqlite3_step(statment);
				sqlite3_finalize(statment);
				Joining_2 = "UPDATE users SET Name=(SELECT Name FROM Cards WHERE NumberCard='" + NumberCard + "')" + " WHERE Email = '" + Email_Reg + "';";
				sqlite3_prepare_v2(db,Joining_2.c_str(), -1, &statment,NULL);
				sqlite3_step(statment);
				sqlite3_finalize(statment);
				Joining3 = "UPDATE users SET FamilyName=(SELECT FamilyName FROM Cards WHERE NumberCard='" + NumberCard + "'),Adresse=(SELECT Adresse FROM Cards WHERE NumberCard=?),DateOfBirth=(SELECT DateOfBirth FROM Cards WHERE NumberCard=?),BankSolde=(SELECT BankSolde FROM Cards WHERE NumberCard=?)" + "WHERE  Email = '" + Email_Reg + "';";
				sqlite3_prepare_v2(db, Joining3.c_str(), -1, &statment, NULL);
				sqlite3_bind_text(statment, 1, NumberCard.c_str(), NumberCard.length(), SQLITE_TRANSIENT);
				sqlite3_bind_text(statment, 2,NumberCard.c_str(), NumberCard.length(), SQLITE_TRANSIENT);
				sqlite3_bind_text(statment, 3, NumberCard.c_str(), NumberCard.length(), SQLITE_TRANSIENT);
				sqlite3_step(statment);
				sqlite3_finalize(statment);
				cout << "Thank For Your Regestration" << endl;
				goto start;
			}
			
		case 2:
			system("cls");
			cout << "Welcome To The Bank" << endl;
			cout << "Enter Your Email" << endl;
			cin >> Email;
			system("cls");
			cout << "Enter your Password" << endl;
			cin >> password;
			system("cls");
			system("cls");
			if (CheakingLogin(Email,password)==true) {
				cout << "LogIn ...." << endl;
				Sleep(3000);
				system("cls");
				goto Welcome;
			}
			else
			{   
				cout << "Invalid Email Or Password" << endl;
				Sleep(1000);
				goto start;
			}
			
		default:
			system("cls");
			cout << "Invalid Input" << endl;
			goto start;
		}
	Welcome:
		int Temp;
		int resault_1;
		int Temp1;
		string newEmail;
		int Temp2;
		int Temp3;
		int Amount;
		int Amount_2;
		int transferedAmount;
		string useremail;
		string newUsername;
		string Check_password;
		string CardNum_1;
		string cvv_1;
		string ExpDate_1;
		string Solde_info_1;
		string querylogin= "SELECT * FROM users WHERE Email='" + Email + "';";
		int resualt = sqlite3_prepare_v2(db,querylogin.c_str(), -1, &statment, NULL);
		bool cheak = false;
		if (resault != SQLITE_OK) {
			cout << sqlite3_errcode(db) << endl;
		}
		else
		{
			while (resault = sqlite3_step(statment) == SQLITE_ROW)
			{
				   NumberCard_Info = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 2)));
				   Name_Info = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 7)));
				   FamilyName_Info=  std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 8)));
				   UserName_Info = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 0)));
				   Solde_Info= std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 5)));
				   Adress_info= std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 9)));
				   DateOfBirth= std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 10)));
				   passwordtocheack=std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 1)));
				   SoldeBank= std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 11)));

			}
		}
		int Choise_1;
		int choise_2;
		int Choise_3;
		int choise4;
			cout << "Welcome "<< UserName_Info <<" To Bank" << endl;
			cout << "***************************************************" << endl;
			cout << "Enter 1 For Despoit" << endl;
			cout << "Enter 2 For transfer" << endl;
			cout << "Enter 3 To Show Your Information" << endl;
			cout << "Enter 4 To Singout"<<endl;
			cout << "*****************************************************" << endl;
			cin >> Choise_1;
			switch (Choise_1)
			{
			case 1:
				system("cls");
				cout << "Select 1 To Deposit From Your Card" << endl;
				cout << "Select 2 To Deposit From Another Card" << endl;
				cout << "Select 3 To return" << endl;
				cin >> choise4;
				switch (choise4)
				{
				case 1:
					system("cls");
				D:
					cout << "Enter The Amount" << endl;
					cin >> Amount;
					 Temp=stoi(Solde_Info);
					 Temp1 = stoi(SoldeBank);
					if (Temp<Amount)
					{
						system("cls");
						cout << "You Dont Have enough credit" << endl;
						goto D;
					}
					else
					{   
						system("cls");
						Temp = Temp - Amount;
						Temp1 = Temp1 + Amount;
						sqlite3_prepare_v2(db, "UPDATE users SET Solde=?,BankSolde=? WHERE Email=?;", -1, &statment, NULL);
						sqlite3_bind_text(statment, 1, to_string(Temp).c_str(), to_string(Temp).length(), SQLITE_TRANSIENT);
						sqlite3_bind_text(statment, 2, to_string(Temp1).c_str(), to_string(Temp1).length(), SQLITE_TRANSIENT);
						sqlite3_bind_text(statment, 3, Email.c_str(), Email.length(), SQLITE_TRANSIENT);
						sqlite3_step(statment);
						sqlite3_finalize(statment);
						cout << "The Amount has been deposit Sucsussfuly" << endl;
						goto Welcome;
						
					}
				case 2:
					system("cls");
				N1:
					cout << "Enter Card Number:" << endl;
					cin >> CardNum_1;
					if (_Checker(CardNum_1, 16)==false)
					{
						cout << "Invalid NumberCard" << endl;
						goto N1;
						system("cls");
					}
					system("cls");
				  N2:
					cout << "Enter The Exp Date (YY/MM)" << endl;
					cin >> ExpDate_1;
					if (ExpDate_1[2] != '/' || _Checker(ExpDate_1, 4) == false)
					{
						system("cls");
						cout << "Invalide Exp Date" << endl;
						goto N2;

					}
					system("cls");
				  N3:
					cout << "Enter Your CVV Code " << endl;
					cin >> cvv_1;
					if (_Checker(cvv_1, 3) == false) {
						system("cls");
						cout << "Invalide CVV" << endl;
						goto N3;
					}
					if (checkingCard(CardNum_1, ExpDate_1, cvv_1) == false)
					{
						system("cls");
						cout << "Invalid Number Card (You Must Have Account With Us !)" << endl;
						goto N1;
					}
					    system("cls");
						cout << "Enter The Amount: " << endl;
					t3:
						cin >> Amount_2;
						system("cls");
						    resault_1 = sqlite3_prepare_v2(db, "SELECT * FROM Cards WHERE NumberCard=?;", -1, &statment, NULL);
						sqlite3_bind_text(statment, 1, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
						if (resault_1 != SQLITE_OK) {
							cout << sqlite3_errcode(db) << endl;
						}

						while (resault_1 = sqlite3_step(statment) == SQLITE_ROW)
						{   
							Temp = stoi(std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 3))));
							if (Amount_2 > Temp) {
								cout << "You Dont Have enough Solde" << endl;
								goto t3;
								system("cls");
							}
							Solde_info_1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 3)));
							Temp2 = stoi(Solde_info_1);
							Temp3 = stoi(SoldeBank);
							Temp2 = Temp2 - Amount_2;
							Temp3 = Temp3 + Amount_2;
							sqlite3_prepare_v2(db, "UPDATE users SET BankSolde=? WHERE Email=?;", -1, &statment, NULL);
							sqlite3_bind_text(statment, 1, to_string(Temp3).c_str(), to_string(Temp3).length(), SQLITE_TRANSIENT);
							sqlite3_bind_text(statment, 2, Email.c_str(), Email.length(), SQLITE_TRANSIENT);
							sqlite3_step(statment);
							sqlite3_finalize(statment);
							sqlite3_prepare_v2(db, "UPDATE Cards SET Solde=? WHERE NumberCard=?;", -1, &statment, NULL);
							sqlite3_bind_text(statment, 1, to_string(Temp2).c_str(), to_string(Temp2).length(), SQLITE_TRANSIENT);
							sqlite3_bind_text(statment, 2, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
							sqlite3_step(statment);
							sqlite3_finalize(statment);
							sqlite3_prepare_v2(db, "UPDATE users SET Solde=(SELECT Solde FROM Cards WHERE NumberCard=?) WHERE NumberCard=?;", -1, &statment, NULL);
							sqlite3_bind_text(statment, 1, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
							sqlite3_bind_text(statment, 2,CardNum_1.c_str(),CardNum_1.length(), SQLITE_TRANSIENT);
							sqlite3_step(statment);
							sqlite3_finalize(statment);
							cout << "The Amount has been deposit Sucsussfuly" << endl;
							goto Welcome;


						}
						
				case 3:
					system("cls");
					goto Welcome;
				default:
					system("cls");
					goto D;
				}
			case 2:
				system("cls");
				cout << "Enter The Email of the user" << endl;
				cin >> useremail;
				if (Itisrepeated(useremail) == false&&useremail!=Email) {
					system("cls");
					cout << "Select 1 To Transfer From Your Card" << endl;
					cout << "Select 2 To Transfer From Your Bank Account" << endl;
					int c;
					cin >>c;
					switch (c)
					{
					    case 1:
						F1:
							system("cls");
							cout << "Enter Card Number:" << endl;
							cin >> CardNum_1;
							if (_Checker(CardNum_1, 16) == false)
							{
								cout << "Invalid NumberCard" << endl;
								goto N1;
								system("cls");
							}
							system("cls");
						F2:
							cout << "Enter The Exp Date (YY/MM)" << endl;
							cin >> ExpDate_1;
							if (ExpDate_1[2] != '/' || _Checker(ExpDate_1, 4) == false)
							{
								system("cls");
								cout << "Invalide Exp Date" << endl;
								goto N2;

							}
							system("cls");
						F3:
							cout << "Enter Your CVV Code " << endl;
							cin >> cvv_1;
							if (_Checker(cvv_1, 3) == false) {
								system("cls");
								cout << "Invalide CVV" << endl;
								goto N3;
							}
							if (checkingCard(CardNum_1, ExpDate_1, cvv_1) == false)
							{
								system("cls");
								cout << "Invalid Number Card (You Must Have Account With Us !)" << endl;
								goto N1;
							}
							system("cls");
						t:
							system("cls");
							cout << "Enter The Amount: " << endl;
							cin >> transferedAmount;
								system("cls");
								resault_1 = sqlite3_prepare_v2(db, "SELECT * FROM Cards WHERE NumberCard=?;", -1, &statment, NULL);
								sqlite3_bind_text(statment, 1, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
								if (resault_1 != SQLITE_OK) {
									cout << sqlite3_errcode(db) << endl;
								}

								while (resault_1 = sqlite3_step(statment) == SQLITE_ROW)
								{
									Solde_info_1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 3)));
									if (transferedAmount > stoi(Solde_info_1)) {
										cout << "You Dont Have enough Solde" << endl;
										goto t;
										system("cls");
									}
									
									Temp2 = stoi(Solde_info_1);
									Temp3 = stoi(SoldeBank);
									Temp2 = Temp2 - transferedAmount;
									Temp3 = Temp3 + transferedAmount;
									sqlite3_prepare_v2(db, "UPDATE users SET BankSolde=? WHERE Email=?;", -1, &statment, NULL);
									sqlite3_bind_text(statment, 1, to_string(Temp3).c_str(), to_string(Temp3).length(), SQLITE_TRANSIENT);
									sqlite3_bind_text(statment, 2, useremail.c_str(), useremail.length(), SQLITE_TRANSIENT);
									sqlite3_step(statment);
									sqlite3_finalize(statment);
									sqlite3_prepare_v2(db, "UPDATE Cards SET Solde=? WHERE NumberCard=?;", -1, &statment, NULL);
									sqlite3_bind_text(statment, 1, to_string(Temp2).c_str(), to_string(Temp2).length(), SQLITE_TRANSIENT);
									sqlite3_bind_text(statment, 2, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
									sqlite3_step(statment);
									sqlite3_finalize(statment);
									sqlite3_prepare_v2(db, "UPDATE users SET Solde=(SELECT Solde FROM Cards WHERE NumberCard=?) WHERE NumberCard=?;", -1, &statment, NULL);
									sqlite3_bind_text(statment, 1, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
									sqlite3_bind_text(statment, 2, CardNum_1.c_str(), CardNum_1.length(), SQLITE_TRANSIENT);
									sqlite3_step(statment);
									sqlite3_finalize(statment);
									cout << "The Amount has been deposit Sucsussfuly" << endl;
									goto Welcome;
								}
								
					    case 2:
						t1:
							system("cls");
							cout << "enter the amount to transfer it" << endl;
							cin >> transferedAmount;
							system("cls");
								resault_1 = sqlite3_prepare_v2(db, "SELECT * FROM users WHERE Email=?;", -1, &statment, NULL);
								sqlite3_bind_text(statment, 1, useremail.c_str(), useremail.length(), SQLITE_TRANSIENT);
								if (resault_1 != SQLITE_OK) {
									cout << sqlite3_errcode(db) << endl;
								}

								while (resault_1 = sqlite3_step(statment) == SQLITE_ROW)
								{
									Solde_info_1 = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statment, 11)));
									if (transferedAmount > stoi(SoldeBank)) {
										cout << "You Dont Have enough Solde" << endl;
										goto t1;
										system("cls");
									}
									else {
										Temp2 = stoi(Solde_info_1);
										Temp3 = stoi(SoldeBank);
										Temp2 = Temp2 + transferedAmount;
										Temp3 = Temp3 - transferedAmount;
										sqlite3_prepare_v2(db, "UPDATE users SET BankSolde=? WHERE Email=?;", -1, &statment, NULL);
										sqlite3_bind_text(statment, 1, to_string(Temp3).c_str(), to_string(Temp3).length(), SQLITE_TRANSIENT);
										sqlite3_bind_text(statment, 2, Email.c_str(), Email.length(), SQLITE_TRANSIENT);
										sqlite3_step(statment);
										sqlite3_finalize(statment);
										sqlite3_prepare_v2(db, "UPDATE users SET BankSolde=? WHERE Email=?;", -1, &statment, NULL);
										sqlite3_bind_text(statment, 2, useremail.c_str(), useremail.length(), SQLITE_TRANSIENT);
										sqlite3_bind_text(statment, 1, to_string(Temp2).c_str(), to_string(Temp2).length(), SQLITE_TRANSIENT);
										sqlite3_step(statment);
										sqlite3_finalize(statment);
										cout << "The Amount tensfered sucsufully" << endl;
										goto Welcome;
									}
								}
							

					default:
						break;
					}
					
				
				}
				else {
					system("cls");
					cout << "Invalid Mail" << endl;
					goto Welcome;
				}

				break;
			case 3:
			  info:
				system("cls");
				cout << "********************************************" << endl;
				cout << " User Name: "<< UserName_Info << endl;
				cout << " Number Card :" << NumberCard_Info << endl;
				cout << " Name :" << Name_Info<< endl;
				cout << " Family Name:" << FamilyName_Info<< endl;
				cout << " Solde In Your Credit Card:  " << Solde_Info <<"$" << endl;
				cout << " Solde In Your Bank Account : "<<SoldeBank<<"$" << endl;
				cout << " Adress : "<<Adress_info << endl;
				cout << " date of birth : " << DateOfBirth<< endl;
				cout << "*********************************************" << endl;
				cout << "Selcet 1 To Go on main menu" << endl;
				cout << "Select 2 To Edit Your Information" << endl;
				cin >> choise_2;
				switch (choise_2)
				{
				case 1:
					system("cls");
					goto Welcome;
				case 2:
					system("cls");
					cout << "Select 1 To Edit Your Username" << endl;
					cout << "Select 2 To Edit Your Email" << endl;
					cout << "If there is any problem with your bank account or Forgete the Password, send a report to the administrator by selecting 3" << endl;
					cin >> Choise_3;
					switch (Choise_3)
					{
					case 1:
						system("cls");
						cout << "Enter The New Username" << endl;
						cin >> newUsername;
						system("cls");
						cout << "Enter Your Password" << endl;
						cin >> Check_password;
						cout << "Select 3 To return" << endl;
						if (Check_password==passwordtocheack)
						{    
							system("cls");
							sqlite3_prepare_v2(db, "UPDATE users SET User_name=?;", -1, &statment, NULL);
							sqlite3_bind_text(statment, 1, newUsername.c_str(), newUsername.length(), SQLITE_TRANSIENT);
							sqlite3_step(statment);
							sqlite3_finalize(statment);
							cout << "Information Has Been Updated" << endl;
							goto Welcome;
						}
						else
						{   
							system("cls");
							cout << "Invalid Password" << endl;
							goto Welcome;
						}
					case 2:
						system("cls");
						cout << "Enter The New Email" << endl;
						cin >> newEmail;
						if (is_valid(newEmail) == false)
						{
							system("cls");
							cout << "Please Enter a Valid Mail" << endl;
							goto mail;
						}
						if (Itisrepeated(newEmail) == false)
						{
							system("cls");
							cout << "This Email Has Been registered" << endl;
							goto mail;
						}
						system("cls");
						cout << "Enter Your Password" << endl;
						cin >> Check_password;
						cout << "Select 3 To return" << endl;
						if (Check_password == passwordtocheack)
						{
							system("cls");
							sqlite3_prepare_v2(db, "UPDATE users SET Email=?;", -1, &statment, NULL);
							sqlite3_bind_text(statment, 1, newEmail.c_str(), newEmail.length(), SQLITE_TRANSIENT);
							sqlite3_step(statment);
							sqlite3_finalize(statment);
							cout << "Information Has Been Updated" << endl;
							goto Welcome;
						}
						else
						{
							system("cls");
							cout << "Invalid Password" << endl;
							goto Welcome;
						}
					case 3:
						goto info;
					default:
						break;
					}
					
				default:
					goto info;

				}
			case 4:
				system("cls");
				goto start;
			}
	}
