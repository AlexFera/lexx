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

/* Analiză lexicală manuală */
void lexical_analysis(FILE *input_file, char current_charcter, FILE *output_file)
{
	char token_charcters[256];		/* tablou de carctere unde sunt depuse dupa *
       						* caz caracterele componente ale atomului curent*/
	unsigned int  length = 0;		/* variabilă contor */
	unsigned int  i = 0;			/* variabilă contor */
	short is_keyword = 0;			
	int number = 0;				/* constanta întreagă */
	const char keywords[][13] = {"break", "char", "const", "do", "double", 
		"else", "float", "for", "if", "int", "return" , "void", "while"}; 
	const char operators[] = {"!%&*-+=~|.<>/?"};
	const char separators[] = {";,{}()[]}"};
	
	/* Parcurgere cod sursă până la întâlnirea
	 * unui carcter diferit de spatiu alb */
	is_keyword = 0;
	while(current_charcter == ' ' || current_charcter == '\n')
		current_charcter = fgetc(input_file);

	/* Clasificare carcter si prelucrare atom */
	if(isalpha(current_charcter)) {
		/* Prelucrează identificator sau cuvânt cheie */
		
		while(isalpha(current_charcter) || isdigit(current_charcter)) {
			token_charcters[length++] = current_charcter;
			current_charcter = fgetc(input_file);
		}
		token_charcters[length++] = '\0';
		/* testăm dacă este cuvânt cheie */
		for(i = 0; i < 13; i++) {
			if(strcmp(keywords[i], token_charcters) == 0) {
				fprintf(output_file, "%s \t\t\teste cuvant cheie\n", token_charcters);
				is_keyword = 1;
				break;
			}
		}
		if(is_keyword == 0) 
			fprintf(output_file, "%s \t\t\teste idenfificator\n", token_charcters);
	}
	else
		if(isdigit(current_charcter)) {
			/* Prelucrează constantă numerică */
			while(isdigit(current_charcter)) {
				number = number * 10 + atoi(&current_charcter);
				current_charcter = fgetc(input_file);
			}
			fprintf(output_file, "%d \t\t\teste un numar\n", number);
		}
		else
			/* Altfel este operator */
			for(i = 0; i < 14; i++)
				if(current_charcter == operators[i]) 
					fprintf(output_file, "%c \t\t\teste un operator\n", current_charcter);
	for(i = 0; i < 10; i++)
		if(current_charcter == separators[i]) {
			fprintf(output_file, "%c \t\t\teste un semn de punctuatie\n", current_charcter);
			break;
		}
	if(current_charcter == '"') {
		do {
			current_charcter = fgetc(input_file);
			fprintf(output_file, "%c", current_charcter);
		}while(current_charcter != '"');
		fprintf(output_file, "\t\teste un sir de caractere\n");
	}
}

int main(int argc, char **argv)
{
	const char *filename;
	FILE *input_file;
	FILE *output_file;
	char current_charcter;

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
	
	while((current_charcter = fgetc(input_file)) != EOF)
		lexical_analysis(input_file, current_charcter, output_file);
	
	fclose(input_file);
	fclose(output_file);
	
	return 0;
}
