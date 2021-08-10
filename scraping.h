#ifndef SCRAPING_H
#define SCRAPING_H

#include <stdio.h>

#define _ENABLE_CURL_ 

#define HTML_TAG "<html>"
#define HTML_TAG_END "</html>"

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

typedef char Type;

typedef struct vector {
    size_t size;
    size_t capacity;
    Type *array;
} Vector;

int extract(void);

void push_node(List *l, char v);
int count_nodes(Node *n);
void output_list(Node *n);
List *create_list(void);

List *get_url(List *l);
char *get_str(List *l);
void got_file(char *argv);

char *fin(FILE *fp);
Vector *vec_make(void);
void vec_add(Vector *v, Type value);
void vec_reset(Vector *v);
void vec_free(Vector *v) ;
size_t vec_size(Vector *v);
Type *vec_getArray(Vector *v);

#endif