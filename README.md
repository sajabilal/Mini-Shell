# Mini-Shell
the program is a mini shell, it uses the previous project "String parsel" to arrange and collect info about the input and then takes it through a process where it prepares it for execution using execvp() function. 
using "string Pracel" allows us to get the command allocated in the memory with words lengths instead of spaces. 
then the allocated chars are transformed into strings saved in arrays with each having its own pointer. 
pointers are saved in an array of pointers allocated in the memory. 
the array data is then used as input for execvp() function which runs the saved command as data of the allocated array into the shell.
by typing "done", the script is terminated and needed data is printed to the screen. 

==Description of MiniShell2.c==

same as MiniShell1.c but with additional data added to the screen about the command which has been run by the user, using cat /proc/<PID>/sched
