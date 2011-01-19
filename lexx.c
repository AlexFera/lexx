/* 
 *  Copyright (C) 2011 <alexnadrufera at gmail dot com>
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

#define MAXBUF	256
#define	LEN	7	/* Lungimea maxima a unui cuvant cheie */

/* Manual lexical analysis */
void lexical_analysis(FILE *input_file, char current_character)
{
	char 		token_characters[MAXBUF];		
	unsigned int  	length = 0;		
	unsigned int  	i = 0;
	unsigned int	j = 1;	
	short 		is_keyword = 0;			
	int 		number = 0;
	const char 	keywords[][LEN] = {"break", "char", "const", "do", 
		                          "double", "else", "float", "for",
					  "if", "int", "return", "void", 
					  "while"}; 
	const char 	operators[] = {"!%&*-+=~|.<>/?"};
	const char 	separators[] = {";,{}()[]}"};
	char		buffer[MAXBUF];
	
	/* Consume white space and new lines */
	is_keyword = 0;
	while(isspace(current_character) || current_character == '\n')
		current_character = fgetc(input_file);

	if(isalpha(current_character)) {
		while(isalpha(current_character) || 
				isdigit(current_character)) {
			token_characters[length++] = current_character;
			current_character = fgetc(input_file);
		}
		token_characters[length++] = '\0';
		
		/* testing for keyword */
		for(i = 0; i < 13; i++) {
			if(strcmp(keywords[i], token_characters) == 0) {
				printf("%s\t este cuvant cheie\n",
					       	token_characters);
				is_keyword = 1;
				ungetc(current_character, input_file);
				return;
			}
		}
		if(is_keyword == 0) {
			printf("%s\t este identificator\n", 
					token_characters);
			ungetc(current_character, input_file);
			return;
		}
	}
	else
		
		if(isdigit(current_character)) {
			/* Numeric constant */
			while(isdigit(current_character)) {
				number = number * 10 + 
					atoi(&current_character);
				current_character = fgetc(input_file);
			}
			printf("%d\t este o constanta intreaga\n", number);
			ungetc(current_character, input_file);
			return;
		}
		else
			
			/* Testing for operators */
			for(i = 0; i < 14; i++)
				if(current_character == operators[i]) {
					printf("%c\t este operator\n", 
						       current_character);
				       	return;
				}
	
	for(i = 0; i < 10; i++)
		if(current_character == separators[i]) {
			printf("%c\t este semn de punctuatie\n", 
					current_character);
			return;
		}
	
	if(current_character == '"') {
		do {
			current_character = fgetc(input_file);
			buffer[j++] = current_character;
		}while(current_character != '"');
		buffer[j] = '\0';
		buffer[0] = '"';
		printf("%s este constanta sir de caractere\n", buffer);
	}

}

int main(int argc, char **argv)
{
	const char 	*filename;
	FILE 		*input_file;
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

	while((current_character = fgetc(input_file)) != EOF)
		lexical_analysis(input_file, current_character); 
	
	fclose(input_file);
	
	return(0);
}
