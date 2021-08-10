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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scraping.h" 

void get_file(char *argv) {
  char *cmd = (char *) malloc(strlen(CURL) + strlen(argv));
  strcat(strcpy(cmd,CURL),argv);

  printf("%s\n", cmd);
  system(cmd);

  free(cmd); 
}

int get_source_file(WSCONF cnfg) {
  FILE *getfp;
  FILE *setfp;

  getfp = fopen(GET_FILE,"r");
  if (!getfp) return 1;

  setfp = fopen(SET_FILE,"w");

  char c;
  if (cnfg.string_init) {

    while ((c = getc(getfp)) != EOF) {
      size_t i;

      for (i = 0; i < strlen(cnfg.string_init); i++, c = getc(getfp)) 
        if (c != cnfg.string_init[i] || c == EOF) break;

      if (i == strlen(cnfg.string_init)) {
        while ((c = getc(getfp)) != EOF) {
          size_t j;
    
          if (cnfg.enable_print)
            putchar(c);

          fprintf(setfp,"%c",c);  
          for (j = 0; j < strlen(cnfg.string_end); j++, c = getc(getfp)) 
            if (c != cnfg.string_end[j] || c == EOF) break;

          if (j == strlen(cnfg.string_end)) { fprintf(setfp,"\n"); break; }
        } 
      }
    }

  }
  else {
    while ((c = getc(getfp)) != EOF)
      putchar(c);
  }

  fclose(setfp);
  fclose(getfp);
  return 0;   
}