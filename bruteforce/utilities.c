/*
** Created by glastis on 06/02/18.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

inline unsigned int         get_alphabet_rank(const char a)
{
    unsigned int            i;

    i = 0;
    while (ALPHABET[i] && ALPHABET[i] != a)
    {
        i += 1;
    }
    return i;
}

void                        reinit_options(t_opt *opt)
{
    opt->output_filepath = NULL;
    opt->hash_filepath = NULL;
    opt->hash_ref = NULL;
    opt->begin_from = NULL;
    opt->quiet = FALSE;
    opt->verbose_lvl_1 = FALSE;
    opt->verbose_lvl_2 = FALSE;
}

void                        get_options(t_opt *opt, char **av)
{
    unsigned int            i;

    i = 0;
    reinit_options(opt);
    while (av[i])
    {
        if (!opt->hash_ref && av[i][0] && av[i][0] != '-')
        {
            add_hash_ref(opt, av[i]);
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
            else if (!strcmp(OPTION_QUIET, av[i]))
            {
                opt->quiet = TRUE;
            }
            else if (!strcmp(OPTION_BEGIN_FROM, av[i]))
            {
                if (!av[i + 1])
                {
                    reinit_options(opt);
                    return;
                }
                opt->begin_from = av[i + 1];
                i += 1;
            }
            else if (!strcmp(OPTION_HASH_FILE, av[i]))
            {
                if (!av[i + 1])
                {
                    reinit_options(opt);
                    return;
                }
                opt->hash_filepath = av[i + 1];
                i += 1;
            }
            else if (!strcmp(OPTION_OUTPUT_FILE, av[i]))
            {
                if (!av[i + 1])
                {
                    reinit_options(opt);
                    return;
                }
                opt->output_filepath = av[i + 1];
                i += 1;
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

unsigned int                set_begining_passphrase(char **to, char *from)
{
    char                    *passphrase;
    unsigned int            i;

    i = 0;
    while (from[i])
    {
        if (!ALPHABET[get_alphabet_rank(from[i])])
        {
            fprintf(stderr, MESSAGE_BEGINING_OPT);
            exit(EXIT_FAILURE);
        }
        i += 1;
    }
    if (!(passphrase = malloc((i + 1) * sizeof(char))))
    {
        fprintf(stderr, "%s", MESSAGE_MALLOC_FAILED);
        exit(EXIT_FAILURE);
    }
    strcpy(passphrase, from);
    *to = passphrase;
    return (strlen(passphrase));
}

void                    add_hash_ref(t_opt *opt, char *new_hash)
{
    unsigned int        i;

    i = 0;
    if (!opt->hash_ref)
    {
        if (!(opt->hash_ref = malloc(sizeof(char **) * 2)))
        {
            fprintf(stderr, "%s", MESSAGE_MALLOC_FAILED);
            exit(EXIT_FAILURE);
        }
        opt->hash_ref[0] = new_hash;
        opt->hash_ref[1] = NULL;
    }
    else
    {
        while (opt->hash_ref[i])
        {
            i += 1;
        }
        if (!(opt->hash_ref = realloc(opt->hash_ref, sizeof(char **) * (i + 2))))
        {
            fprintf(stderr, "%s", MESSAGE_MALLOC_FAILED);
            exit(EXIT_FAILURE);
        }
        opt->hash_ref[i] = new_hash;
        opt->hash_ref[i + 1] = NULL;
    }
}

void                    del_hash_ref(t_opt *opt, const unsigned int del_elem)
{
    unsigned int        max;

    max = 0;
    while (opt->hash_ref[max])
    {
        max += 1;
    }
    if (max == 0)
    {
        return;
    }
    if (del_elem != max - 1)
    {
        opt->hash_ref[del_elem] = opt->hash_ref[max - 1];
    }
    opt->hash_ref[max - 1] = NULL;
}
