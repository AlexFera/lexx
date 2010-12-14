#ifndef LEX_H
#define LEX_H

typedef enum 
{
	IDENTIFIER,
	KEYWORD,
	NUMBER,
	OPERATOR,
	PUNCTUATION,
	DELIMITER,
	STRING
} type; 

typedef struct  
{
	int 	value;
	char	*name;
	type	code;
} token;

#endif
	
