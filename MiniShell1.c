#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

 char** inputForExec(char* ptr, int stringLength,int count);

int main() {
//    uid_t uid =0;//choose the user
    int commandLength =0;//total length of command without spaces
    int space = 0;//number of spaces before the command
    char input[150];
    int count = 1; //counts the number of commands inserted
    int charCount = 0;//counts the number of char of the commands inserted
        int j = 0;
        struct passwd *p;
        p = getpwuid(getuid());
        int PATH_MAX=150;
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {//user and directory ready, user input wanted

        if ((getpwuid(getuid())) == NULL)//failed to find the user, insert as user null
        printf("null @%s>",  cwd );

        else  printf("%s@%s>", p->pw_name, cwd );//user is determined and directory is ready
            fgets(input,512,stdin);
            while (input[0]== ' ') {//removing spaces before the command + counting them
                for (j = 0; j < strlen(input); j++)
                input[j] = input[j + 1];

                space++;
            }
            int result= 100;
            if(input[0]=='d'&& input[1]=='o'&& input[2]=='n'&&input[3]=='e')//determining if the input is "done", if so script is terminated
                result = 0;

            int stringLength = strlen(input);

            while (result != 0)//continueS entries until "done"

            {
                char *ptr = malloc(strlen(input) * sizeof(int));//pointer to allocated memory where input is saved with words length instead of spaces in between

                if (!ptr)// exit the program immediately if there is no enough memory.
                {
                    printf("malloc failed\n");
                    exit(0);
                }
                char *ptr1 = ptr;
                int startPoint = 0; // start reading point after each word passed over
                int counter = 0; //counts the number of words passed over
                int length = 0;//length of each word passed over
                if (result == 0)//if input is "done, script terminated
                    exit(0);
                else if (result != 0) {//input not "done", more commands to be inserted
                    int i;

                    int stringLength = strlen(input);
                    int length1 = 0;

                    for (i = 0; i < strlen(input); i++) {//loops over the sentence until end
                        if (input[i] != ' ' && input[i] != '\n')//increment length between spaces or new line
                            length++;

                        if (input[i] == ' ' || i == stringLength - 1 || input[startPoint] == '\n' ||
                            input[startPoint] ==
                            '\t') {//conditions of the competence of a full word to be passed to temp array
                            int loop;

                            char temp[strlen(input)];
                            for (loop = 0;
                                 input[startPoint] != '\t' && input[startPoint] != '\n' && input[startPoint] != ' ' &&
                                 input[startPoint] != '\0' && startPoint != stringLength -
                                                                            1; loop++) {//passing the elements of the temp array into the allocated array until one of the conditions is not met

                                temp[loop] = input[startPoint];

                                startPoint = startPoint + 1;

                            }
                            while (input[i] == ' ' && i < stringLength &&
                                   input[i + 1] == ' ') {//skipping multiple spaces in a row in sentence
                                startPoint++;
                                i++;

                            }

                            length1 = length1 + length;//overall length of string inside allocated memory

                            if (loop != 0) {//in case string added to temp array, updates on variables takes place
                                startPoint++; //steps over a single space
                                strcpy(ptr1, temp);//adding word to allocated memory
                                ptr1 = ptr + length1 + counter;//re-allocating the pointer
                                counter++;
                                char lengthString[510];
                                sprintf(lengthString, "%d", length);
                                strcpy(ptr1, lengthString);
                                ptr1 = ptr + length1 + counter;
                            }
                            charCount = charCount + length;
                            length = 0;

                        }

                    }


                }
                commandLength = commandLength + strlen(input)-1 ;
                char **command = inputForExec(ptr, strlen(input), count);//preparing command to be inserted to execvp()
                int pid = fork();//starting a parent and child processes
                if (pid < 0) {//incase of failure of starting child process
                    perror("fork() error");
                    return 1;
                } else if (pid == 0) {//child process number 1 to run
                    if (strcmp(command[0], "cd") == 0)//exception for "cd"
                        printf("command not supported (Yet)\n");
                    else {
                        execvp(command[0], (char *const *) command);//executing the input command
                        perror("command not found\n");
exit(0);
                    }
                } else {//parent process number1
                wait(NULL);//wait for child process to finish for output arrangements
                for (int w = 0; w < sizeof(command) - 1 && command[w] != NULL; w++) {//freeing command array of pointers to strings
                    command[w] = NULL;
                }
//free rest of pointers
                free(command);
                count++;
                ptr1 = ptr;
                free(ptr1);
                ptr = NULL;
                //preparing command line again and input from user(like the beginning of the code)
                struct passwd *p;
                p = getpwuid(getuid());
                int PATH_MAX = 150;
                char cwd[PATH_MAX];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {//user and directory ready, user input wanted
                    if ((getpwuid(getuid())) == NULL)//failed to find the user
                        printf("null @%s>", cwd);

                    else printf("%s@%s>", p->pw_name, cwd);
                    fgets(input, 512, stdin);
                    while (input[0] == ' ') {
                        for (j = 0; j < strlen(input); j++)
                            input[j] = input[j + 1];
                        space++;
                    }
                    result = 100;
                    if (input[0] == 'd' && input[1] == 'o' && input[2] == 'n' && input[3] == 'e')
                        result = 0;
                } else {
                    perror("getcwd() error");
                    return 1;
                }

            }
            }



        } else {//incase no directory found, an exception appears
            perror("getcwd() error");
            return 1;
        }
//    }
int counter;
        int add =0;//counter of spaces after the command
        for(counter=0; counter<strlen(input); counter++){
            if (input[counter]==' ')
                add++;
        }

    printf("Num of commands: %d\n", count);
    printf("Total length of all commands: %d\n", commandLength +4 + add+space);
    double average = (charCount+4)/count;
    printf("Average length of all commands: %f\n", average);
    printf("See You Next Time !\n");
    exit (0);
    return 0;
}

 char**  inputForExec(char* ptrr, int stringLength,int count){//this function processes the input for it to be used as input for execvp() function
                int k =0;
                int t =0;
                int j;
                char commandTemp[150];
                char**  command = malloc(count * sizeof(int));//allocating memory for pointers to strings of fixed command
     if (!command)// exit the program immediately if there is no enough memory.
     {
         printf("malloc failed\n");
         exit(0);
     }
                for (j = 0; j < stringLength; j++) {//loops until the end of the first word;

                    while (ptrr[j]== ' '){//shifts to the first filled element of "input"
                        j++;
                    }
                    if (ptrr[j] >= '0' && ptrr[j] <= '9') {//a number found, a word is completed
                        commandTemp[t] = '\0';//null is added to the end of the commandTemp
                        command[k] =  malloc(t * sizeof(char));//memory allocated for the word
                        strcpy(command[k] ,commandTemp);//the word added to the allocated memory
                        t=0;
                        k++;
                        if(ptrr[j+1] == '\0'){//if it is the las word then a null is added to the next element

                         command[k] =NULL;
                        }
                        if (ptrr[j+1] >= '0' && ptrr[j+1] <= '9') {

                            j++;
                        }
                    } else {//incase no number found, the word is not completed and chars are added to commandTemp
                        commandTemp[t] = ptrr[j];
                        t++;
                    }


                }


                return command;

}
