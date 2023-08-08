//This is a shell that will have a bunch of random functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//This function will get input from the user.
char *getInput() {
  char *buffer;
  size_t bufsize = 32;
  size_t characters;
  characters = getline(&buffer, &bufsize,stdin);
  return buffer;
}

//This function will execute the command.
void exe(char *strarr[]){

  //Forking will allow me to run the main process after I run the execvp command
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "\n fork failed \n");
    exit(1);
  } 
  else if (rc == 0) {
// child (new process)
    if(execvp(strarr[0], strarr) == -1){
	printf("execvp error!\n");
	exit(1);
    }
  }
  else{
    wait(NULL);
  }
}

//This function will tokenize the string.
void tokenizer3000(char *buffer, char *strarr[]){
  int i = 0;
  const char *dlimitter = " \t\r\n\a";
  
  char* toke = strtok(buffer, dlimitter);
  strarr[i] = strdup(toke);

  //While loop to create an array with the tokens
  while(toke != NULL){
    i++;

    toke = strtok(NULL,dlimitter);
    strarr[i] = toke;
    }
  strarr[i + 1] = NULL;
}

//This is the function where I will run all of this code.
int main(){
  char **strarr = malloc(16 * sizeof(char*));

  //While loop for main shell function.
  while(1){
    printf("<3: ");
    *strarr = realloc(strarr, 16*sizeof(char*));
    tokenizer3000(getInput(), strarr);

    //If statement to exit the loop 
    if (strcmp(strarr[0], "exit") == 0){
      free(strarr);
      exit(1);
  }
    exe(strarr);
  }
  //Frees the array
  free(strarr);
  return 0;
}
