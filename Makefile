prog1.exe : serial_read_start.o Sentences.o
	g++ serial_read_start.o Sentences.o -lwiringPi -o prog1

serial_read_start.o : serial_read_start.cpp Sentences.h
	g++ -c serial_read_start.cpp

Sentences.o : Sentences.cpp Sentences.h 
	g++ -c Sentences.cpp 

clean :
	rm *.o
	rm prog1
