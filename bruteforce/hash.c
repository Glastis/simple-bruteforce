/*
** Created by glastis on 16/02/18.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>

#include "main.h"

static inline void      get_md5(const char *ref, char *result, const unsigned int len)
{
    unsigned char       hash_raw[MD5_DIGEST_LENGTH];
    unsigned int        i;

    i = 0;
    MD5((unsigned char *)ref, len, hash_raw);
    while (i < MD5_DIGEST_LENGTH)
    {
        sprintf(&result[i * 2], HASH_HEX_FORMAT, hash_raw[i]);
        i += 1;
    }
}

int                     compare_passphrase(t_opt *opt, const char *passphrase, const unsigned int len)
{
    unsigned int        i;
    char                result[MD5_HASH_SIGNED_SIZE];

    i = 0;
    get_md5(passphrase, &result[0], len);
    if (opt->verbose_lvl_2)
    {
        fprintf(stderr, "%s: %s\n", passphrase, result);
    }
    else if (opt->verbose_lvl_1)
    {
        fprintf(stderr, "%s\n", passphrase);
    }
    while (opt->hash_ref[i])
    {
        if (!strcmp(opt->hash_ref[i], result))
        {
            printf("Password found for %s: %s\n", opt->hash_ref[i], passphrase);
            del_hash_ref(opt, i);
            i = 0;
        }
        i += 1;
    }
    return (opt->hash_ref[0] != NULL);
}