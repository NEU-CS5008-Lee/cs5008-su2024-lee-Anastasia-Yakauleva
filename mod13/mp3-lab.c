// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu

#include<stdio.h>
#include<string.h>

/**
 * Compresses the input character array by counting consecutive characters
 * and appending the character followed by the count to the result array.
 * If a character appears only once, it is appended without a count.
 *
 * For example:
 * - Input: "aaaaaaaaaaaaaabbbbcccd"
 * - Output: "a14b4c3d"
 *
 * @param arr The input character array to be compressed.
 * @param n The length of the input character array.
 * @param res The output character array to store the compressed result.
 *
 * @return The length of the compressed string stored in res.
 *
 */
int compression(char arr[], int n, char res[]){
    int count = 1;
    int count_res = 0;

    char prev = arr[0];
    char cur;

    for (int i = 1; i<n; i++){
        cur = arr[i];
        if (prev == cur){
            count ++;
        } else{
            res[count_res++] = prev;
            if (count > 1) {
                // sprintf to handle counts greater than 9
                count_res += sprintf(&res[count_res], "%d", count);
                }
            count = 1;
        }
        prev = cur;
    }
    // Handle the last group
    res[count_res++] = prev;
    if (count > 1) {
        count_res += sprintf(&res[count_res], "%d", count);
    }

    res[count_res] = '\0'; // Null-terminate the result string
    return count_res;

}

int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("Compressed string: %s\n", res);
    printf("length of the compressed string:%d\n",r);
    return 0;
}