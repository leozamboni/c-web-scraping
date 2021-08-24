/*
 * Web Scraping C 
 * Copyright © 2021 Leonardo Zamboni
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 * 
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 * 
 * you should have received a copy of the gnu general public license
 * along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "scraping.h" 

Queue *create_queue(void) 
{
	Queue *q = (Queue *) malloc(sizeof(Queue));
  	q->f = q->b = NULL;
  	return q;
}

void push_queue(Queue *q, char c) 
{
  	Node *new = (Node *) malloc(sizeof(Node));
  	new->c = c;
  	new->n = NULL;
  	if (!q->f) q->f = new;
  	else q->b->n = new;
  	q->b = new;
}

void output_queue(Node *f) 
{
  	if (!f) return;
  	printf("%c",f->c);
  	output_queue(f->n);
}

uint16_t count_nodes(Node *f) 
{
  	if (!f) return 0;
  	return 1 + count_nodes(f->n);
}

char *get_str(Node *f) 
{
  	char *str = (char *) malloc((count_nodes(f) + 1) * sizeof(char));
  	
	size_t i;
  	for (i = 0; f; f = f->n, ++i) 
	{
    		str[i] = f->c;
	}

 	str[i+1] = '\0';
  	return str;
}

void get_file(char *argv) 
{
  	char *cmd = (char *) malloc(strlen(CURL) + strlen(argv));

  	strcat(strcpy(cmd,CURL),argv);

	system(cmd);

	free(cmd); 
}

char *get_block(WSCONF conf) 
{
	Queue *src_q = create_queue();

	FILE *fl = fopen("source.html", "r");
	if (!fl) exit(EXIT_FAILURE);

	char c;
	while (c != EOF)
	{
		c = getc(fl);

		if (c == conf.start_block[0])
		{
			size_t i = 0;
			for (i = 1; i < strlen(conf.start_block); ++i) 
			{
				c = getc(fl);
				if (c != conf.start_block[i]) break;
			}

			if (i == strlen(conf.start_block)) 
			{
				while (c != EOF)
				{
					c = getc(fl);

					size_t j = 0;
					if (c == conf.end_block[0])
					{
						for (j = 1; j < strlen(conf.end_block); ++j) 
						{	
							c = getc(fl);

							if (c != conf.end_block[j]) break;
						}
					}
					if (j == strlen(conf.end_block)) break;

					push_queue(src_q, c);
				}

				push_queue(src_q, '\n');
			}
		}
	}

	fclose(fl);
	
	remove("source.html");
	
  	return get_str(src_q->f);   
}
