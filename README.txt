When starting the ptytest.py program, run it with "python3 ptytest.py <input_file_name>"

For example:

$ python3 ptytest.py gps1.log

The first line printed out will tell you which pseudoterminal to connect to in the .cpp program
ex: /dev/pts/<num>

To test the .cpp code, it setup for command line arguments. ex: ./prog1 /dev/pts/<num>
This will open the pseudoterminal and start reading from it one byte at a time.
