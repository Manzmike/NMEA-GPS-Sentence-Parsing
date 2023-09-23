#include <iostream>
#include <wiringPi.h>
#include <csignal>
#include <string>
#include <sstream>

#include "Sentences.h"

using namespace std;

finder::finder(string s)									// constructor
{
	to_find = s;											// setup string to find in incoming characters
	State = Dollar;
	newdata="";
	data="";											// set initial state to "None"
}

finder::~finder()			// destructor
{

}

 // Blink an LED
void blink_led_on(int led) {
    digitalWrite(led, HIGH);
}

void blink_led_off(int led) {
    digitalWrite(led, LOW);
}

void finder::find(char c)
{
	int i;
	int SIZE;
	string temp;




    wiringPiSetupGpio();
	pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);




	//checking for the dollar sign of a state each time through and if dollar is reached
	//then the code will transation to the next state of Type_1
	
		if(State == Dollar || c == '$'){
				State=Type_1;
				
				Message_type="";
				newdata="";
				Checksum="";


		}

	//checking of state one of the 5 types from this point if c == to_find[0]
	//code would tranation to the next type 
	//else if c!= to_find then the state goes back to state one 
	//message contatation is added on to as the proceedure is gone through

		else if(State == Type_1 ){

			if(c == to_find[0]){
				this->Message_type+=c;
				State=Type_2;	
			}
			else if(c != to_find[0]){
				State = Type_1;
			}
			
		}

	//checking of state one of the 5 types from this point if c == to_find[0]
	//code would tranation to the next type 
	//else if c!= to_find then the state goes back to state one 
	//message contatation is added on to as the proceedure is gone through

		else if(State == Type_2 ){
		
			if(c == to_find[1]){
				this->Message_type+=c;
				State=Type_3;	
			}
			else if(c != to_find[1]){
				State = Type_1;
			}
			
		}
	//checking of state one of the 5 types from this point if c == to_find[0]
	//code would tranation to the next type 
	//else if c!= to_find then the state goes back to state one 
	//message contatation is added on to as the proceedure is gone through

		else if(State == Type_3 ){

			if(c == 'G' || c == 'R'){
				//cout<<"Going to Type 4"<<endl;

				this->Message_type+=c;

				State=Type_4;
				
			}
			else if(c != 'G' || c != 'R'){
				State = Type_1;
			}
			
		}
	//checking of state one of the 5 types from this point if c == to_find[0]
	//code would tranation to the next type 
	//else if c!= to_find then the state goes back to state one 
	//message contatation is added on to as the proceedure is gone through
		else if(State == Type_4 ){
			
			if(c == 'G' || c == 'S'|| c == 'M'){
				this->Message_type+=c;
				State=Type_5;
				
			}
			else if(c != to_find[3]){
				State = Type_1;
			}
			
		}
	//checking of state one of the 5 types from this point if c == to_find[0]
	//code would tranation to the next type 
	//else if c!= to_find then the state goes back to state one 
	//message contatation is added on to as the proceedure is gone through
	//from this point as well the leds are all inalized and turned off to start	
	// if GPGGA or GPRMC is the message then output is green
	// if GPGSA is the message then output is yellow
	//else then the output is red in any case

		else if(State == Type_5 ){
			
			if(c == 'A' || c == 'V'|| c == 'C'){
				this->Message_type+=c;
				State = Data;
			}
			else if(c != to_find[4]){
				State = Type_1;
			}

			blink_led_off(green);
 			blink_led_off(yellow);
 			blink_led_off(red);

 			if(this->Message_type=="GPGGA" || this->Message_type=="GPRMC"){
 			blink_led_on(green);
 			delay(500);
 			}

 			else if(this->Message_type=="GPGSA"){
 			blink_led_on(yellow);
 			delay(500);
 			}

 			else {
 			blink_led_on(red);
 			delay(500);
 			}

			this->data="";
			this->newdata="";
		}

		
		// the data is alwasy checking for the dollar sign.
		// if the dollar fisn is found then the datat is removed
		//if the star is could then the data is stoped to be proceeded 
		// then the next state of check sum is started
		// the data is alway adding onto the string 
		else if(State == Data){

			if(c == '$'){
				
				this->Message_type="";
				this->Checksum="";
				State = Type_1;
			}
			if(c =='*'){
				this->newdata=data;
				this->data="";
				State = Check_Sum1;
				//cout<<"Going to Check_sum1"<<endl;
			}
			
			else{
			this->data+=c;
			}
		}


		//from this is just gets the data for the first value and sets it to the string

		else if(State == Check_Sum1){

			this->Checksum+=c;		
			State=Check_Sum2;
			

		}
		//from this is just gets the data for the second value and sets it to the string
		// going along the string stream is taken to take the hex value and make it intp
		//the sting stream in made intoa var
		// the var is compared witht the checksum
		// the checksum is caluclated by the eqaution of ORing each data with
		// the total amount giving us our total for our checksum
		//from that point if the data is correct it is outputted
		// then the data is then set to null to end.
		else if(State == Check_Sum2){
			this->Checksum+=c;
			stringstream cs;
			string temp;
			unsigned int check_sum=0;

			string Total = Message_type + newdata;
			for(int i=0;i<Total.length();i++){
				check_sum^=Total[i];

			}
			cs << uppercase << hex << check_sum;
			cs >> temp;			

			if (temp == Checksum)
			{
				cout<<endl<<"Message type:"<<Message_type<<endl;
				cout<<"Message Data:"<<Total<<endl;
				cout<<"Message Checksum:"<<Checksum<<endl;
			}

			Message_type="";
			newdata="";
			Checksum="";
			State=Dollar;
		}
		
	}
					

	

