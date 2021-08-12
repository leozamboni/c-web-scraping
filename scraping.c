/*
 * Web Scraping C 
 * Copyright © 2021 Leonardo Zamboni 🌎 leozamboni.dev
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
#include "scraping.h" 

Queue *create_queue(void) {
  Queue *q = (Queue *) malloc(sizeof(Queue));
  q->f = q->b = NULL;
  return q;
}

void push_queue(Queue *q, char c) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->c = c;
  new->n = NULL;
  if (!q->f) q->f = new;
  else q->b->n = new;
  q->b = new;
}

void output_queue(Node *f) {
  if (!f) return;
  printf("%c",f->c);
  output_queue(f->n);
}

int count_nodes_queue(Node *f) {
  if (!f) return 0;
  return 1 + count_nodes_queue(f->n);
}

char *get_str(Node *f) {
  char *str = (char *) malloc(count_nodes_queue(f) * sizeof(char));

  size_t i;
  for (i = 0; f; f = f->n) 
    str[i++] = f->c;

  str[i] = '\0';
  return str;
}

void get_file(char *argv) {
  char *cmd = (char *) malloc(strlen(CURL) + strlen(argv));
  strcat(strcpy(cmd,CURL),argv);

  printf("%s\n", cmd);
  system(cmd);

  free(cmd); 
}

char *get_source(WSCONF cnfg) {
  Queue *srcq = create_queue();
  FILE *getfl;

  getfl = fopen(GET_FILE,"r");
  if (!getfl) return NULL;

  char c;
  if (cnfg.string_init) {

    while ((c = getc(getfl)) != EOF) {
      size_t i;
      for (i = 0; i < strlen(cnfg.string_init); i++) 
        if (c != cnfg.string_init[i] || c == EOF) break;
        else c = getc(getfl);

      if (i == strlen(cnfg.string_init)) {

        while ((c = getc(getfl)) != EOF) {
          size_t j;
          for (j = 0; j < strlen(cnfg.string_end); j++) 
            if (c != cnfg.string_end[j] || c == EOF) break;
            else c = getc(getfl);

          if (j == strlen(cnfg.string_end)) { push_queue(srcq,'\n'); break; }
    
          if (cnfg.enable_print) putchar(c);

          push_queue(srcq,c); 
        } 
        
        puts("");
      }
    }

  }
  else {
    while ((c = getc(getfl)) != EOF)
      putchar(c);
  }

  fclose(getfl);
  remove(GET_FILE);
  return get_str(srcq->f);   
}