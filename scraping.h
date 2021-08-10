/*
 * Simple program for web scraping with C
 * (Leonardo Zamboni leozamboni.dev)
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
#include <stdbool.h>

#define SET_CURL

#define GET_FILE "get.txt"
#define SET_FILE "set.txt"

#ifdef SET_CURL  
  #define CURL "curl --output get.txt "
#endif

typedef struct conf WSCONF;

struct conf {
  char *string_init;
  char *string_end;
  bool enable_print;
};

//void push_node(List *l, char v);
//int count_nodes(Node *n);
//void output_list(Node *n);
//List *create_list(void);

int get_source_file(WSCONF cnfg);
//List *get_url(List *l);
//char *get_str(List *l);
void get_file(char *argv);

#endif