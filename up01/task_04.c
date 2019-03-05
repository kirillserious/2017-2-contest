#include <stdio.h>
#include <string.h>

int 
main(void)
{
    char filepath[80];
    
    int i, ch;
    for(i = 0; i < 61; i++){
        ch = getc(stdin);        
        filepath[i] = (char)ch;
        if ((ch == '\r') || (ch == '\n') || (ch == EOF)) break;
    }
    filepath[i] = '\0';
    if(i == 61){
        for (i = 0; i < 10; i ++) printf("%d 0\n", i);
        return 0;
    }

    
    FILE *inputfile;
    if(!(inputfile = fopen(filepath, "r"))){
        for (i = 0; i < 10; i ++) printf("%d 0\n", i);
        return 0;
    }
    
    unsigned int freq[10];
    memset(freq, 0, 10 * sizeof(unsigned));
    while (!feof(inputfile)){
        ch = fgetc(inputfile) - '0';
        if ((ch <= 9) && (ch >= 0)){
            freq[ch]++;
        }
        
    }
    
    for (i = 0; i <= 9; i ++) printf("%d %u\n", i, freq[i]);
    
    return 0;
}



