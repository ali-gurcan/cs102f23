#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum gate name length
#define MAX_GATE_NAME 20

// Gate type constants
#define INPUT 1
#define OUTPUT 0
#define AND 2
#define OR 3
#define NOT 4
#define FLIPFLOP 5

struct Gate
{
    int type;                 // Type of the gate
    char name[MAX_GATE_NAME]; // Name of the gate
    struct Gate *inp1;        // Points to input gate 1
    struct Gate *inp2;        // Points to input gate 2
    int output;               // Stores the current output
    int former_out;           // Only for flipflop
    int flag;
};

void createLogicCircuit(FILE *circuit_file, struct Gate *gates[], int *gate_count);
void evaluateInput(FILE *input_file, struct Gate *gates[], int *gate_count, int *input_count);
int evaluateGate(struct Gate *gate);
void freeMemory(struct Gate *gates[], int gate_count);
int gateCounter(FILE *circuit_file, int *input_count);

// Function to evaluate gate outputs
int evaluateGate(struct Gate *gate)
{
    if (gate->type == OUTPUT)
    {
        return evaluateGate(gate->inp1);
    }
    if (gate->type == INPUT)
    {
        return gate->output;
    }
    if (gate->type == AND)
    {
        if (gate->flag == 1)
        {
            return gate->output;
        }
        else
        {
            int inp1 = evaluateGate(gate->inp1);
            int inp2 = evaluateGate(gate->inp2);
            gate->output = inp1 && inp2;
            gate->flag = 1;
            return gate->output;
        }
    }
    if (gate->type == OR)
    {
        if (gate->flag == 1)
        {
            return gate->output;
        }
        else
        {
            int inp1 = evaluateGate(gate->inp1);
            int inp2 = evaluateGate(gate->inp2);
            gate->output = inp1 || inp2;
            gate->flag = 1;
            return gate->output;
        }
    }
    if (gate->type == NOT)
    {
        if (gate->flag == 1)
        {
            return gate->output;
        }
        else
        {
            gate->output = !evaluateGate(gate->inp1);
            gate->flag = 1;
            return gate->output;
        }
    }
    if (gate->type == FLIPFLOP)
    {
        if (gate->flag == 1)
        {
            return gate->output;
        }
        else
        {
            gate->output = (evaluateGate(gate->inp1) ^ gate->former_out);
            gate->former_out = gate->output;
            gate->flag = 1;
            return gate->output;
        }
    }
    // For unrecognized behavior
    return 0;
}

void createLogicCircuit(FILE *circuit_file, struct Gate *gates[], int *gate_count)
{
    char gateType[MAX_GATE_NAME], gateName[MAX_GATE_NAME];
    char fromGate[MAX_GATE_NAME], toGate[MAX_GATE_NAME];
    // Initial capacity of the gates array
    while (fscanf(circuit_file, "%s", gateType) == 1)
    {
        // FOR GATE CREATION
        if (strcmp(gateType, "GATE") == 0)
        {
            fscanf(circuit_file, "%s %s", gateType, gateName);
            //  to check gates correctly
            struct Gate *newGate = (struct Gate *)malloc(sizeof(struct Gate));
            if (!newGate)
            {
                printf("Memory allocation failed!\n");
            }
            if (strcmp(gateType, "INPUT") == 0)
            {
                newGate->type = INPUT;
            }
            else if (strcmp(gateType, "OUTPUT") == 0)
            {
                newGate->type = OUTPUT;
            }
            else if (strcmp(gateType, "AND") == 0)
            {
                newGate->type = AND;
            }
            else if (strcmp(gateType, "OR") == 0)
            {
                newGate->type = OR;
            }
            else if (strcmp(gateType, "NOT") == 0)
            {
                newGate->type = NOT;
            }
            else if (strcmp(gateType, "FLIPFLOP") == 0)
            {
                newGate->type = FLIPFLOP;
            }

            // Copy gate name and initialize
            strcpy(newGate->name, gateName);
            newGate->output = 0;
            newGate->former_out = 0;
            newGate->flag = 0;
            newGate->inp1 = NULL;
            newGate->inp2 = NULL;

            gates[(*gate_count)] = newGate;
            (*gate_count)++;
        }
        // FOR GATE CONNECTIONS
        if (strcmp(gateType, "CONNECTION") == 0)
        {
            fscanf(circuit_file, "%s %s", fromGate, toGate);
            struct Gate *from = NULL;
            struct Gate *to = NULL;
            for (int i = 0; i < *gate_count; ++i)
            {
                if (strcmp(gates[i]->name, fromGate) == 0)
                    from = gates[i];
                if (strcmp(gates[i]->name, toGate) == 0)
                    to = gates[i];
            }
            if (from != NULL && to != NULL)
            {
                if (to->inp1 == NULL)
                    to->inp1 = from;
                else
                    to->inp2 = from;
            }
        }
    }
}

void evaluateInput(FILE *input_file, struct Gate *gates[], int *gate_count, int *input_count)
{
    // that creates enough size input array according to gate number(column)
    // +1 for \0
    char input[*input_count + 1];
    int out = 0;
    int j = 0;
    while (fscanf(input_file, "%s", input) == 1)
    {
        // j will be reset for each row of input values
        j = 0;
        // Assign input values to INPUT type gate
        for (int i = 0; i < *gate_count; i++)
        {
            if (gates[i]->type == INPUT)
            {
                // Convert character input to integer value
                gates[i]->output = input[j] - '0';
                j++;
            }
        }
        for (int i = 0; i < *gate_count; i++)
        {
            // Find output gate and set as root gate
            if (gates[i]->type == OUTPUT)
            {
                out = evaluateGate(gates[i]);
                printf("%d\n", out);
                break;
            }
        }
        // Reset flags for next line
        for (int i = 0; i < *gate_count; i++)
        {
            gates[i]->flag = 0;
        }
    }
}
95 50 75 95 80 100 200,     30,40625 40.6
// Function to free allocated memory
void freeMemory(struct Gate *gates[], int gate_count)
{
    // Free gates and their connections
    for (int i = 0; i < gate_count; i++)
    {
        free(gates[i]);
    }
    // Free the array of gate pointers
    free(gates);
}
int gateCounter(FILE *circuit_file, int *input_count)
{
    int gate_count = 0;
    char counter[MAX_GATE_NAME];
    // Initial capacity of the gates array
    while (fscanf(circuit_file, "%s", counter) == 1)
    {
        if (strcmp(counter, "GATE") == 0)
        {
            (gate_count)++;
        }
        if (strcmp(counter, "INPUT") == 0)
        {
            (*input_count)++;
        }
    }
    // Reset file pointer to the beginning
    fseek(circuit_file, 0, SEEK_SET);
    return gate_count;
}
int main()
{
    FILE *circuit_file, *input_file;

    circuit_file = fopen("circuit.txt", "r");
    int gate_count = 0;
    int input_count = 0;
    //  That func give us how many gates and input gate there are
    gate_count = gateCounter(circuit_file, &input_count);
    
    // It creates fixed size of struct array
    struct Gate **gates = (struct Gate **)malloc(gate_count * sizeof(struct Gate *));

    // reset gate_count  
    gate_count = 0;
    // That func creates tree
    createLogicCircuit(circuit_file, gates, &gate_count);
    fclose(circuit_file);

    // Open input file
    input_file = fopen("input.txt", "r");
    // Evaluate input cases
    evaluateInput(input_file, gates, &gate_count, &input_count);
    fclose(input_file);
    // Free allocated memory
    freeMemory(gates, gate_count);

    return 0;
}
