//Anastasia
//yakauleva.a@northeastern.edu

//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>
int main()
{
    FILE *fp, *fp_w;
    int arr[10],temp;
    int count=0,i,j;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp=fopen("Input1.txt","r");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(1);
    }
    else{
		while(fscanf(fp, "%d", &temp) == 1){
			arr[count] = temp;
			count++;
		}

	}
	fclose(fp);

	for (i = 1; i < count; i++){
		temp = arr[i];
		j = i - 1;
		while(j >= 0 && temp < arr[j]){
			arr[j+1] = arr[j];  // The one to the right becomes like left
			j--;
		}
		arr[j+1] = temp; // left becomes the smallest

	}

    // Display the sorted array
    printf("Sorted array: ");
	for(i = 0; i < count; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

    // Open the output file for writing
    fp_w = fopen("Output.txt", "w");
	if (fp_w == NULL){
	printf("\nCannot open the output file\n");
    exit(1);
	}

	// Write the sorted array to the output file
	for (i = 0; i< count; i++){
		fprintf(fp_w, "%d\n", arr[i]);
	}

    fclose(fp_w);
    
    return 0;
}
