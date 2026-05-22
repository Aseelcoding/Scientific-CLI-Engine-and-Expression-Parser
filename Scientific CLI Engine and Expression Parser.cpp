#include <iostream>
#include <cctype>
#include <map>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include<deque>
#include <string>
using namespace std;

class calculator
{
private:
	map <string, int> Variables;
	//
	map <string, short>precedence = { {"(",5}, { ")",5 }, {"*",4},{"/",4} ,{"+",2} ,{"-" ,2} };
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
	}
	// //Analyize the enterd text
	//My isDigitFunction
	bool IsItNumber(const string& str)
	{
		bool hasDecimal = false;
		for (char ch : str)
		{
			if (ch == '.')
			{
				if (hasDecimal) return false;
				hasDecimal = true;
			}
			else if (!isdigit((signed char)ch)&& !(ch=='-'||ch=='+'))
			{
				return false;
			}
		}
		return true;

	}
	bool TokenizingText(string temp)
	{
		size_t Size = temp.size();
		for (int i = 0; i < Size; i++)
		{
			string Temp;
			if (isdigit(temp[i]))
			{

				for (int j = i; j < Size; j++)
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
							else { return false; }
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
							return false;


						break;
					}
				}
			}
			else 
			{
				Temp = Temp + temp[i];

				if (precedence.find(Temp) != precedence.end())
				{
					if ((Temp == "-" || Temp == "+") && (i == 0) || (Tokens.back() == "("))
					{
						for (int j = i+1; j < Size; j++)
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
									else { return false; }
								}
							}
							else
							{
							
								if (IsItNumber(Temp))
								{
									i = j - 1;
									
								}
								else
									return false;

								break;
							
							}
						}
						Tokens.push_back(Temp);
					}
					else if ((Temp != "-" && Temp != "+" && Temp!="(") && (i == 0) || (Tokens.back() == "("))
					{
						return false;
					}
					else
					Tokens.push_back(Temp);
				}
				else
					return false;

				
			}
		}
		return true;
	}
	//
	void print() {
	
		for (string& s : Tokens) 
		{
			cout << s << endl;
		}
	}

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

	void Print()
	{

		while (!Output.empty())
		{
			cout << Output.front() << endl;
			Output.pop_front();
		}
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


};


int main()
{
	calculator c;
	string temp = "-2.5+2.5+(1+1+1*5)";
	c.TextCorrection(temp);
	c.TokenizingText(temp);
	c.print();
	c.PolishNotation();
	c.Print();
	c.evaluate();
	cout << c.Result;


}

