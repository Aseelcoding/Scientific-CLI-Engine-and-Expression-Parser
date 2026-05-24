#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <map>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include<deque>
#include <string>
#include <fstream>
#include <chrono>
//CHisxtory.txt
using namespace std;
class calculator
{
private:
	map <string, double> Variables = {
	{"a",0}, {"b",0}, {"c",0}, {"d",0}, {"e",0},
	{"f",0}, {"g",0}, {"h",0}, {"i",0}, {"j",0},
	{"k",0}, {"l",0}, {"m",0}, {"n",0}, {"o",0},
	{"p",0}, {"q",0}, {"r",0}, {"s",0}, {"t",0},
	{"u",0}, {"v",0}, {"w",0}, {"x",0}, {"y",0},
	{"z",0}
	};

	//
	map <string, short>precedence = { {"(",5}, {")",5}, {"*",4},{"/",4} ,{"+",2} ,{"-" ,2}};
	deque<string> Output;
	stack<string> Operations;
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
	void HistoryScreen()
	{
		system("cls");
		cout <<
			R"(
==================================================
                  HISTORY SCREEN
==================================================
------------------------------------------------------------------------------------------------------------------------)" << endl;
		ReadFromFile();

	
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
			if (ch != ' ')
			{
				ch = tolower((unsigned char)ch);
				NewTemp = NewTemp + ch;
			}
		}
		temp = NewTemp;
		expression = temp;
	}
	// //Analyize the enterd text
	//My isDigitFunction
	bool IsItNumber(const string& str)
	{
		if (str.empty())
			return false;

		bool hasDecimal = false;
		bool hasDigit = false;

		for (int i = 0; i < str.size(); i++)
		{
			char ch = str[i];

			if (ch == '.')
			{
				if (hasDecimal)
					return false;

				hasDecimal = true;
			}
			else if (ch == '+' || ch == '-')
			{
				if (i != 0)
					return false;
			}
			else if (isdigit((unsigned char)ch))
			{
				hasDigit = true;
			}
			else
			{
				return false;
			}
		}

		return hasDigit;
	}
	bool SetVar(string temp) 
	{
		if (temp.size() <= 2)
			return false;

		string Temp;
		Temp = Temp + temp[0];
		if (Variables.find(Temp) != Variables.end()) 
		{
			string Num;
			for (int i = 2; i < temp.size(); i++) 
			{
				
				Num = Num + temp[i];
				if (!IsItNumber(Num))
				{
					return false;
				}
				
			}
			auto f = Variables.find(Temp);
			f->second = stod(Num);
			return true;
		}
		return true;
	}
	string TokenizingText(string temp)
	{
		if (temp.empty())
			return "false";
		size_t Size = temp.size();
		for (int i = 0; i < Size; i++)
		{
			string Temp;
			if (isdigit(temp[i]))
			{	for (int j = i; j < Size; j++)
				{
					if (isdigit(temp[j]) || temp[j] == '.')
					{
						Temp = Temp + temp[j];
						if (j == (Size - 1))
						{
							if (IsItNumber(Temp))
							{
								Tokens.push_back(Temp);
								i = j;
								break;
							}
							else { return "false"; }
						}
					}

					else

					{

						i = j - 1;
						if (IsItNumber(Temp))

						{

							Tokens.push_back(Temp);

						}

						else

							return "false";





						break;

					}

				}

			}
			else
			{
				Temp = Temp + temp[i];
				if (precedence.find(Temp) != precedence.end())
				{

					if ((Temp == "-" || Temp == "+") && (i == 0 || Tokens.back() == "("))

					{

						for (int j = i + 1; j < Size; j++)

						{



							if (isdigit(temp[j]) || temp[j] == '.')

							{

								Temp = Temp + temp[j];

								if (j == (Size - 1))

								{
								

									if (IsItNumber(Temp))

									{
										i = j;
										Tokens.push_back(Temp);

								

										break;

									}

									else { return "false"; }

								}

							}

							else

							{


								if (IsItNumber(Temp))

								{

									i = j-1;

								
								}

								else

									return "false";



								break;


							}

						}

						Tokens.push_back(Temp);

					}

					else if ((Temp != "-" && Temp != "+" && Temp != "(") && (i == 0 || Tokens.back() == "("))

					{

						return "false";

					}

					else

						Tokens.push_back(Temp);

				}

				else if ((Variables.find(Temp) != Variables.end() ))
				{
					auto f = Variables.find(Temp);
					if (i + 2 >= Size)
						return "false";
					Temp = "";
					Temp = Temp + to_string(f->second);
					Tokens.push_back(Temp);

				}
				else

					return "false";




			}

		}

		return "true";

	}
	//
	
	bool PolishNotation()
	{
		int count = 0;

		while (!Tokens.empty())
		{

			if (IsItNumber(Tokens[count]))
			{

				Output.push_front(Tokens[count]);

			}
			else if (precedence.find(Tokens[count]) != precedence.end())
			{

				if (Operations.empty())
				{
					auto f = precedence.find(Tokens[count]);
					Operations.push(f->first);
				}
				else
				{
					auto inside = precedence.find(Operations.top());
					auto out = precedence.find(Tokens[count]);

					if (out->first == ")")
					{
						while (Operations.top() != "(")
						{
							Output.push_front(Operations.top());
							Operations.pop();

						}
						Operations.pop();
					}
					while (inside->second > out->second)
					{
						if (inside->first != "(" && out->first != ")")
						{
							Output.push_front(Operations.top());
							Operations.pop();
							if (!Operations.empty())
							{
								inside = precedence.find(Operations.top());

							}
							else { break; }
						}
						else { break; }
					}
					if (out->first != ")")
						Operations.push(out->first);
				}


			}

			else
			{

				return false;
			}


			Tokens.erase(Tokens.begin() + count);

		}
		while (!Operations.empty())
		{
			Output.push_front(Operations.top());
			Operations.pop();
		}


		return true;
	}
	void evaluate()
	{
		for (int i = Output.size() - 1; i >= 0; i--)
		{
			string Result = "";

			if (Output[i] == "+")
			{
				Result = to_string((stod(Output[i + 1]) + stod(Output[i + 2])));
				Output.erase(Output.begin() + (i + 1), Output.begin() + (i + 3));
				Output[i] = Result;
				i = Output.size() - 1;
			}
			else if (Output[i] == "-")
			{
				Result = to_string((stod(Output[i + 1]) - stod(Output[i + 2])));
				Output.erase(Output.begin() + (i + 1), Output.begin() + (i + 3));
				Output[i] = Result;
				i = Output.size() - 1;
			}
			else if (Output[i] == "*")
			{
				Result = to_string((stod(Output[i + 1]) * stod(Output[i + 2])));
				Output.erase(Output.begin() + (i + 1), Output.begin() + (i + 3));
				Output[i] = Result;
				i = Output.size() - 1;
			}
			else if (Output[i] == "/")
			{
				Result = to_string((stod(Output[i + 1]) / stod(Output[i + 2])));
				Output.erase(Output.begin() + (i + 1), Output.begin() + (i + 3));
				Output[i] = Result;
				i = Output.size() - 1;
			}


			if (Output.size() == 1)
				break;

		}

		Result = stod(Output.front());
	}

	//
	void SaveToFile() 
	{
		std::ofstream outFile("CHistory.txt", std::ios::out | std::ios::app);
		if (outFile.is_open()) 
		{
			auto Now = chrono::system_clock::now();
		time_t currentTime = chrono::system_clock::to_time_t(Now);
			outFile << ctime(&currentTime) <<"  " << this->expression <<endl;
			outFile.close(); // Always close your files
		}


	}
	void ReadFromFile() 
	{
		std::ifstream inFile("CHistory.txt");
		std::string line;
		if (inFile.is_open()) {
			while (std::getline(inFile, line)) 
			{
				std::cout << line << std::endl;
			}
			inFile.close();
		}
	}
};
void StartTheProgram() 
{
	calculator c;
	string temp;
	string temp2;

	do
	{
		c.Reset();
		c.MainScreen();
		getline(cin, temp);
		c.TextCorrection(temp);
		
		if (temp == "help") 
		{
			c.HelpScreen();
			system("pause");
			continue;
		}
		else if (temp == "exit") { continue; }
		else if (temp == "history") 
		{
			c.HistoryScreen();
			system("pause");
			continue;
		}
		else if (temp == "clear") 
		{
			c.ClearScreen();
			continue;
		}
		else if ((!isdigit(temp[0]) &&temp[1]=='='))
		{
			if (c.SetVar(temp)) 
			{
				cout << "var Saved \n\n";
				system("pause");
				continue;
			}
			else {
				cout << "Bad expression , try again \n\n";
				system("pause");
				continue;
			}

		}
		temp2 = c.TokenizingText(temp);
	
		if (temp2 =="false")
		{
			
			cout << "Bad expression , try again \n\n";
			system("pause");
			continue;
		}
		else if (temp2 == "var")
		{
			cout << "var saved ! \n\n";
			system("pause");
			continue;
		}
		if (!c.PolishNotation()) 
		{
		
			cout << "Bad expression , try again \n\n";
			system("pause");
			continue;
		}


		c.evaluate();
		cout << "Result : " << c.Result << endl;;
		c.SaveToFile();
		system("pause");
		continue;

	} while (temp != "exit");

}
int main()
{
	
	StartTheProgram();

}

