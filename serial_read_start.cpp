//******************************************************************
// Program #: Reading from serial port
//
// Programmer: Matthew Gelber/Robert Klenke
//
// Due Date: NA
//
// EGRE 347, Fall 2020       Instructor: Robert Klenke
//
// Pledge: I have neither given nor received unauthorized aid on this program.
//
// Description: C++ example for reading information from serial port one byte at a time
//
// Input: command line argument of the desired serial port
//
// Output: none
//
//******************************************************************

#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <fstream>

#include "Sentences.h"

using namespace std;

const string TYPE1("GP");

int main(int argc, char *argv[])
{
	//create insteacne of class
	//unsigned char read_buff;
	
	char read_buff;
	finder find(TYPE1);



	
	cout << argv[1] << endl;
	int sp = open(argv[1], O_RDONLY | O_NOCTTY | O_NDELAY);	//opens the serial port inputted as argument as read only
	



	if(sp < 0)
		cout << "unable to open port " << argv[1] << endl;
	else
		cout << "port successfully opened" << endl;


	while(true){
		//reads from port one bit at a time
		int n = read(sp, &read_buff, sizeof(read_buff));

		if(n>0)
		{
			//the read_buff is gone through and taken through the object
			//it goes through a essentiall forever loop until broken
			//cout<<"read_buff:"<<read_buff<<endl<<endl<<"N: "<<n<<endl<<endl;
			find.find(read_buff);
		}


	}

		
		
	close(sp);
}
