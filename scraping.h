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
#ifndef SCRAPING_H
#define SCRAPING_H

#include <stdio.h>
#include <stdint.h>

#define HTML_PAGE "source.html"
#define CURL "curl --silent --output source.html "

typedef struct conf WSCONF;

struct conf {
  	char *start_block;
  	char *end_block;
  	uint8_t enable_print;
};

typedef struct node Node;

struct node {
  	char c;
  	Node *n;
};

typedef struct queue Queue;

struct queue {
  	Node *f;
  	Node *b;
};

/* Queue functions */
Queue *create_queue(void);
void push_queue(Queue *q, char c);
void output_queue(Node *f);
int count_nodes_queue(Node *f);
char *get_str(Node *f);

/* Scraping functions */
char *get_source(WSCONF cnfg);
void get_file(char *argv);

#endif
