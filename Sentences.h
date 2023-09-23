using namespace std;

enum find_states{Dollar,Type,Type_1,Type_2,Type_3,Type_4,Type_5, Buffer, Data, Check_Sum1,Check_Sum2};

class finder
{
	private:
		enum find_states State;		// Holds current state the traffic light is in
		string to_find;			// string to find

		string Message_type;
		string Checksum;
		string data;
		string newdata;


		


		
	public:
		finder(string);				// Constructor
		
		~finder();					// Destructor
	
	
		void find(char c);			// Main implementation for the state machine

		void print();

		const int red = 24;
		const int yellow = 5;
		const int green = 16;
};
