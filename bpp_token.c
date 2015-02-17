//
//	Practice file for strtok implementing rules from Minor Assignment 4 csce 3600
//
//	Created by: Michael Hinderman
//	Date: 02/14/15
//
//
//	Notes: I have realized that strtok will be helpful for dealing with spaces.
//			I do run into the issue of there being no spaces between words.
//			This program does not deal with the issue of no spaces around brackets
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

	// Get contents of file into a buffer

	// File handle
	FILE *bashfile;
	// set file pointer to first argument
	bashfile=fopen(argv[1], "r");

	// if the file failed to open
	if (bashfile == NULL)
	{
		printf("ERROR opening file");
		return 1;
	}

	// obtain the size of the file for buffer allocation
	// go to the end of the file

	// set buffer
	char *buffer = NULL;

	// if fseek was successful
	if(!(fseek(bashfile, 0, SEEK_END)))
	{
		// get the size of the file
		int size = ftell(bashfile);
		//printf("File Size: %d\n", size);

		// allocate buffer of file size
		buffer = malloc(size+1 * sizeof(char));

		//move file pointer to the begining of the file
		// if fseek failed
		if(fseek(bashfile, 0, SEEK_SET))
		{
			printf("ERROR moving to front of file\n");
			free(buffer);
			return 1;
		}

		// read file into buffer
		size_t buffLength = fread(buffer, sizeof(char), size, bashfile);
		if(!buffLength)
			printf("ERROR reading from file",stderr);
		else
			buffer[++buffLength] = '\0';
	}


	//	strtok functions start here

	
	// set character pointer for each token
	char *token;
	// token function that does the magic
	token = strtok(buffer, " \n\t\0");

	// set what command is active at a time
	int comActive = 0;

	
	// This while loop will traverse the buffer created above
	while(token != NULL)
	{
		// if a token is called "echo" or echo related
		if (strcmp(token,"echo") == 0 || comActive == 1 )
		{
			// echo command is active
			comActive = 1;
			// if token is called "echo"
			if (!strcmp(token,"echo"))
			{
				// print echo to output
				printf("\necho ");
				// move to next token
				token = strtok(NULL, " \n\t");
			}
			// if token starts with "$"
			else
			{
				// if token starts with '$'
				if(token[0] == '$')
				{
					// print "$" to output
					printf("%s ", token);
					// move to next token
					token = strtok(NULL, " \n\t");
				}
				// if token starts with '"'
				else if(token[0] == '"')
				{
					// quotation variable to keep track of quotes
					int quo = 1;
					while(quo < 2)
					{
						// if last element of token is '"'
						if(token[strlen(token)-1]=='"')
						{
							// print token to output
							printf("%s ", token);
							// increase quote by one
							quo++;
							// move to next token
							token = strtok(NULL, " \n\t");
						}
						// else
						else
						{
							// print token to output
							printf("%s ", token);
							// move to next file
							token = strtok(NULL, " \n\t");
						}
					}
				}
				else
				{
					// print new line
					printf("\n");
					// echo command no longer active
					comActive = 0;
				}
			}
		} // end echo if
		// if token is equal to "if" or if command active
		else if(strcmp(token,"if") == 0 || comActive == 2)
		{
			// activate if command
			comActive = 2;
			// if token is equal to "if"
			if(!strcmp(token,"if"))
			{
				// print if to output
				printf("\nif ");
				// move to next token
				token = strtok(NULL, " \n\t");
			}
			else
			{
				// if token is '['
				if(token[0] == '[')
				{
					// bracket variable for tracking
					int brak = 1;
					while(brak < 2)
					{
						// if token equals ']'
						if (token[0] == ']')
						{
							// print token to output
							printf("%s\n", token);
							brak++;
							// move to next token
							token = strtok(NULL, " \n\t");
						}
						else
						{
							// print token to output
							printf("%s ", token);
							// move to next token
							token = strtok(NULL, " \n\t");
						}
					}
				} 
				else
				{
					// if command no longer active
					comActive = 0;
				}
			}
		}
		// if anything else
		else
		{
			// print token to output
			printf("%s\n", token);
			// move to next token
			token = strtok(NULL, " \n\t");
		}
	}


	fclose(bashfile);
	free(buffer);
	return 0;
}
