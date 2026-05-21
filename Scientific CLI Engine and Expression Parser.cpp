#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class calculator
{
private:
	map <string, int> Variables;
	//
	map <char, short>precedence = { {'*',4},{'/',4} ,{'+',2} ,{ '-' ,2 } };
	deque<string> Output;
	stack<char> Operations;
	//
public:
	calculator()
	{
		//for later
	}
	string expression;
	double Result = 0;

	//Screens
	void MainScreen()
	{
		system("cls");
		cout << R"(    
                                      ==================================================
                                                    SCIENTIFIC CLI ENGINE   
                                      ==================================================
Commands:

  help: Show help menu | history: Show calculation history | clear: Clear screen | exit: Exit program
========================================================================================================================
)";


	}

};


int main()
{
	calculator c;
	c.MainScreen();
}

