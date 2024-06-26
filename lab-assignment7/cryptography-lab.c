// name: Anastasia
// email: yakauleva.a@northeastern.edu

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* function to encrypt the data*/
void encrypt(char text[], int key)
{
    for (int x=0; x < strlen(text); x++){
        // Determine if char is uppercase or lowercase
        char offset = isupper(text[x]) ? 'A' : 'a';
        text[x] = (text[x] - offset + key) % 26 + offset;

    }
}

/*function to decrypt the data*/
void decrypt(char text[],int key)
{
    
    for (int x=0; x < strlen(text); x++){
        char offset = isupper(text[x]) ? 'A' : 'a';
        text[x] = (text[x] - offset - key +26) % 26 + offset;
    }
}


/*----------- Main program---------------*/
int main()
{
    char text[20] ;
    int keyvalue=3;
    /*Input string */
    printf("Enter the message:  ");
    scanf("%s",text);
    printf("text input   = %s\n",text);
    
    /*call function to encrypt the data*/
    encrypt(text,keyvalue);
    printf("Encrypted value = %s\n",text);
    
    /*call function to decrypt the data*/
    decrypt(text,keyvalue);
    printf("Decrypted value = %s\n",text);
    
    return 0;
}
