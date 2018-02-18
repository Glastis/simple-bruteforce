/*
** Created by glastis on 06/02/18.
*/

#ifndef DEVOIR_SECU_1_MAIN_H
#define DEVOIR_SECU_1_MAIN_H

#define AES_BLOCK_SIZE          16
#define MD5_HASH_SIGNED_SIZE    (MD5_DIGEST_LENGTH * 2)

#define TRUE                    1u
#define FALSE                   0u
#define UNUSED(X)               ((void)(X))
#define UNUSED(X)               ((void)(X))
#define ALPHABET                "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*"
#define HASH_HEX_FORMAT         "%02x"

/* OPTIONS */

#define OPTION_VERBOSE_1        "-v"
#define OPTION_VERBOSE_2        "-vv"
#define OPTION_BEGIN_FROM       "-r"
#define OPTION_HASH_FILE        "-f"
#define OPTION_OUTPUT_FILE      "-o"
#define OPTION_QUIET            "-q"

/* ERROR MESSAGES */

#define MESSAGE_MALLOC_FAILED   "Error when allocating memory.\n"
#define MESSAGE_USAGE           "hash \t[-v[v]]\t\tverbose mode lvl 1/2 (print on error output).\n\t\t[-r begin_with]\tprovide password to begin with.\n\t\t[-f filepath]\tprovide file that contains hash to reverse.\n\t\t[-o filepath]\tspecify output file.\n\t\t[-q]\t\tsupress default output (not including verbose and file output).\n"
#define MESSAGE_BEGINING_OPT    "Provided begining password not matching with ALPHABET macro.\n"
#define MESSAGE_OPEN_FAIL       "Can't open file."

typedef struct                  s_sav
{
    struct s_opt                *opt;
    char                        *passphrase;
}                               t_sav;

typedef struct                  s_opt
{
    unsigned int                verbose_lvl_1;
    unsigned int                verbose_lvl_2;
    unsigned int                quiet;
    char                        *output_filepath;
    char                        *hash_filepath;
    char                        *begin_from;
    char                        **hash_ref;
}                               t_opt;

/* main.c */
void                            sigint_handler(int i);

/* utilities.c */
unsigned int                    get_alphabet_rank(const char a);
void                            get_options(t_opt *opt, char **av);
unsigned int                    set_begining_passphrase(char **to, char *from);
void                            add_hash_ref(t_opt *opt, char *new_hash);
void                            del_hash_ref(t_opt *opt, const unsigned int del_elem);

/* file.c */
void                            get_hash(t_opt *opt);
void                            write_output(const char *filepath, const char *message);

/* hash.c */
int                             compare_passphrase(t_opt *opt, const char *passphrase, const unsigned int len);

#endif /* DEVOIR_SECU_1_MAIN_H */
