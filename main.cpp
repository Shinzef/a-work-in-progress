#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

struct userandpass {
	std::string username;
	std::string password;
	std::string isadmin;
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

		std::string username, password, isadmin;
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');
		std::getline(ss, isadmin, ',');

		userandpass user = { username, password, isadmin };
		users.push_back(user);

	}

	file.close();
}

void writeFile(userandpass user)
{
	std::ofstream file("F:\\randomstuff\\x64\\Debug\\data.txt", std::ios::app);

	
	file << user.username << "," << user.password << "," << user.isadmin << std::endl;
}

void forgetPassword()
{
	while (true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cin >> username;

		for ( auto& user : users )
		{
			if ( user.username == username)
			{
				std::cout << "Enter new password: ";
				std::string password;
				std::cin >> password;

				user.password = password;
				writeFile(user);
				std::cout << "Password changed" << std::endl;

				return;
			}
		}

		std::cout << "Username not found" << std::endl;

		while(true)
		{
			std::cout << "Do you want to try again? (y/n) ";
			char c;
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
	while(true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cin >> username;

		std::cout << "Enter password: ";
		std::string password;
		std::cin >> password;

		std::cout << username << " " << password << std::endl;
		std::cout << "Are you sure about this? (y/n) ";
		while (true)
		{
			std::string answer;
			std::cin >> answer;
			if (answer == "y")
			{
				userandpass user = { username, password, "0" };
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

session login()
{
	while (true)
	{
		std::cout << "Enter username: ";
		std::string username;
		std::cin >> username;

		std::cout << "Enter password: ";
		std::string password;
		std::cin >> password;

		for ( auto& user : users )
		{
			if ( user.username == username && user.password == password)
			{
				std::cout << "Login successful" << std::endl;
				if ( user.isadmin == "1")
				{
					std::cout << "You are an admin" << std::endl;
					std::cout << "Logged in as: " << user.username << std::endl;
					return {user.username, user.isadmin };
				}
				else
				{
					std::cout << "Logged in as: " << user.username << std::endl;
					return {user.username, user.isadmin };
				}
			}
		}
		std::cout << "Login failed" << std::endl;

		while(true)
		{
			std::cout << "Do you want to try again or forget your password? (f/l) ";
			char c;
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
	while (true)
	{
		std::cout << "Login or register? (l/r)" << std::endl;
		std::string loginOrRegister;
		std::cin >> loginOrRegister;

		if (loginOrRegister == "l")
		{
			session s = login();

			if ( !s.username.empty() && !s.isadmin.empty() )
			{
				return s;
			}
			
		}
		else if (loginOrRegister == "r")
		{
			createUser();
		}
		else
		{
			std::cout << "Invalid input" << std::endl;
			continue;
		}
	}
}

int main()
{
	openFile();
	
	session s = loginLoop();
}



