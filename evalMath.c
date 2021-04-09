/* 

    EvalMath

    library like "eval()" in python and JS

    Eg.: eval("1 + 3"); result = 4

    eval math *char


    Author: Fillipe Meireles

 */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct GenericList
{
    void *element;
    struct GenericList *next;
};
typedef int (*func)(int *, int);

char SYMBOL_OPS[4] = {'+', '-', '*', '/'};

void list_push(struct GenericList **head_ref, void *new_data, size_t data_len);
func assocArr(char ops);

int sum(int *nums, int componets_len)
{
    int result = 0;

     for (int i = 0; i < componets_len; i++)
        result += nums[i];

    return result;
}

int subtr(int *nums, int componets_len)
{
    int result = 0;

     for (int i = 0; i < componets_len; i++)
        result = nums[i] - nums[i + 1];

    return result;
}

func OPERATORS[] = {&sum, &subtr};
int main()
{

    char *test_calc;
    test_calc = "3 - 1";

    int *nums_to_calc;
    char op;
    size_t components_len = 2;

    nums_to_calc = (int *)malloc(2 *sizeof(int));
    for (int i = 0; i < sizeof(test_calc); i++)
    {
        for (int j = 0; j < sizeof(SYMBOL_OPS); j++)
        {
            if (test_calc[i] == SYMBOL_OPS[j])
            {
                op = SYMBOL_OPS[j];

                for (int k = i - 1; k >= 0; k--)
                {
                    if (isdigit(test_calc[k]))
                        nums_to_calc[0] = test_calc[k] - '0';
                }
                for (int l = i; l <= sizeof(test_calc); l++)
                {
                    if (isdigit(test_calc[l]))
                        nums_to_calc[1] = test_calc[l] - '0';
                }
            }
        }
    }


    func operation = assocArr(op);
    

    int result = operation(nums_to_calc, components_len);

    printf("operation result : %d\n", result);
    free(nums_to_calc);
    return 0;
}

// To associative array
void list_push(struct GenericList **head_ref, void *new_data, size_t data_len)
{
    struct GenericList *new_list = (struct GenericList *)malloc(sizeof(struct GenericList));
    new_list->element = malloc(data_len);
    new_list->next = (*head_ref);

    for (int i = 0; i < data_len; i++)
        *(char *)(new_list->element + 1) = *(char *)(new_data + 1);

    (*head_ref) = new_list;
}

func assocArr(char ops)
{
    int symbol_index;

    for (int i = 0; i < sizeof(SYMBOL_OPS); i++)
    {
        if (ops == SYMBOL_OPS[i])
            symbol_index = i;
    }

    return OPERATORS[symbol_index];
}