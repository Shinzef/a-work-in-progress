#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

struct userandpass {
	std::string username;
	std::string password;
	std::string isadmin;
	std::string balance;
};

struct session {
	std::string username;
	std::string isadmin;
};

std::vector<userandpass> users;

void openFile()
{
	std::ifstream file("F:\\randomstuff\\x64\\Debug\\data.txt", std::ios::in);

	// print if file is successfully opened
	if (file.is_open())
	{
		std::cout << "File is opened" << std::endl;
	}
	else
	{
		std::cout << "File is not opened" << std::endl;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);

		std::string username, password, isadmin, balance;
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');
		std::getline(ss, isadmin, ',');
		std::getline(ss, balance, ',');

		userandpass user = { username, password, isadmin, balance };
		users.push_back(user);

	}

	file.close();
}

void writeFile(userandpass user)
{
	std::ofstream file("F:\\randomstuff\\x64\\Debug\\data.txt", std::ios::app);


	file << user.username << "," << user.password << "," << user.isadmin << "," << user.balance << std::endl;
}

void changeFile(userandpass user)
{
	std::ifstream file("F:\\randomstuff\\x64\\Debug\\data.txt", std::ios::in);

	std::string line;
	std::vector<userandpass> temp;
	while (std::getline(file , line))
	{
		std::stringstream ss(line);

		std::string username, password, isadmin, balance;
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');
		std::getline(ss, isadmin, ',');
		std::getline(ss, balance, ',');

		userandpass user_temp = { username, password, isadmin, balance };
		temp.push_back(user_temp);
	}

	for ( auto& temp_user : temp)
	{
		if (temp_user.username == user.username)
		{
			temp_user.password = user.password;
			temp_user.isadmin = user.isadmin;
			temp_user.balance = user.balance;
		}
	}

	std::ofstream file_write("F:\\randomstuff\\x64\\Debug\\data.txt", std::ios::trunc);

	for (auto& temp_user : temp)
	{
		file_write << temp_user.username << "," << temp_user.password << "," << temp_user.isadmin << "," << temp_user.balance << std::endl;
	}

	file.close();
}

void forgetPassword()
{
	while (true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cout << "\n> ";
		std::cin >> username;

		for (auto& user : users)
		{
			if (user.username == username)
			{
				std::cout << "Enter new password: ";
				std::string password;
				std::cin >> password;

				user.password = password;
				changeFile(user);
				std::cout << "Password changed" << std::endl;

				return;
			}
		}

		std::cout << "Username not found" << std::endl;

		while (true)
		{
			std::cout << "Do you want to try again? (y/n) ";
			char c;
			std::cout << "> ";
			std::cin >> c;

			if (c == 'y')
			{
				break;
			}
			else if (c == 'n')
			{
				return;
			}
			else
			{
				std::cout << "Invalid input" << std::endl;
			}
		}
	}
}

void createUser()
{
	while (true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cout << "\n> ";
		std::cin >> username;

		std::cout << "Enter password: ";
		std::string password;
		std::cout << "\n> ";
		std::cin >> password;

		std::cout << username << " " << password << std::endl;
		std::cout << "Are you sure about this? (y/n) ";
		std::cout << "\n> ";
		while (true)
		{
			std::string answer;
			std::cin >> answer;
			if (answer == "y")
			{
				userandpass user = { username, password, "0", "0" };
				writeFile(user);
				users.push_back(user);
				std::cout << "User created" << std::endl;
				break;
			}
			else if (answer == "n")
			{
				std::cout << "User not created" << std::endl;
				break;
			}
			else
			{
				std::cout << "Please enter y or n" << std::endl;
			}
		}
		return;
	}
}

void createUserAdmin()
{
	while (true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cout << "\n> ";
		std::cin >> username;

		std::cout << "Enter password: ";
		std::string password;
		std::cout << "\n> ";
		std::cin >> password;

		std::cout << "Is user admin? (y/n) ";
		std::string isadmin;
		std::cout << "\n> ";
		std::cin >> isadmin;

		std::cout << "Enter initial balance: ";
		std::string balance;
		std::cout << "\n> ";
		std::cin >> balance;


		std::cout << "Summary: " << username << " " << password << " " << isadmin << " " << balance << std::endl;

		std::cout << "Are you sure about this? (y/n) ";
		std::cout << "\n> ";

		if (isadmin == "y")
		{
			isadmin = "1";
		}
		else
		{
			isadmin = "0";
		}

		while (true)
		{
			std::string answer;
			std::cin >> answer;
			if (answer == "y")
			{
				userandpass user = { username, password, isadmin, balance };
				writeFile(user);
				users.push_back(user);
				std::cout << "User created" << std::endl;
				break;
			}
			else if (answer == "n")
			{
				std::cout << "User not created" << std::endl;
				break;
			}
			else
			{
				std::cout << "Please enter y or n" << std::endl;
			}
		}
		return;
	}
}

void deleteAccount()
{
	
}

session login()
{
	while (true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cout << "\n> ";
		std::cin >> username;

		std::cout << "Enter password: ";
		std::string password;
		std::cout << "\n> ";
		std::cin >> password;

		for (auto& user : users)
		{
			if (user.username == username && user.password == password)
			{
				std::cout << "Login successful" << std::endl;
				if (user.isadmin == "1")
				{
					std::cout << "You are an admin" << std::endl;
					std::cout << "Logged in as: " << user.username << std::endl;
					return { user.username, user.isadmin };
				}
				else
				{
					std::cout << "Logged in as: " << user.username << std::endl;
					return { user.username, user.isadmin };
				}
			}
		}
		std::cout << "Login failed" << std::endl;

		while (true)
		{
			std::cout << "Do you want to try again or forget your password? (f/l) ";
			char c;
			std::cout << "> ";
			std::cin >> c;

			if (c == 'f')
			{
				forgetPassword();
				break;
			}
			else if (c == 'l')
			{
				break;
			}
			else
			{
				std::cout << "Invalid input" << std::endl;
			}
		}
	}
}

session loginLoop()
{
	std::cout << "What would you like to do?" << std::endl;
	while (true)
	{
		std::cout << "1. Create a new account\n"
			<< "2. Login to an existing account\n"
			<< "3. Exit" << std::endl;
		std::cout << "> ";

		std::string loginOrRegister;
		std::cin >> loginOrRegister;

		if (loginOrRegister == "2")
		{
			session s = login();

			if (!s.username.empty() && !s.isadmin.empty())
			{
				return s;
			}

		}
		else if (loginOrRegister == "1")
		{
			createUser();
		}
		else if (loginOrRegister == "3")
		{
			return { "", "" };
		}
		else
		{
			std::cout << "Invalid input" << std::endl;
		}
		
	}
}

void bankingLoop(session s)
{
	if (s.isadmin != "0")
	{
		std::cout << "Welcome to the Admin Panel" << std::endl;
		while (true)
		{
			std::cout << "What would you like to do?" << std::endl;
			std::cout << "1. Create a new account\n"
				<< "2. Delete an existing account\n"
				<< "3. Change a user's password\n"
				<< "4. Add money to an account\n"
				<< "5. Remove money from an account\n"
				<< "6. List all accounts\n"
				<< "7. Exit" << std::endl;
			std::cout << "> ";
			int choiceAdmin;
			std::cin >> choiceAdmin;

			switch (choiceAdmin)
			{
				case 1:
				{
					createUserAdmin();
					break;
				}
				case 2:
				{
					
				}
			}
		}

	}
	else
	{
		std::cout << "Welcome to the Banking Panel" << std::endl;
		while ( true )
		{
			std::cout << "What would you like to do?" << std::endl;
			std::cout << "1. Deposit\n"
				<< "2. Withdraw\n"
				<< "3. Transfer\n"
				<< "4. Check balance\n"
				<< "5. Logout" << std::endl;
			std::cout << "> ";
			int choice;
			std::cin >> choice;

			switch ( choice )
			{
				case 1:
				{
					std::cout << "Enter amount to deposit: ";
					std::string amount;
					std::cin >> amount;

					for (auto& user : users)
					{
						if (user.username == s.username)
						{
							user.balance = std::to_string(std::stoi(user.balance) + std::stoi(amount));
							std::cout << "Deposited $" << amount << " to " << user.username << std::endl;
							changeFile(user);
							break;
						}
					}
					
					break;
				}
				case 2:
				{
					std::cout << "Enter amount to withdraw: ";
					std::string amount;
					std::cin >> amount;

					for (auto& user : users)
					{
						if (user.username == s.username)
						{
							user.balance = std::to_string(std::stoi(user.balance) - std::stoi(amount));
							std::cout << "Deposited $" << amount << " to " << user.username << std::endl;
							changeFile(user);
							break;
						}
					}


					break;
				}
				case 3:
				{
					std::cout << "Enter amount: ";
					std::string amount;
					std::cin >> amount;

					std::cout << "Enter receiver username: ";
					std::string receiver;
					std::cin >> receiver;


					for ( auto& user : users )
					{
						if ( user.username == s.username )
						{
							user.balance = std::to_string( std::stoi( user.balance ) - std::stoi( amount ) );
							changeFile( user );
						}
						else if ( user.username == receiver )
						{
							user.balance = std::to_string( std::stoi( user.balance ) + std::stoi( amount ) );
							changeFile( user );
						}

					}
					std::cout << "Transferred $" << amount << " to " << receiver << std::endl;
					break;
				}
				case 4:
				{
					for (auto& user : users)
					{
						if (user.username == s.username)
						{
							std::cout << "Balance: $" << user.balance << std::endl;
						}
					}
				}
				case 5:
				{
					return;
				}
				default:
				{
					std::cout << "Invalid input" << std::endl;
				}
			}
		}
	}
}

int main()
{
	openFile();
	std::cout << "Welcome to the banking system!" << std::endl;
	session s = loginLoop();
	bankingLoop(s);


	return 0;
}
	
