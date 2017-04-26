/*
	Marshall Lindsay
	ECE3220
	Lab10
	4/25/17
*/
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define PI 3.14159

/***********************************************************
					Base Conic Class
***********************************************************/
class BaseConic{
	protected:
		string name;	//Name of the object
		double x;		//X coordinate of the center
		double y;		//Y coordinate of the center
		
	public:
		BaseConic();
		BaseConic(double _x, double _y, string _name);
		virtual ~BaseConic(){};
		virtual void move(double nx, double ny);
		virtual void rotate(double) = 0;
		virtual void resize(void) = 0;
		virtual void printInfo(void);
		virtual void validPoint(double,double) = 0;
		virtual void calcVertices(void) = 0;
		virtual void calcCircumference(void) = 0;
		virtual void calcArea(void) = 0;
};

//Default constructor for BaseConic. Sets X and Y equal to 0 and 
//sets the name to "Default"
BaseConic::BaseConic(){
	this->x = 0;
	this->y = 0;
	this->name = "Default";
}

//Parametric constructor for BaseConic. Sets x,y, and name to the
//given values.
BaseConic::BaseConic(double _x, double _y, string _name){
	this -> x = _x; 
	this-> y = _y; 
	this->name = _name;
}

//Move method. Sets the x and y coordinates to the given coordinates.
void BaseConic::move(double nx, double ny){
	this->x = nx;
	this->y = ny;
}

//Prints the x and y coordinates of the conic center
void BaseConic::printInfo(void){
	cout<<" This conic's name : "<< this->name
		<<"\n X coordinate for center of : "<<this->x
		<<"\n y coordinate : "<<this->y<<endl;
}

/***********************************************************
			Derived Circle Class from Base Conic
***********************************************************/
class Circle : public BaseConic{
	private:
		double radius;
		double area;
		double circumference;
	public:
		Circle();
		Circle(double _x, double _y, double _radius, string _name);
		~Circle(){};
		void calcCircumference(void);
		void validPoint(double _x, double _y);
		void rotate(double){};
		void resize(void);
		void calcVertices(void){};
		void calcArea(void);
		void printInfo(void);
	
};

//Default consructor for circle. This should not be used but given just in case.
//Calls the Base Conic default constructor. Sets the radius equal to 1 and calculates
//the area and circumference from there.

Circle::Circle() : BaseConic(){
	this->radius = 1;
	this->calcCircumference();
	this->calcArea();
}

//Parametric constructor. Sets X and Y equal to the given values and calculates the area
//and circumference respectively.

Circle::Circle(double _x, double _y, double _radius, string _name) : BaseConic(_x, _y, _name){
	this->radius = _radius;
	this->calcArea();
	this->calcCircumference();

}

//Method to set the circumference from the objects radius.
void Circle::calcCircumference(void){
	this->circumference = 2 * PI * this->radius;
}

//Method to set the area from the objects radius.
void Circle::calcArea(void){
	this->area = PI * radius * radius;
}

//Method to resize the object given a new radius.
void Circle::resize(void){
	string userInput;
	cout<<"\n Please enter the new radius: "<<endl;
	getline(cin, userInput);
	this->radius = atof(userInput.c_str());
	this->calcArea();
	this->calcCircumference();
}

//Method to check if a given point is within the circle, outside the circle or on the circle.
//Prints a message corresponding to the result.
void Circle::validPoint(double _x, double _y){
	if(((_x - this->x) * (_x - this->x)) + ((_y- this->y) *(_y - this->y)) == (this->radius * this->radius)){
		cout<<"\n The point ("<<_x<<","<<_y<<") is on the circle"<<endl;
	}else if(((_x - this->x) * (_x - this->x)) + ((_y- this->y) *(_y - this->y)) > (this->radius * this->radius)){
		cout<<"\n The point ("<<_x<<","<<_y<<") is outside the circle"<<endl;
	}else{
		cout<<"\n The point ("<<_x<<","<<_y<<") is inside the circle"<<endl;
	}
}

//Method to print all of the information about the circle.
void Circle::printInfo(void){
	cout<<"\n The name of the circle is: "<<this->name
		<<"\n Coordinates are: ("<<this->x<<","<<this->y<<")"
		<<"\n The radius is: "<<this->radius
		<<"\n The area is: "<<this->area
		<<"\n The circumference is: "<<this->circumference<<endl;
}

/***********************************************************
			Derived Elipse Class from Base Conic
***********************************************************/
class Ellipse : public BaseConic{
	private:
		double a;		//semi-major axis
		double b;		//semi-minor axis
		double angle;	//orientation angle
		
		double vmajor_x1;
		double vmajor_x2;
		double vmajor_y1;
		double vmajor_y2;
		
		double vminor_x1;
		double vminor_x2;
		double vminor_y1;
		double vminor_y2;
		
		double area;
	public:
		Ellipse();
		Ellipse(double _x, double _y, double _a, double _b, double _angle, string _name);
		~Ellipse(){};
		void move(double nx, double ny);
		void rotate(double nangle);
		void resize(void);
		void printInfo(void);
		void validPoint(double, double){};
		void calcArea(void);
		void calcCircumference(void){};
		void calcVertices(void);
};

//Defaule constructor. Calls the BaseConic default constructor.
//Sets the major axis, minor axis, and angle to zero. Calculates the vertices
//and the area.
Ellipse::Ellipse() : BaseConic(){
	this->a = 1;
	this->b = 1;
	this->angle = 0;
	this->calcArea();
	this->calcVertices();
}

//Parametric constructor. Takes the initial position (x,y), the length of the major
//and minor axis, the angle of orientation and the name of the object. It calls the
//BaseConic parametric constructor with the (x,y) and the name. Calulates the area and
//vertices.
Ellipse::Ellipse(double _x, double _y, double _a, double _b, double _angle, string _name) : BaseConic(_x,_y, _name){
	this->a = _a;
	this->b = _b;
	this->angle = _angle;
	this->calcArea();
	this->calcVertices();
}

//Calculates the area of the Ellipse based off the major and minor axis lengths.
void Ellipse::calcArea(void){
	this->area = PI * a * b;
}

//Calculates the verties of the Ellipse based off the major and minor axis lengths
//and the orientation angle.
void Ellipse::calcVertices(void){
	//Major vertices.
	this->vmajor_y1 = this->y + (this->a)*(sin((this->angle+90) * PI / 180));
	this->vmajor_x1 = this->x + (this->a)*(cos((this->angle+90) * PI / 180));
	this->vmajor_x2 = this->x - (this->a)*(cos((this->angle+90) * PI / 180));
	this->vmajor_y2 = this->y - (this->a)*(sin((this->angle+90) * PI / 180));
	
	//Minor vertices.
	this->vminor_x1 = this->x + (this->b)*(cos(this->angle * PI / 180));
	this->vminor_y1 = this->y + (this->b)*(sin(this->angle * PI / 180));
	this->vminor_y2 = this->y - (this->b)*(sin(this->angle * PI / 180));
	this->vminor_x2 = this->x - (this->b)*(cos(this->angle * PI / 180));
}

//Method to rotate the Ellipse. Sets the angle to the new angle and recalculates the
//vertices.
void Ellipse::rotate(double nangle){
		this->angle = nangle;
		this->calcVertices();
}

//Method to move the Ellipse. Sets the center to the new coordinates, calculates the new
//vertices.
void Ellipse::move(double nx, double ny){
	this->x = nx;
	this->y = ny;
	this->calcVertices();
}

//Method to resize the ellipse given new major and minor axis.
void Ellipse::resize(void){
	string userInput;
	
	cout<<"\n Please enter the new major axis length: "<<endl;
	getline(cin, userInput);
	this->a = atof(userInput.c_str());
	cout<<"\n Please enter the new minor axis length: "<<endl;
	getline(cin, userInput);
	this->b = atof(userInput.c_str());
	
	this->calcVertices();
}

void Ellipse::printInfo(void){
	cout<<"\n The name of the Ellipse is: "<<this->name
	<<"\n Center coordinates are: ("<<this->x<<","<<this->y<<")"
	<<"\n The major axis length is: "<<this->a
	<<"\n The minor axis length is: "<<this->b
	<<"\n The orientation angle is: "<<this->angle
	<<"\n The major axis vertice coordinates are: ("<<this->vmajor_x1<<","<<this->vmajor_y1<<"),"
	<<"("<<this->vmajor_x2<<","<<this->vmajor_y2<<")"
	<<"\n The minor axis vertice coordinates are: ("<<this->vminor_x1<<","<<this->vminor_y1<<"),"
	<<"("<<this->vminor_x2<<","<<this->vminor_y2<<")"<<endl;

}

void optionsMenu(void);

void baseConic(BaseConic*);
BaseConic* createBaseConic(void);

void ellipse(BaseConic*);
BaseConic* createEllipse(void);
void ellipseOptionsMenu(void);

void circle(BaseConic*);
BaseConic* createCircle(void);
void circleOptionsMenu(void);

int main(void){
	BaseConic* basePtr = NULL;

	string userInput;
	while(1){
		optionsMenu();
		getline(cin,userInput);
		if(userInput == "1"){
			baseConic(basePtr);
		}else if(userInput == "2"){
			circle(basePtr);
		}else if(userInput == "3"){
			ellipse(basePtr);
		}else if(userInput == "4"){
			return(0);
		}else{
			cout<<"\n Invalid Input!"<<endl;
		}
		
	}
	
	return(0);
}

void optionsMenu(void){
	cout<<"\n What would you like to do?"<<endl;
	cout<<" 1) Create a BaseConic object\n"
		<<" 2) Create a Circle object\n"
		<<" 3) Create an Ellipse object\n"
		<<" 4) Quit"<<endl;
}

void circle(BaseConic* circlePtr){
	string userInput[2];
	
	circlePtr = createCircle();
	
	while(1){
		circleOptionsMenu();
		getline(cin, userInput[0]);
		if(userInput[0] == "1"){
			circlePtr->printInfo();
		}else if(userInput[0] == "2"){
			cout<<"\n Enter the new X coordinate:"<<endl;
			getline(cin, userInput[0]);
			cout<<"\n Enter the new Y coordinate:"<<endl;
			getline(cin, userInput[1]);
			
			circlePtr->move(atof(userInput[0].c_str()), atof(userInput[1].c_str()));
			
		}else if(userInput[0] == "3"){
			circlePtr->resize();
		}else if(userInput[0] == "4"){
			cout<<"\n Enter the X coordinate of the point:"<<endl;
			getline(cin, userInput[0]);
			cout<<"\n Enter the Y coordinate of the point:"<<endl;
			getline(cin, userInput[1]);
			circlePtr->validPoint(atof(userInput[0].c_str()), atof(userInput[1].c_str()));
			
		}else if(userInput[0] == "5"){
			delete circlePtr;
			circlePtr = createCircle();
			
		}else if(userInput[0] == "6"){
			delete circlePtr;
			break;
		}else{
			cout<<"\n Invalid Input!"<<endl;
		}
	}
	
}

BaseConic* createCircle(void){
	string userInput[4];
	cout<<" Please enter the name for the circle: "<<endl;
	getline(cin, userInput[0]);
	
	cout<<" Please enter a starting X coordinate: "<<endl;
	getline(cin, userInput[1]);
	
	cout<<" Please enter a starting Y coordinate: "<<endl;
	getline(cin, userInput[2]);
	
	cout<<" Please enter the radius of the circle: "<<endl;
	getline(cin, userInput[3]);
	
	return(new Circle(atof(userInput[1].c_str()), atof(userInput[2].c_str()), atof(userInput[3].c_str()), userInput[0]));
	
}

void circleOptionsMenu(void){
	cout<<"\n What would you like to do?"
		<<"\n 1)Print the circle information"
		<<"\n 2)Move the circle"
		<<"\n 3)Resize the circle"
		<<"\n 4)Test a point"
		<<"\n 5)Create a new circle"
		<<"\n 6)Quit to main menu"<<endl;
}

void ellipse(BaseConic* ellipsePtr){
	string userInput[2];
	
	ellipsePtr = createEllipse();
	
	while(1){
		ellipseOptionsMenu();
		getline(cin, userInput[0]);
		if(userInput[0] == "1"){
			ellipsePtr->printInfo();
		}else if(userInput[0] == "2"){
			cout<<"\n Enter the new X coordinate:"<<endl;
			getline(cin, userInput[0]);
			cout<<"\n Enter the new Y coordinate:"<<endl;
			getline(cin, userInput[1]);
			
			ellipsePtr->move(atof(userInput[0].c_str()), atof(userInput[1].c_str()));
			
		}else if(userInput[0] == "3"){
			ellipsePtr->resize();
		}else if(userInput[0] == "4"){
			cout<<"\n Enter the new orientation angle: "<<endl;
			getline(cin, userInput[0]);
			ellipsePtr->rotate(atof(userInput[0].c_str()));
		}else if(userInput[0] == "5"){
			delete ellipsePtr;
			ellipsePtr = createEllipse();
			
		}else if(userInput[0] == "6"){
			delete ellipsePtr;
			break;
		}else{
			cout<<"\n Invalid Input!"<<endl;
		}
	}
}

BaseConic* createEllipse(void){
	string userInput[6];
	cout<<" Please enter the name for the Ellipse: "<<endl;
	getline(cin, userInput[0]);
	
	cout<<" Please enter a starting X coordinate: "<<endl;
	getline(cin, userInput[1]);
	
	cout<<" Please enter a starting Y coordinate: "<<endl;
	getline(cin, userInput[2]);
	
	cout<<" Please enter the major axis length: "<<endl;
	getline(cin, userInput[3]);
	
	cout<<" Please enter the minor axis length: "<<endl;
	getline(cin, userInput[4]);
	
	cout<<" Please enter the orientation angle: "<<endl;
	getline(cin, userInput[5]);
	
	return(new Ellipse(atof(userInput[1].c_str()), atof(userInput[2].c_str()), 
			atof(userInput[3].c_str()), atof(userInput[4].c_str()), atof(userInput[5].c_str()), userInput[0]));
}

void ellipseOptionsMenu(void){
	cout<<"\n What would you like to do?"
		<<"\n 1)Print the ellipse information"
		<<"\n 2)Move the ellipse"
		<<"\n 3)Resize the ellipse"
		<<"\n 4)Rotate the ellipse"
		<<"\n 5)Create a new ellipse"
		<<"\n 6)Quit to main menu"<<endl;
}

void baseConic(BaseConic* basePtr){
	
	string userInput[2];
	cout<<"Cannot create an object that is an ABC"<<endl;
	//basePtr = createBaseConic();
	
}
/*
BaseConic* createBaseConic(void){
	string userInput[3];
	cout<<" Please enter the name for the Ellipse: "<<endl;
	getline(cin, userInput[0]);
	
	cout<<" Please enter a starting X coordinate: "<<endl;
	getline(cin, userInput[1]);
	
	cout<<" Please enter a starting Y coordinate: "<<endl;
	getline(cin, userInput[2]);
	
return(new BaseConic(atof(userInput[1].c_str()), atof(userInput[2].c_str()), atof(userInput[3].c_str())));
}
*/


