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

int extract(void) {
  FILE *html;
  char c;

  html = fopen(HTML,"r");
  if (!html) return 1;

  #ifdef HTML_TAG

  while ((c = getc(html)) != EOF) {
    size_t i;

    for (i = 0; i < strlen(HTML_TAG); i++, c = getc(html)) 
      if (c != HTML_TAG[i] || c == EOF) break;

    if (i == strlen(HTML_TAG)) {
      while ((c = getc(html)) != EOF) {
        size_t j;

        putchar(c);
        
        for (j = 0; j < strlen(HTML_TAG_END); j++, c = getc(html)) 
          if (c != HTML_TAG_END[j] || c == EOF) break;

        if (j == strlen(HTML_TAG_END)) break;
      } 
    }
  }

  #else

  while ((c = getc(html)) != EOF)
    putchar(c);

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

