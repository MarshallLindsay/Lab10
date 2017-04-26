/*
	C++ test for trying lots of stuff
	
*/
#include <iostream>
#include <string>
using namespace std;


string getUserInput1(void) throw(string);
void function1(void) throw(const int);
int main(void){
	string userInput= "Input";
	try{
		throw(3);
	}catch(...){
		cout<<"\n Caught it!"<<endl;
	}
	
	cout<<userInput<<endl;
	
	
	return(0);
}

void function1(void)throw(const int){
	throw(1);
}

string getUserInput1(void) throw(string){
	string userInput;
	cout<<"\nEnter 'F' to use the file name or 'N' to use the file number:"<<endl;
	getline(cin, userInput);
	//Convert input to upper case
	for(auto &c : userInput){
		c = toupper(c);
	}
	
	if(userInput != "F" && userInput != "N")
		throw((string)("\n Invalid Input!"));
	else
		return(userInput);
}