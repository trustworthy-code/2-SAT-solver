#include <stdlib.h>
#include <stdio.h>
#include "two_satisfiability_solver.h"

void two_satisfiability(int argc, char* argv[])
{
    FILE *fin;
    int is_input_file = 0;
    if (argc > 1)
    {
        fin = fopen(argv[1], "r");
        is_input_file = 1;
    }

    int variable_count = 0;
    int disjunction_count = 0;
    if (is_input_file == 1)
    {
        fscanf(fin, "p cnf %d %d", &variable_count, &disjunction_count);
    }
    else
    {
        scanf("p cnf %d %d", &variable_count, &disjunction_count);
    }

    int double_disjunction_count = disjunction_count + disjunction_count; 
    int* disjunctions = (int*)malloc(double_disjunction_count * sizeof(int));

    for (int i = 0; i < double_disjunction_count; i += 2)
    {
        int first_disjunct = 0;
        int second_disjunct = 0;
        if (is_input_file == 1)
        {
            fscanf(fin, " %d %d 0", &first_disjunct, &second_disjunct);
        }
        else
        {
            scanf(" %d %d 0", &first_disjunct, &second_disjunct);
        }

        disjunctions[i] = first_disjunct;
        disjunctions[i + 1] = second_disjunct;
    }

    if (is_input_file == 1)
    {
        fclose(fin);
    }

    int* model = (int*)malloc(variable_count * sizeof(int));

    int result = two_satisfiability_solver(variable_count, disjunction_count, disjunctions, model);

    free(disjunctions);

    FILE *fout;
    int is_output_file = 0;
    if (argc > 2)
    {
        fout = fopen(argv[2], "w");
        is_output_file = 1;
    }

    if (result == 1)
    {
        if (is_output_file == 1)
        {
            fprintf(fout, "s SATISFIABLE\n");
            fprintf(fout, "v ");
            for (int i = 0; i < variable_count; i++)
            {
                fprintf(fout, "%d ", model[i]);
            }
            fprintf(fout, "0\n");
        }
        else
        {
            printf("s SATISFIABLE\n");
            printf("v ");
            for (int i = 0; i < variable_count; i++)
            {
                printf("%d ", model[i]);
            }
            printf("0\n");
        }
    }
    else
    {
        if (is_output_file == 1)
        {
            fprintf(fout, "s UNSATISFIABLE\n");
        }
        else
        {
            printf("s UNSATISFIABLE\n");
        }
    }

    free(model);

    if (is_output_file == 1)
    {
        fclose(fout);
    }
}