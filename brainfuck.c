#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){


    FILE *file;
    char filename[20];
    if( argc == 2 )
        strcpy(filename,argv[1]);
    else{
        printf("How to: <program_name> <file_name>\n");
        exit(1);
    }

    int i;
    int count = 0;
    int ch;
    int *p;
    int *move;

    if(( p = malloc(256)) == NULL || ( move = malloc(256)) == NULL) {
        printf("no memory\n");
        exit(1);
    }

    for(i=0; i<64; i++) {
        *(p+i) = 0;
        *(move+i) = 0;
    }

    if ((file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "not found: %s\n", filename);
        exit(1);
    }
    int *hmove = move;
    while (( ch = fgetc(file)) != EOF ) {

        if( ch == 91) {     // [
            if( *p == 0) {
                while(1) {
                    ch = fgetc(file);
                    if(ch == 91)
                        count++;
                    if(ch == 93 && count == 0)
                        break;
                    else if(ch == 93)
                        count--;
                    if( ch == EOF){    //not found ]
                        printf("no ] \n");
                        exit(1);
                    }
                 }

            }else{
                move++;
                *move = ftell(file);

            }
        }

        else if( ch == 62) { //>
            p++;
        }else if( ch == 60) { //<
            p--;
        }else if( ch == 43) //+
            *p += 1;

        else if( ch == 45) // -
            (*p)--;

        else if( ch == 46) // .
            printf("%c",*p);

        else if( ch == 44) // ,
            *p=getchar();

        else if( ch == 93) {                      // ]
            if(hmove == move){                //not found [
                printf("%d: no [\n",ftell(file));
                exit(1);
            }
            if(*p != 0) {
                fseek(file, *move, 0);
            } else
                move--;
        }
    }
    free(p);
    free(move);

    fclose(file);
    return EXIT_SUCCESS;
}
