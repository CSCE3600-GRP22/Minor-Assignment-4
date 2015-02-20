/*
Andrew Turner
Christopher Beasly
Dustin Eaton
Michael Hinderman

Sweany
CSCE 3600

Purpose is to get rid of a few quirks that bash has
with whitespace. Specifically with assignment statements
and if, while, until statements.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int getPos(char *buffer, int x, int i){
  //necessary variables to check and count
  int check = 0;
  int pCount = 0;
  //increments i so that you wont be on the equals
  i+=x;
  //loop to find the position of the start and end
  do{
    //if the buffer equal a whitespace increment i
    if(buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t'){
      i+=x;
    //otherwise send the program into the part that checks for the variable or constant
    }else{
      //set check to one so that the program knows that a character other than whitespace
      //has been encountered
      check = 1;
      //do loop to loop through either side of the variable
      do{
        //if there are quotes or parenthasese increase pcount and move the counter
        if(buffer[i] == '(' || buffer[i] == '\'' || buffer[i] == '\"'){
          pCount += x;
          i+=x;
        //else if there is the counterpart to those decrement the pCount and move the counter
        }else if(buffer[i] == ')' || buffer[i] == '\'' || buffer[i] == '\"'){
          pCount -= x;
          i+=x;
        //else if there is whitespace and pCount is 0 break and return the counter
        }else if(buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t'){
          if(pCount == 0){
            break;
          //else increment the counter
          }else{
            i+=x;
          }
        //else increment the counter
        }else{
          i+=x;
        }
      //checks to see if you need to break the loop
      }while((buffer[i] != ' ' || buffer[i] != '\n' || buffer[i] != '\t') && pCount == 0);
    }
  //if check isnt 0 stop
  }while(check == 0);
  //return i-x so that you avoid the whitespace between the two
  return i-x;
}
int assignmentParser(char *buffer, int equalPos){
  //necessary variables, including the start and end position of the buffer
  int start, end;
  int i, j = 0, pCount = 0;
  char *printBuffer;
  char *correctBuffer;
  //create space of 300 characters for the buffers
  printBuffer = malloc(300*sizeof(char));
  correctBuffer = malloc(300*sizeof(char));
  //find the positions in the buffer
  end = getPos(buffer, 1, equalPos);
  start = getPos(buffer, -1, equalPos);
  //copies the buffer over to the temporary buffer
  for(i = start; i < end; i++){
    printBuffer[j] = buffer[i];
    j++;
  }
  //make sure the temp buffer has a null at the end
  printBuffer[j] = '\0';
  //set both counters to 0
  i=0;
  j=0;
  //loop that creates the corrected buffer
  do{
    //checks if the position isnt white space
    if(printBuffer[i] != ' ' && printBuffer[i] != '\n' && printBuffer[i] != '\t'){
      //if so copy it to the correct buffer
      correctBuffer[j] = printBuffer[i];
      //also increment the pCount if necessary
      if(printBuffer[i] == '(')
        pCount +=1;
      else if(printBuffer[i] == ')')
        pCount -=1;
      i++;
      j++;
    //checks to see if there is any whitespace, if so ignore it
    }else if((printBuffer[i] == ' ' || printBuffer[i] == '\n' || printBuffer[i] == '\t') && pCount == 0){
      i++;
    //else copy it to the correct buffer
    }else{
      correctBuffer[j] = printBuffer[i];
      i++;
      j++;
    }
  //runs until it reaches the null character
  }while(printBuffer[i] != '\0');
  //prints the corrected buffer
  printf("\n%s", correctBuffer);
  free(printBuffer);
  free(correctBuffer);
  //returns the end position back to the parser
  return end;
}
int iwuParser(char *buffer, int startPos){
  //necessary counters, and on off integers
  //also declares the temporary buffers
  //one for reading and the other for modification
  int i, j, k = 0;
  int pNum = 0, bNum = 0, bracket = 0, ifso = 0;
  char *printBuffer;
  char *correctBuffer;
  printBuffer = malloc(300*sizeof(char));
  correctBuffer = malloc(300*sizeof(char));
  //sets i to the starting position that it needs to be in the
  //buffer
  i = startPos;
  //while loop that copies the buffer to the temporary buffer
  printf("\n");
  while(buffer[i] != '\n'){
    printBuffer[k] = buffer[i];
    i++;
    k++;
  }
  //saves k for the return
  k = i;
  //adds a new line character to the end
  //printBuffer[i+1] = '\n';
  //set counters to 0
  i = j = 0;
  //do loop for the modification of the buffer
  do{
    //checks for the until statement, if so it writes it to the modified buffer
    //along with a space, then moves the counters past those positions. This should
    //only occur once
    if(printBuffer[i] == 'u' && printBuffer[i+1] == 'n' && ifso == 0){
        correctBuffer[j] = printBuffer[i];
        correctBuffer[j+1] = printBuffer[i+1];
        correctBuffer[j+2] = printBuffer[i+2];
        correctBuffer[j+3] = printBuffer[i+3];
        correctBuffer[j+4] = printBuffer[i+4];
        if(printBuffer[i+5] == ' '){
          correctBuffer[j+5] = printBuffer[i+5];
          j+=6;
        }else{
          correctBuffer[j+5] = ' ';
          j+=6;
        }
        i+=4;
        ifso = 1;
      }
      //checks for the while statement, if so it writes it to the modified buffer
      //along with a space, then moves the counters past those positions. This should
      //only occur once
      else if(printBuffer[i] == 'w' && printBuffer[i+1] == 'h' && ifso == 0){
          correctBuffer[j] = printBuffer[i];
          correctBuffer[j+1] = printBuffer[i+1];
          correctBuffer[j+2] = printBuffer[i+2];
          correctBuffer[j+3] = printBuffer[i+3];
          correctBuffer[j+4] = printBuffer[i+4];
          if(printBuffer[i+5] == ' '){
            correctBuffer[j+5] = printBuffer[i+5];
            j+=6;
          }else{
            correctBuffer[j+5] = ' ';
            j+=6;
          }
          i+=4;
          ifso = 1;
        }
        //checks for the if statement, if so it writes it to the modified buffer
        //along with a space, then moves the counters past those positions. This should
        //only occur once
        else if(printBuffer[i] == 'i' && printBuffer[i+1] == 'f' && ifso == 0){
            correctBuffer[j] = printBuffer[i];
            correctBuffer[j+1] = printBuffer[i+1];
            if(printBuffer[i+2] == ' '){
              correctBuffer[j+2] = printBuffer[i+2];
              j+=3;
            }else{
              correctBuffer[j+2] = ' ';
              j+=3;
            }
            i+=1;
            ifso = 1;
          }
      //checks the read buffer for the opening bracket
      //if it is there input it into the modified
      //buffer and move the counters the correct amount
      else if(printBuffer[i] == '['){
      correctBuffer[j] = '[';
      bracket = 1;
      bNum += 1;
      correctBuffer[j+1] = ' ';
      j+=2;
      //does the same thing as above but with parenthasese
    }else if(printBuffer[i] == '('){
      correctBuffer[j] = printBuffer[i];
      bracket = 1;
      pNum += 1;
      correctBuffer[j+1] = ' ';
      j+=2;
    }
    //checks for a close bracket, if one exists
    //place it in the modified buffer and increment the counter
    else if(printBuffer[i-1] == ']'){
      bNum -= 1;
      correctBuffer[j] = ']';
      j++;
    }
    //does the same thing as above but with parenthasese
    else if(printBuffer[i] == ')'){
      pNum -= 1;
      correctBuffer[j] = ')';
      j++;
    }
    //this is the part of the loop that reads in the text inside the brackets
    //when it find texts, it continues until it finds whitespace or a bracket
    //it then places it inside of the modified buffer. Pretty simple copying
    //added a space at the end to allow for whitespace
    else if(printBuffer[i] != ' ' && printBuffer[i] != '\t'){
        while(printBuffer[i] != ' ' && printBuffer[i] != '\t' && printBuffer[i] != ']'){
          correctBuffer[j] = printBuffer[i];
          i++;
          j++;
        }
        correctBuffer[j] = ' ';
        j++;
    }
    i++;
    //if statement that checks whether the amount of brackets open equals
    //the amount of brackets close. This determines when to end the loop in most
    //cases.
    if((pNum == 0) && (bNum == 0) && (bracket == 1)){
      correctBuffer[j] = '\0';
      break;
    }
}while(i < 300);
  //[rints the corrected buffer to the output
  printf("%s", correctBuffer);
  i = startPos;
  //while loop that checks if the then is in the correct buffer
  while(buffer[i] != '\n'){
    if(buffer[i] == 't')
      if(buffer[i+1] == 'h')
        if(buffer[i+2] == 'e')
          if(buffer[i+3] == 'n'){
            printf("\n\tthen");
            break;
          }
    //also checks fo do
    if(buffer[i] == 'd')
      if(buffer[i+1] == 'o'){
        printf("\n\tdo");
          break;
          }
    i++;
  }
  free(printBuffer);
  free(correctBuffer);
  return k;
}
void copyAndPrint(char *buffer, int startPos, int endPos){
        //Counter and temporary buffer declared
        int i;
        char printBuffer[100];
        //loop that goes through and copies the contents of the buffer to the
        //temporary for quick printing
        for(i = 0; ((startPos + i) < (endPos)); i++)
          printBuffer[i] = buffer[startPos+i];
        //adds a null character to the end so we dont get random
        //characters that are weird and stuff
        printBuffer[i] = '\0';
        //prints the selected portion of the buffer
        printf("%s", printBuffer);
}
void parseBuffer(char *buffer){
        //all necessary variables
        int j, i = 0;
        int startPos = 0, endPos = 0;
        //while loop that goes until the end of the file
        while(buffer[i] != '\0'){
          //checks for if statement, if so it goes to the
          //if statement parsing function
          if(buffer[i] == 'i' && buffer[i+1] == 'f'){
             i = startPos = iwuParser(buffer, i);
            //increments by two so it bypasses the if
          }
          //checks for the while loop, if so it goes to the
          //while loop parsing function
          else if(buffer[i] == 'w' && buffer[i+1] == 'h' && buffer[i+2] == 'i'){
            if(buffer[i+3] == 'l' && buffer[i+4] == 'e'){
              i = startPos = iwuParser(buffer, i);
              //increments i by 5 to bypass the while
            }
          }
          //checks for the until loop, if so it goes to the
          //until loop parsing function
          else if(buffer[i] == 'u' && buffer[i+1] == 'n' && buffer[i+2] == 't'){
            if(buffer[i+3] == 'i' && buffer[i+4] == 'l'){
              i = startPos = iwuParser(buffer, i);
              //increments i by 5 to bypass the until
            }
          }
          //just calls the normal print function whenever
          //there is nothing to modify
          else if(buffer[i] == '\n'){
            endPos = i;
            copyAndPrint(buffer, startPos, endPos);
            i++;
            startPos = endPos;
          }
          else if(buffer[i] == '='){
            i = startPos = assignmentParser(buffer, i);
          }
          //else increment by one
          else{
            i++;
            }
          }
        return;
}
void parseFile(char *buffer, char **argv){
        //all the necessary variable declarations
        //including the FILE IO
        FILE *input;
        char c;
        int i = 1;
        int fileSize;
        //checks to see if the file you want to open exists
        if(access(argv[1], F_OK) != -1){
          //opens the file for reading
          input = fopen(argv[1], "r");
          //sends the offset to the very end of the file
          fseek(input, 0, SEEK_END);
          //gets the position of the end of the file
          fileSize = ftell(input);
          //goes back to the end of the file
          fseek(input, 0, SEEK_SET);
          //creates just enough space in the buffer in order to store
          //the data in the file
          buffer = malloc((fileSize+1)*sizeof(char));
          //reads in the file contents to the buffer
          fread(buffer, fileSize, sizeof(char), input);
          //closes the file
          fclose(input);
          //goes to the parsing section of the program
          parseBuffer(buffer);
          //frees the space of the buffer
          free(buffer);
        }
        else
          printf("File does not exist\n");
          //end program
        return;
}
int main(int argc, char **argv){
        //Creates the buffer that will store the whole program
        char *buffer;
        //checks to see if there are enough arguments
        if(argc > 1){
          //goes to the parse file function
          parseFile(buffer, argv);
        }
        //otherwise it ends the program
        else
            printf("Not enough arguments input\n");
        printf("\n\n");
        return 0;
}
