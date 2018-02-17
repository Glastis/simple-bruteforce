/*
** Created by glastis on 06/02/18.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

static int          get_next_passphrase(char **passphrase_ori, unsigned int len)
{
    char            *passphrase;
    unsigned int    lentmp;

    passphrase = *passphrase_ori;
    if (!passphrase)
    {
        if (!(passphrase = malloc(sizeof(char) * 2)))
        {
            fprintf(stderr, "%s", "Error when allocating memory\n");
            exit(EXIT_FAILURE);
        }
        *passphrase_ori = passphrase;
        passphrase[0] = ALPHABET[0];
        passphrase[1] = '\0';
        return (1);
    }
    if (passphrase[len - 1] != ALPHABET[sizeof(ALPHABET) - 2])
    {
        passphrase[len - 1] = ALPHABET[get_alphabet_rank(passphrase[len - 1]) + 1];
        return (len);
    }
    lentmp = len;
    while (passphrase[lentmp - 1] == ALPHABET[sizeof(ALPHABET) - 2])
    {
        passphrase[lentmp - 1] = ALPHABET[0];
        if (lentmp - 1 == 0)
        {
            len += 1;
            if (!(passphrase = realloc(passphrase, sizeof(char) * (len + 1))))
            {
                fprintf(stderr, "%s", MESSAGE_MALLOC_FAILED);
                exit(EXIT_FAILURE);
            }
            *passphrase_ori = passphrase;
            passphrase[len - 1] = ALPHABET[0];
            passphrase[len] = '\0';
            return (len);
        }
        lentmp -= 1;
        passphrase[lentmp - 1] = ALPHABET[get_alphabet_rank(passphrase[lentmp - 1]) + 1];
    }
    return (len);
}

int                 main(int ac, char **av)
{
    char            *passphrase;
    unsigned int    len;
    t_opt           opt;

    UNUSED(ac);
    len = 0;
    passphrase = NULL;
    get_options(&opt, &av[1]);
    if (!opt.hash_ref && !opt.hash_filepath)
    {
        fprintf(stderr, "%s%c%s", av[0], ' ', MESSAGE_USAGE);
        return (EXIT_FAILURE);
    }
    if (opt.hash_filepath)
    {
        get_hash(&opt);
    }
    if (opt.begin_from)
    {
        len = set_begining_passphrase(&passphrase, opt.begin_from);
    }
    else
    {
        len = get_next_passphrase(&passphrase, len);
    }
    while (compare_passphrase(&opt, passphrase, len))
    {
        len = get_next_passphrase(&passphrase, len);
    }
    return (0);
}