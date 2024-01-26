#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 250
#define MAX_WORD_LENGTH 10

void findWord(char letter[MAX_ROWS][MAX_COLS], char word[MAX_WORD_LENGTH], int rows, int cols, FILE *output)
{
    // find length of word
    int len = strlen(word);

    word[strcspn(word, "\n")] = '\0';

    int i = 0, j = 0, k = 0;

    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {

            // check if it is possible to search horizontally
            if (j <= cols - len)
            {
                int found = 1;

                // check horizontal
                for (k = 0; k < len; ++k)
                {
                    if (letter[i][j + k] != word[k])
                    {
                        found = 0;
                        break;
                    }
                }

                if (found)
                {
                    fprintf(output, "%s (%d,%d) Horizontal\n", word, i + 1, j + 1);
                    return;
                }
            }

            // check if it is possible to search vertically
            if (i <= rows - len)
            {
                int found = 1;

                // check vertical
                for (k = 0; k < len; ++k)
                {
                    if (letter[i + k][j] != word[k])
                    {
                        found = 0;
                        break;
                    }
                }

                if (found)
                {
                    fprintf(output, "%s (%d,%d) Vertical\n", word, i + 1, j + 1);
                    return;
                }
            }

            // check if it is possible to search diagonally (left to right)
            if (i <= rows - len && j <= cols - len)
            {
                int found = 1;

                // check diagonal left to right
                for (k = 0; k < len; ++k)
                {
                    if (letter[i + k][j + k] != word[k])
                    {
                        found = 0;
                        break;
                    }
                }

                if (found)
                {
                    fprintf(output, "%s (%d,%d) Diagonal\n", word, i + 1, j + 1);
                    return;
                }
            }
        }
    }
}

int main()
{
    FILE *output = fopen("output.txt", "w");
    FILE *input2 = fopen("input2.txt", "r");
    FILE *input1 = fopen("input1.txt", "r");

    char letter[MAX_ROWS][MAX_COLS];
    char words[MAX_WORD_LENGTH];

    int rows = 0, currentcols, cols = 0;

    // reading from  input2.txt
    while (fgets(letter[rows], MAX_COLS, input2) != NULL)
    {
        rows++;
        if (rows == MAX_ROWS)
        {
            break;
        }
    }

    // calculate maximum column to get correct grid
    for (int i = 0; i < rows; i++)
    {
        currentcols = strlen(letter[i]);
        if (cols < currentcols)
        {
            cols = currentcols;
        }
    }

    // scan words from input1.txt
    while (fscanf(input1, "%10s", words) == 1)
    {
        findWord(letter, words, rows, cols, output);
    }

    fclose(input2);
    fclose(input1);
    fclose(output);

    return 0;
}
