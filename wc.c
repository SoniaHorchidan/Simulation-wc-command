#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int parse_input(char **argv)
{
   int opt;
   if(argv[1] == NULL)
      return 3;
   else
   {
      if(argv[1][0] != '-')
         return 1;
      else
      {
         if(argv[2] == NULL)
            return 4;
         else
            return 2;
       }
   }
   return 0;
}

void print(int characters, int words, int lines, bool flag_c, bool flag_w, bool flag_l)
{
   if(flag_l == true)
        printf("%d ",lines);
     if(flag_w == true)
        printf("%d ",words);
   if(flag_c == true)
        printf("%d ",characters);
    printf("\n");
}

void word_count(char *tip, char *source, bool flag_c, bool flag_w, bool flag_l)
{
   int characters = 0, words = 0, lines = 0;
   char buffer = NULL;
   int prev = NULL;
   bool printed = false;
   if(strcmp(tip,"file") == 0)
   {
      FILE *in = fopen(source, "r");
      if(in == NULL)
         printf("Cannot find file %s\n", source);
      else
      {
         buffer = fgetc(in);

         if(buffer == EOF)
         {
            print(0, 0, 0, flag_c, flag_w, flag_l);
            printed = true;
         }
         else 
         {
            characters ++;
            while(!feof(in))
            {
               prev = buffer;
               buffer = fgetc(in);
               characters ++;
               if(buffer == '\n')
               {
                   lines++;
                   if(prev != '\n' && prev != ' ')
                        words++;
               }
               else
                  if(buffer == ' ')
                      if(prev != ' ' && prev != '\n')
                         words ++;
            }
            if(prev != ' '  && prev != '\n')
                words ++;
            characters --;
         }
         fclose(in);
      }
   }
   else
   {
      while(true)
      {
         prev = buffer;
         buffer = getchar();
         characters ++;
         if(buffer != EOF)
         {
            if(buffer == '\n')
            {
                lines++;
                if(prev != '\n' && prev != ' ')
                         words++;
            }
            else 
               if(buffer == ' ')
                   if(prev != ' ' && prev != '\n')
                       words ++;
          }
        else break;

      }
      if(prev != '\n' && prev != ' ')
         words ++;
     characters --;
   }
   if(!printed)
      print(characters , words, lines, flag_c, flag_w, flag_l);
}

void get_options(char *opt, bool *flag_c, bool *flag_w, bool *flag_l)
{
   int length = strlen(opt);
   for(int i = 1; i < length; i++)
   {
      if(opt[i] == 'c')
         *flag_c = true;
      else
         if(opt[i] == 'w')
            *flag_w = true;
         else
            if(opt[i] == 'l')
               *flag_l = true;
            else
            {
               printf("%s\n", "Optiune necunoscuta!");
               return;
            }
   }
}

int main(int argc, char **argv)
{
   if(argc < 1)
   {
      printf("%s\n", "Lipsa argumente!");
      exit(1);
   }

   int opt = parse_input(argv);

   switch(opt)
   {
      case 1:              //wc f
      {
         word_count("file",argv[1], true, true, true);
         break;
      }
      case 2:              //wc -opt f
      {
         bool flag_c = false;
         bool flag_w = false;
         bool flag_l = false;
         get_options(argv[1], &flag_c, &flag_w, &flag_l);
         word_count("file",argv[2], flag_c, flag_w, flag_l);
         break;
      }
      case 3:               //wc
      {
         word_count("stdin", NULL, true, true, true);
         break;
      }
      case 4:              //wc opt
      {
         bool flag_c = false;
         bool flag_w = false;
         bool flag_l = false;
         get_options(argv[1], &flag_c, &flag_w, &flag_l);
         word_count("stdin",NULL, flag_c, flag_w, flag_l);
         break;
      }
      case 0:
      {
         printf("%s\n", "Comanda necunoscuta!");
         break;
      }
   }
   return 0;
}
