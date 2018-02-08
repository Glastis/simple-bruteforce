/*
// Created by glastis on 06/02/18.
*/

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

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
                fprintf(stderr, "%s", "Error when allocating memory\n");
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

static int          compare_passphrase(t_opt *opt, const char *passphrase, unsigned int len)
{
    unsigned char   hash_raw[MD5_DIGEST_LENGTH];
    char            result[MD5_HASH_SIGNED_SIZE];
    unsigned int    i;

    i = 0;
    MD5((unsigned char *)passphrase, len, hash_raw);
    while (i < MD5_DIGEST_LENGTH)
    {
        sprintf(&result[i * 2], HASH_HEX_FORMAT, hash_raw[i]);
        i += 1;
    }
    if (opt->verbose_lvl_2)
    {
        printf("%s: %s\n", passphrase, result);
    }
    else if (opt->verbose_lvl_1)
    {
        printf("%s\n", passphrase);
    }

    return (strcmp(opt->hash_ref, result));
}

int                 main(int ac, char **av)
{
    char            *passphrase;
    unsigned int    len;
    t_opt           opt;

    UNUSED(ac);
    passphrase = NULL;
    get_options(&opt, &av[1]);
    if (!opt.hash_ref)
    {
        fprintf(stderr, "%s%s", av[0], " hash [-v[v]]\n");
        return (EXIT_FAILURE);
    }
    do
    {
        len = get_next_passphrase(&passphrase, len);
    }
    while (compare_passphrase(&opt, passphrase, len));
    printf("Password found: %s\n", passphrase);
    return (0);
}