/*
// Created by glastis on 06/02/18.
*/

#ifndef DEVOIR_SECU_1_MAIN_H
#define DEVOIR_SECU_1_MAIN_H

#define AES_BLOCK_SIZE          16
#define MD5_HASH_SIGNED_SIZE    (MD5_DIGEST_LENGTH * 2)

#define TRUE                    1u
#define FALSE                   0u
#define UNUSED(X)               ((void)(X))
#define ALPHABET                "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*"
#define HASH_HEX_FORMAT         "%02x"

#define OPTION_VERBOSE_1        "-v"
#define OPTION_VERBOSE_2        "-vv"


typedef struct                  s_opt
{
    unsigned int                verbose_lvl_1;
    unsigned int                verbose_lvl_2;
    char                        *hash_ref;
}                               t_opt;

unsigned int                    get_alphabet_rank(const char a);
void                            get_options(t_opt *opt, char **av);

#endif /* DEVOIR_SECU_1_MAIN_H */
