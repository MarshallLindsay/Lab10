/*
	Marshall Lindsay
	Lab10
	4/25/17
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>

using namespace std;

#define DEFAULT_DATA_FILE "defaultData.txt"

//Signal Class
class Signal{
	private:
		string fileName;
		int length;
		double max_value;
		double average;
		vector<double> data;
		void calcAvg();
		double calcMaxValue();
		
	public:

		void operator*(double x);
		void operator+(double x);
		void addData(double x, int i);
		void setName(string);
		double getData(int);
		void setAvg(double);
		double getAvg();
		void setData(double, int);
		double getMax();
		void setMax(double);
		int getLength();
		void center();
		void normalize();
		void Sig_info();
		void Save_file(string);
		Signal();
		Signal(string L);
		Signal(const char* fileName)throw(const char*);
		~Signal();

};

//Default constructor. Sets all private members to zero
Signal::Signal(){
	this -> fileName = "void";
	this -> length = 0;
	this -> max_value = 0;
	this -> average = 0;
	
}

//Filenumber constructor. Opens the data file with the corresponding filenumber
//and sets all the private members.
Signal::Signal(string L){
	fstream dataFile;
	string fileName;
	
	//Declare a const char* to be used with the .open() on line 115
	//that points to the file name.
	const char* ptrFileName = fileName.c_str();
	
	
	//Append the integers into the file name template
	fileName = std::string("Raw_data_") + L + ".txt";
	
	this->fileName = fileName;
	//Open the correct file
	dataFile.open(ptrFileName);
	
	//Check that the file was opened correctly.
	//If not, set default values and return
	if(!dataFile.is_open()){
		cout<<"\nCould not open "<<fileName<<" setting default values!"<<endl;
		this -> fileName = "NULL";
		this -> length = 0;
		this -> max_value = 0;
		this -> average = 0;
		return;
	}
	
	//Read the number of integers in the datafile
	dataFile >>  this -> length;
	vector<double> copy(this -> length, 0);
	//Allocate memory for the data array.
	this -> data = copy;
	
	//Read the max value from the data file
	dataFile >> this -> max_value;
	
	//Read the data from the file and place in the data array.
	for(int i = 0; i < this -> data.size(); i++){
		dataFile >> this -> data[i];
	}
	//Close the file
	dataFile.close();
	//Calculate the average value from the data
	calcAvg();
	return;
}

Signal::Signal(const char* fileName)throw(const char*){
	fstream dataFile;
	
	this->fileName = fileName;
	//Open the correct file
	dataFile.open(fileName);
	
	//Check that the file was opened correctly.
	//If not, set default values and return
	if(!dataFile.is_open()){
		throw(fileName);
	}
	
	//Read the number of integers in the datafile
	dataFile >>  this -> length;
	vector<double> copy(this -> length, 0);
	//Allocate memory for the data array.
	this -> data = copy;
	
	//Read the max value from the data file
	dataFile >> this -> max_value;
	
	//Read the data from the file and place in the data array.
	for(int i = 0; i < this -> data.size(); i++){
		dataFile >> this -> data[i];
	}
	
	dataFile.close();
	calcAvg();
	return;
}

//Destructor. Doesn't do anything really. It prints to know it was called.
Signal::~Signal(){
	cout<<"Destructor"<<endl;
}

double Signal::getAvg(){
	return(this-> average);
}

void Signal::setAvg(double value){
	this->average = value;
}

void Signal::setName(string name){
	this->fileName = name;
}

//Finds the maximum value in the data set and returns it.
double Signal::calcMaxValue(){
	double hold = 0;
	
	for(int i = 0; i < this -> data.size(); i++){
		if(this -> data[i] > hold)
			hold = this -> data[i];
	}
	
	return(hold);
	
}

void Signal::setMax(double value){
	this->max_value = value;
}

//Returns the value at the specified location in the data vector
double Signal::getData(int i){
	if(i < (this -> length)-1)
		return(this->data[i]);
	return(0);
}

//Returns the objects length member
int Signal::getLength(){
	return(this->length);
}

//Calculates the average of the data set and sets the average member.
void Signal::calcAvg(){
	
	double total = 0;
	
	for(int i = 0; i < this -> data.size(); i++){
		total += this -> data[i];
	}
	
	this -> average = (double)(total) / this -> length;
	
}

//Sets the data at the index to the value specified.
void Signal::setData(double value, int i){
	this->data[i] = value;
}
//Returns the max_value
double Signal::getMax(){
	return(this->max_value);
}

//Overloaded operator to multiply a signal by a double. Multiplies each
//data value by the double value sent to the function. Finds the new max
//value and calculates the new average.
void Signal::operator*(double x){
	
	for(int i = 0; i < this -> length; i++){
		this -> data[i] = this -> data[i] * x;
	}
	this -> max_value = calcMaxValue();
	calcAvg();
}

//Overloaded operator to add a double to a signal. Adds the double to each
//of the data values. Finds the new max value and calulates the new average.
void Signal::operator+(double x){
	
	for(int i = 0; i < this -> length; i++){
		this -> data[i] = this -> data[i] + x;
	}
	this -> max_value = calcMaxValue();
	calcAvg();
}

//Adds a value x to the data indexed by i
void Signal::addData(double x, int i){
	this->data[i] += x;
}

//Centers the data by using the overloaded addition operator.
void Signal::center(){
	this -> operator+(-(this -> average));
	this -> max_value = calcMaxValue();
	calcAvg();
}

//Normalizes the data by using the overloaded multiplication operator.
void Signal::normalize(){
	operator*(1/(this->max_value));
	this -> max_value = calcMaxValue();
	calcAvg();
	
}

//Prints all of the information about the signal. This was changed from
//Lab6 to include the printing of the data and the filename where the data
//came from.
void Signal::Sig_info(){
	cout<<"\nData file name: "<< this->fileName
	<<"\nNumber of data points (length): "<<this->length
	<<"\nMaximum value (max_value): "<<this->max_value
	<<"\nAverage of data (average): "<<this->average<<endl;
	for( int i = 0; i < this->length; i++){
		cout<< this ->data[i] << endl;
	}
}

//Saves the current signal to a new file whose name is that
//of the string that is passed to the function.
void Signal::Save_file(string newFileName){
	newFileName = std::string(newFileName) + ".txt";
	const char* newFilePtr = newFileName.c_str();
	
	//open save file
	
	ofstream saveFile(newFilePtr);
	
	//Save the Length, Max Value, and the data to the save file
	saveFile << this->length<< " " << this->max_value<<endl;
	
	for(auto i:data){
		saveFile<< i <<endl;
	}
	
	//Close the file
	saveFile.close();
	return;
}

class ExceptionObject{
	private:
		int size1;
		int size2;
	public:
		ExceptionObject(int a, int b) : size1(a), size2(b){};
		void msg(void);
	
};

void ExceptionObject::msg(void){
	cout<<"\n Could not add the two signals, they are not the same size!\n"
		<<"\n Signal1 size: "<<this->size1
		<<"\n Signal2 size: "<<this->size2<<endl;
}

Signal operator+(Signal, Signal) throw(ExceptionObject);
void optionMenu();
double scaling();
double offsetting();
Signal addSignals();
string fileSave();
string getUserInput1(void) throw(string);
double getScalingValue(void) throw(const int);

int main(){
	
	locale loc; //Used for some error checking.
	string userInput;
	string fileName;
	const char* fileNamePtr = fileName.c_str();
	Signal* dataSignal;
	
	cout<<"\n****Lab7****"<<endl;
	while(1){
		
		while(1){
			try{
				userInput = getUserInput1();
				break;
			}
			catch(string message){
				cout<<message;
			}
		}
		
		if(userInput == "F"){
			while(1){	
				try{
					cout<<"Please enter the file name to be opened:"<<endl;
					getline(cin, fileName);
					dataSignal = new Signal(fileNamePtr);		//If file does not exist, will throw an exception.
					break;
				}
				catch(...){										//Catch will catch the bad file exception.
					cout<<"\n "<<fileName<<" is not a valid file!"<<endl;
					cin.clear();
					fflush(stdin);
				}
			}
		}else{
			cout<<"\nPlease enter the file number to be opened:"<<endl;
			getline(cin, userInput);
			//Error check on file number input
			while(userInput.size() > 2 || (!isdigit(userInput[0],loc) && !isdigit(userInput[1],loc))){
				cout<<"\nInvalid file number!"<<endl;
				cout<<"\nPlease enter the file number to be opened:"<<endl;
				getline(cin, userInput);
			}
			if(userInput.size() == 1){
				string hold = userInput;
				userInput = "0";
				userInput = userInput + hold;
			}
			dataSignal = new Signal(userInput);
		}
		
		while(1){
		try{
				//Display option menu
				optionMenu();
			
				//Get user choice
				getline(cin, userInput);
			
				for(auto &c: userInput){
					c = toupper(c);
				}
				//Logic on the user input for operations
				if(userInput == "S"){
					dataSignal->operator*(scaling());
				}else if(userInput == "O"){
					dataSignal->operator+(offsetting());
				}else if(userInput == "P"){
					dataSignal->Sig_info();
				}else if(userInput == "C"){
					dataSignal->Sig_info();
				}else if(userInput == "N"){
					dataSignal->normalize();
				}else if(userInput == "V"){
					dataSignal->Save_file(fileSave());
				}else if(userInput == "Q"){
					break;
				}else if(userInput == "A"){
					*dataSignal = *dataSignal + addSignals();
				}else{
					cout<<"Invalid input!"<<endl;
				}
			}
			catch(ExceptionObject eo){
				eo.msg();
			}
			catch(...){
				cout<<"\n Catch all block from optionsMenu"<<endl;
			}
		}
		
		cout<<"Would you like to manipulate another signal?(Y N)"<<endl;
		getline(cin, userInput);
		for(auto &c: userInput){
			c = toupper(c);
		}
		while(userInput != "Y" && userInput != "N"){
			cout<<"\nInvalid input!"<<endl;
			cout<<"Would you like to manipulate another signal?(Y N)"<<endl;
			getline(cin, userInput);
			for(auto &c:userInput){
				c = toupper(c);
			}
		}
		if(userInput == "N"){
			delete dataSignal;
			break;
		}
		
		delete dataSignal;
		
	}
	
	return(0);
}

void optionMenu(){
	
	cout<<"What would you like to do with the signal?"<<endl;
	cout<<"(S) : Scale the data\n"
		<<"(O) : Offset the data\n"
		<<"(P) : Print statistics for the data\n"
		<<"(C) : Center the data\n"
		<<"(N) : Normalize the data\n"
		<<"(A) : Add signals\n"
		<<"(V) : Save data to file\n"
		<<"(Q) : Quit"<<endl;
	return;
}

double scaling(){
	double value;
	while(1){
		try{
			value = getScalingValue();
			return(value);
		}
		catch(const int y){
			cout<<"\n Rethrow caught in scaling. Supplied by getScalingValue"<<endl;
			if(y == 1){
				cin.clear();
				fflush(stdin);
			}
		}
		catch(...){
			cout<<"\n Rethrow caught in scaling(catch all). Supplied by getScalingValue"<<endl;
		}
	}
}

double getScalingValue()throw(const int){
	double userInput;
	try{
		cout<<"\n Enter a value to scale by: "<<endl;
		cin>>userInput;
		if(cin.fail()){
			throw(1);
		}else if(userInput == 0){
			throw(2);
		}
		return(userInput);
	}
	catch(const int x){
		if(x == 1){
			cout<<"\n Scaling value supplied is not a number!"<<endl;
			throw;
		}else if(x == 2){
			cout<<"\n Cannot scale by zero!"<<endl;
			throw;
		}
	}
	catch(...){
		cout<<"\n Not sure how you got here. Catch all getScalingValue()"<<endl;
		throw;
	}
	
}

double offsetting(){
	double value;
	
	cout<<"Please enter the value you wish to offset the data by:"<<endl;
	cin >> value;
	
	//Check that the user input is a double type
	while(cin.fail()){
		cin.clear();
		fflush(stdin);
		cout<<"Invalid input! Please enter a number!"<<endl;
		cin >> value;
	}
	fflush(stdin);
	return(value);
}

string fileSave(){
	
	string newFileName;
	
	cout<<"Please enter the name of the file to save the updated data to:"<<endl;
	getline(cin, newFileName);
	
	return(newFileName);
	
}

//Opens a new signal to be added to the current one
//Returns that signal.
Signal addSignals(){
	locale loc;
	string userInput;
	Signal* dataSignal;
	string fileName;
	const char* fileNamePtr = fileName.c_str();
	cout<<"\nPlease specify which data file contains the signal you wish to add."<<endl;
	cout<<"Enter 'F' to use the file name or 'N' to use the file number:"<<endl;
	getline(cin, userInput);
	//Convert input to upper case
	for(auto &c : userInput){
		c = toupper(c);
	}
	//Error check input
	while(userInput != "F" && userInput != "N"){
		cout<<"\nInvalid input!"<<endl;
		cout<<"\nEnter 'F' to use the file name or 'N' to use the file number:"<<endl;
		getline(cin, userInput);
		for(auto &c : userInput){
		c = toupper(c);
		}
	}
	//Logic on input
	if(userInput == "F"){
		cout<<"Please enter the file name to be opened:"<<endl;
		getline(cin, fileName);
		dataSignal = new Signal(fileNamePtr);
	}else{
		cout<<"\nPlease enter the file number to be opened:"<<endl;
		getline(cin, userInput);
		//Error check on file number input
		while(userInput.size() > 2 || (!isdigit(userInput[0],loc) && !isdigit(userInput[1],loc))){
			cout<<"\nInvalid file number!"<<endl;
			cout<<"\nPlease enter the file number to be opened:"<<endl;
			getline(cin, userInput);
		}
		if(userInput.size() == 1){
			string hold = userInput;
			userInput = "0";
			userInput = userInput + hold;
		}
		dataSignal = new Signal(userInput);
	}
	
return(*dataSignal);
}

Signal operator+(Signal sig1, Signal sig2) throw(ExceptionObject){
	if(sig1.getLength() != sig2.getLength()){
		throw(ExceptionObject(sig1.getLength(), sig2.getLength()));
	}
	
	for(int i = 0; i < sig1.getLength(); i++){
		sig1.addData(sig2.getData(i), i);
	}
	double max = sig1.getMax() > sig2.getMax() ? sig1.getMax() : sig2.getMax();
	sig1.setAvg(sig1.getAvg() + sig2.getAvg());
	sig1.setName("Added");
	sig1.setMax(max);
	
	return(sig1);
	
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