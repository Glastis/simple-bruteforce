/*
// Created by glastis on 06/02/18.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

unsigned int         get_alphabet_rank(const char a)
{
    unsigned int            i;

    i = 0;
    while (ALPHABET[i] && ALPHABET[i] != a)
    {
        ++i;
    }
    return i;
}

void                get_options(t_opt *opt, char **av)
{
    unsigned int    i;

    i = 0;
    opt->hash_ref = NULL;
    opt->verbose_lvl_1 = FALSE;
    opt->verbose_lvl_2 = FALSE;
    while (av[i])
    {
        if (!opt->hash_ref && av[i][0] && av[i][0] != '-')
        {
            opt->hash_ref = av[i];
        }
        else if (av[i][0] == '-')
        {
            if (!strcmp(OPTION_VERBOSE_1, av[i]))
            {
                opt->verbose_lvl_1 = TRUE;
            }
            else if (!strcmp(OPTION_VERBOSE_2, av[i]))
            {
                opt->verbose_lvl_2 = TRUE;
            }
            else
            {
                printf("Unknown option: %s\n", av[i]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Unknown parameter: %s\n", av[i]);
            exit(EXIT_FAILURE);
        }
        i += 1;
    }

}