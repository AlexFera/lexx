/* 
 *  Copyright (C) 2010 <alexnadrufera at gmail dot com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Manual lexical analysis */
void lexical_analysis(FILE *input_file, char current_character, FILE *output_file)
{
	char 		token_characters[256];		
	unsigned int  	length = 0;		
	unsigned int  	i = 0;			
	short 		is_keyword = 0;			
	int 		number = 0;				
	const char 	keywords[][13] = {"break", "char", "const", "do", "double", 
					  "else", "float", "for", "if", "int", "return" , 
					  "void", "while"}; 
	const char 	operators[] = {"!%&*-+=~|.<>/?"};
	const char 	separators[] = {";,{}()[]}"};
	
	
	is_keyword = 0;
	while(current_character == ' ' || current_character == '\n')
		current_character = fgetc(input_file);

	if(isalpha(current_character)) {
		while(isalpha(current_character) || isdigit(current_character)) {
			token_characters[length++] = current_character;
			current_character = fgetc(input_file);
		}
		token_characters[length++] = '\0';
		/* testing for keyword */
		for(i = 0; i < 13; i++) {
			if(strcmp(keywords[i], token_characters) == 0) {
				fprintf(output_file, "%s \t\t\teste cuvant cheie\n", token_characters);
				is_keyword = 1;
				break;
			}
		}
		if(is_keyword == 0) 
			fprintf(output_file, "%s \t\t\teste idenfificator\n", token_characters);
	}
	else
		if(isdigit(current_character)) {
			/* Numeric constant */
			while(isdigit(current_character)) {
				number = number * 10 + atoi(&current_character);
				current_character = fgetc(input_file);
			}
			fprintf(output_file, "%d \t\t\teste un numar\n", number);
		}
		else
			/* Testing for operators */
			for(i = 0; i < 14; i++)
				if(current_character == operators[i]) 
					fprintf(output_file, "%c \t\t\teste un operator\n", current_character);
	for(i = 0; i < 10; i++)
		if(current_character == separators[i]) {
			fprintf(output_file, "%c \t\t\teste un semn de punctuatie\n", current_character);
			break;
		}
	if(current_character == '"') {
		do {
			current_character = fgetc(input_file);
			fprintf(output_file, "%c", current_character);
		}while(current_character != '"');
		fprintf(output_file, "\t\teste un sir de caractere\n");
	}
}

int main(int argc, char **argv)
{
	const char 	*filename;
	FILE 		*input_file;
	FILE 		*output_file;
	char 		current_character;

	if(argc == 1) {
		printf("Introduceti numele fisierului ca parametru in " 
		       "linia de comanda\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	input_file = fopen(filename, "r");
	if(input_file == NULL) {
		printf("Fisierul nu exista!\n");
		exit(EXIT_FAILURE);
	}

	output_file = fopen("output.txt", "w+");
	if(output_file == NULL) {
		printf("Fisierul nu poate fi creat!\n");
		exit(EXIT_FAILURE);
	}
	
	while((current_character = fgetc(input_file)) != EOF)
		lexical_analysis(input_file, current_character, output_file);
	
	fclose(input_file);
	fclose(output_file);
	
	return 0;
}
