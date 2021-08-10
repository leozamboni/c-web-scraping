#ifndef SCRAPING_H
#define SCRAPING_H

#include <stdio.h>

#define _ENABLE_CURL_ 

#define HTML_TAG "<li class"
#define HTML_TAG_END "</li>"

#define HTML "index.txt"

#ifdef _ENABLE_CURL_  
  #define CURL "curl --output index.txt "
#endif

typedef struct node Node;

struct node {
  char value;
  Node *next;
};

typedef struct list List; 

struct list {
  Node *nodes;
  Node *head;
};

int extract(void);

void push_node(List *l, char v);
int count_nodes(Node *n);
void output_list(Node *n);
List *create_list(void);

List *get_url(List *l);
char *get_str(List *l);
void got_file(char *argv);

#endif