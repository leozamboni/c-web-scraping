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

uint8_t is_tag(FILE *fl, char *str, char c) 
{
	if (*str == '\0') return 1;

	if (c != *str++ || c == EOF) return 0;
	 
	return is_tag(fl, str, getc(fl));
}

char get_block(WSCONF cnfg, FILE *getfl, Queue *srcq, char c)
{
	if (c == EOF || is_tag(getfl, cnfg.end_block, c)) return c;

	if (cnfg.enable_print) putchar(c);

	push_queue(srcq, c);

	return get_block(cnfg, getfl, srcq, getc(getfl));
}

char *get_source(WSCONF cnfg) 
{
  	Queue *srcq = create_queue();
  	FILE *getfl;

  	getfl = fopen(HTML_PAGE,"r");
  	if (!getfl) return NULL;

	char c;
    	while (c != EOF) 
	{
		c = getc(getfl);

      		if (is_tag(getfl, cnfg.start_block, c)) 
		{
			get_block(cnfg, getfl, srcq, getc(getfl));
			
			push_queue(srcq,'\n'); 

			if (cnfg.enable_print) puts("");
      		}
    	}

  	fclose(getfl);

  	remove(HTML_PAGE);

  	return get_str(srcq->f);   
}
