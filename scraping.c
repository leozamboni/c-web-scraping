#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scraping.h" 

List *create_list(void) {
  List *l = (List *) malloc(sizeof(List));
  l->nodes = l->head = NULL;
  return l;
}

void push_node(List *l, char v) {
  Node *new = (Node *) malloc(sizeof(Node));
  if (!l->head) l->head = new;
  else l->nodes->next = new;
  new->value = v;
  new->next = NULL;
  l->nodes = new;
}

int count_nodes(Node *n) {
  if (!n) return 0;
  return 1 + count_nodes(n->next);
}

List *get_url(List *l) {
  char c = getchar();
  if (c == '\n') return l;
  push_node(l,c);
  get_url(l);
} 

void output_list(Node *n) {
  if (!n) return;
  printf("%c", n->value);
  output_list(n->next);
}

char *get_str(List *l) {
  Node *w = l->head;
  char *str = (char *) malloc((count_nodes(w)-1) * sizeof(char));

  for (size_t i = 0; w; w = w->next) 
    str[i++] = w->value;

  return str;
}

void got_file(char *argv) {
  char *cmd = (char *) malloc(strlen(CURL) + strlen(argv));
  strcat(strcpy(cmd,CURL),argv);

  printf("%s\n", cmd);
  system(cmd);

  free(cmd); 
}

Vector *vec_make(void) {
  Vector *v;
  v = (Vector*)malloc(sizeof(Vector));
  if(v){
    v->size = 0;
    v->capacity=16;
    v->array=(Type*)realloc(NULL, sizeof(Type)*(v->capacity += 16));
  }
  return v;
}

void vec_add(Vector *v, Type value) {
  v->array[v->size] = value;
  if(++v->size == v->capacity){
      v->array=(Type*)realloc(v->array, sizeof(Type)*(v->capacity += 16));
      if(!v->array){
          perror("memory not enough");
          exit(-1);
      }
  }
}

void vec_reset(Vector *v) {
  v->size = 0;
}

size_t vec_size(Vector *v) {
  return v->size;
}

Type *vec_getArray(Vector *v) {
  return v->array;
}

void vec_free(Vector *v) {
  free(v->array);
  free(v);
}

char *fin(FILE *fp) {
  static Vector *v = NULL;
  int ch;

  if(v == NULL) v = vec_make();
  vec_reset(v);
  while(EOF!=(ch=fgetc(fp))){
    if(isspace(ch)) continue;
    while(!isspace(ch)){
        vec_add(v, ch);
        if(EOF == (ch = fgetc(fp)))break;
    }
    vec_add(v, '\0');
    break;
  }
  if(vec_size(v) != 0) return vec_getArray(v);
  vec_free(v);
  v = NULL;
  return NULL;
}

int extract(void) {
  FILE *html;
  FILE *result;

  html = fopen(HTML,"r");
  if (!html) return 1;

  result = fopen("return.txt","w");

  char *wordp;

  #ifdef HTML_TAG
  char *isdwordp;
  while(NULL!=(wordp=fin(html))) {
    if(strcmp(wordp,HTML_TAG) == 0) {
      while(NULL!=(isdwordp=fin(html))) {
        printf("%s<-\n",isdwordp);
        fprintf(result,isdwordp);
        if(strcmp(isdwordp,HTML_TAG_END) == 0) return 0;
      }
    }
  }
  #else
  while(NULL!=(wordp=fin(html)))
    printf("%s",wordp);
  #endif

  fclose(html);
  return 0;
}

int main(int argc, char **argv) {
  #ifdef _ENABLE_CURL_

  if (argc == 1) {
    printf("url: ");
    got_file(get_str(get_url(create_list()))); 
  }
  else got_file(argv[1]);

  #endif

  if (extract()) printf("Could not open HTML file\n");

  return 0;
}

