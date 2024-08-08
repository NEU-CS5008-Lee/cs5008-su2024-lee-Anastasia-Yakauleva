// name: <your name here>
// email: <your email here>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int getrepeat(char *str,char ch)
{
    char *ptr=str;
    int repeat=0;
    while(*ptr==ch)
    {
        ptr+=1;
        repeat++;
    }
    return repeat;
}

// Function to perform Run Length Encoding (RLE) on a given string
char *runlengthencoding(char *str,char *rle )
{
    char *ptr=str;
    char *ptrend=&str[strlen(str)];
    char encoding[100];
    int repeat;
    strcpy(rle,""); // Initialize the encoded string to be empty

    while(ptr<ptrend)
    {    // Count consecutive occurrences of the current character
        repeat=getrepeat(ptr,*ptr);
        if(repeat>1)
        {
            sprintf(encoding,"%c%d",*ptr,repeat);
            strcat(rle,encoding);
            ptr=ptr+repeat;
        }else
        {
            sprintf(encoding,"%c",*ptr);
            strcat(rle,encoding);
            ptr++;
        }
    }

    return rle;
}

// Function to extract the number following a character from the encoded string
int getcount(char *rle)
{
    int count=0;
    while(isdigit(*rle)){
        //'3' - '0' gives 3 because the characters ‘0’ to ‘9’ are contiguous in the ASCII table
        count = count * 10 + (*rle - '0');
        rle++;
    }
    return count;
}

char *decode_rle(char *rle, char *str)
{
    char *ptr=rle;
    char *ptrend=&rle[strlen(rle)]; // end pointer = adress of encoded str null terminator
    char decoding[100];
    int i=0,j=0,count=0, digit=0;
    strcpy(str, "");

    // Loop through the encoded string
    while (ptr < ptrend){
        if (isalpha(*ptr)){
            char current = *ptr;
            ptr++;
            if (isdigit(*ptr)){
                // If the next character is a digit, extract the repeat
                count = getcount(ptr);
                // Move the pointer forward by the number of digits processed
                while (isdigit(*ptr)) {
                    ptr++;
                }
            }else{
                // If there is no repeat count, it means the character repeats once
                count = 1;
            }
            // char appends count times
            for(j = 0; j < count; j++){
                str[i++] = current;
            }
        }
    }

    str[i] = '\0';
    return str;
}


int main()
{
    char str_org[]="WWWWWWWWWWWWWWWWWWWWWWWWWWWWbAAAABBCBBCBBCaaa";
    char rle[100];
    runlengthencoding(str_org,rle);
    printf("str_org:[%s] => rle:[%s]\n",str_org,rle);

    char str_dec[100];
    decode_rle(rle,str_dec);
    printf("rle:[%s] => str_dec:[%s]\n",rle, str_dec);
    return 0;
}