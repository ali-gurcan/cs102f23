#include <stdio.h>
#define MAX 100

int main()
{
    FILE *fp1, *fp2;
    int i = 0, k = 0;
    // inputnumber is number of input .In pdf, it's 13
    int inputnumber = 0;
    int firstgram[MAX] = {0}, secondgram[MAX] = {0}, counter[MAX] = {0};
    int line =0,flag=0;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (fp1 == NULL){
        printf("Error for input.txt\n");
        return 1;
    }
    if (fp2 == NULL){
        printf("Error for output.txt\n");
        return 1;
    }

    //that reads all numbers and counts how many numbers we have 
    while (fscanf(fp1, "%d", &firstgram[inputnumber]) != EOF){
       inputnumber++;
    }
    
    //adjusting secondgrams
    for (i = 0; i < inputnumber-1; i++){
        secondgram[i] = firstgram[i + 1];
    }

    //  finding successive elements
    for (i = 0; i < inputnumber - 1; i++)
    {
        for (k = 0; k < inputnumber - 1; k++)
        {
            if (firstgram[i] == firstgram[k] && secondgram[i] == secondgram[k])
            {
                // if i greater than k we do not need to check,except first time
                if (i > k){
                    //flag=1 means that it is readed.
                    flag=1;
                    counter[i]=0;
                    break;
                }
                // flag checks the if statement above
                // if line is greater than MAX which is 100,execution stops
                if (flag != 1 || line < MAX){
                    counter[i]++;
                }
            }
        }
        // writing operation,i and line must be less than MAX
        if (counter[i] > 0 && i<MAX && line<MAX){
            fprintf(fp2, "%d %d:%d\n",firstgram[i], secondgram[i], counter[i]);
            line++;
        }
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
