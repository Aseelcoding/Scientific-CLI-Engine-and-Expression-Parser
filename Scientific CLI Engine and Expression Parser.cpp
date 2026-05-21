#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class calculator
{
private :
	map <string, int> Variables;
	//
	map <char, short>precedence = { {'*',4},{'/',4} ,{'+',2} ,{ '-' ,2 } };
	deque<string> Output;
	stack<char> Op;
	//


};


int main()
{

}

