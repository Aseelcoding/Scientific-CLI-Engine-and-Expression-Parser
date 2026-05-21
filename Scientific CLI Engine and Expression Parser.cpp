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
	vector<string> Tokens;
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
	void HelpScreen()
	{
		system("cls");
		cout << R"(

==================================================
                    HELP MENU
==================================================

[ BASIC OPERATIONS ]
  +    Addition
  -    Subtraction
  *    Multiplication
  /    Division

--------------------------------------------------

[ SCIENTIFIC FUNCTIONS ]
  sin(x)     Sine function
  cos(x)     Cosine function
  log(x)     Logarithm function

--------------------------------------------------

[ VARIABLES ]
  You can store values inside variables.

  Example:
    x = 5
    y = 10
    x + y

--------------------------------------------------

[ EXPRESSION EXAMPLES ]

  5 + 2 * 3
  (4 + 6) / 2
  sin(30)
  log(10)

--------------------------------------------------

[ AVAILABLE COMMANDS ]

  help       Show help screen
  history    Show previous calculations
  clear      Clear console screen
  exit       Close the program

--------------------------------------------------

[ NOTES ]

  - Spaces are allowed in expressions
  - Parentheses are supported
  - Invalid expressions will show an error
  - Division by zero is not allowed

==================================================

)";
	}
	void ClearScreen() {
		system("cls");
	}
	void Reset()
	{
		this->expression = "";
		this->Result = 0;
		Output.clear();
		while (!Operations.empty()) {
			Operations.pop();

		}
		Tokens.clear();

	}
	void TextCorrection(string& temp)
	{
		string NewTemp = "";
		for (char& ch : temp) 
		{ 
			if (ch!=' ')
			{
				ch = tolower((unsigned char)ch);
				NewTemp = NewTemp + ch;
			}
		}
		temp = NewTemp;
	}
	// //Analyize the enterd text
	void TokenizingText(string temp) 
	{
		size_t Size = temp.size();
		for (int i = 0; i < Size; i++)
		{
			string Temp;
			if (isdigit(temp[i]))
			{
				
				for (int j = i; j < Size; j++)
				{

					if (isdigit(temp[j]))
					{
						Temp = Temp + temp[j];
						if (j == (Size - 1))
						{
							Tokens.push_back(Temp);
							i = j;
							break;
						}
					}
					else
					{
						i = j - 1;
						Tokens.push_back(Temp);


						break;
					}
				}
			}
			else
			{


			
				Temp = Temp + temp[i];
				Tokens.push_back(Temp);

			}
		}

	}
	//Test
	void PrintTokens() 
	{
		for (string& st : Tokens) 
		{
			cout << st;
		}
	}
};


int main()
{
	calculator c;
	string temp = "   2   +   8/ 2  *    2";
	c.TextCorrection(temp);
	c.TokenizingText(temp);
	c.PrintTokens();
}

