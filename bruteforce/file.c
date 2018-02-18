/*
** Created by glastis on 13/02/18.
*/

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void                write_output(const char *filepath, const char *message)
{
    FILE            *fs;

    fs = fopen(filepath, "a");
    if (!fs)
    {
        fprintf(stderr, "%s: %s\n", filepath, MESSAGE_OPEN_FAIL);
        exit(EXIT_FAILURE);
    }
    fprintf(fs, "%s", message);
    fclose(fs);
}

static char         *get_file(const char *filepath)
{
    FILE            *fs;
    long            len;
    char            *raw;

    raw = NULL;
    if (!(fs = fopen(filepath, "rb")))
    {
        fprintf(stderr, "%s: %s\n", filepath, MESSAGE_OPEN_FAIL);
        exit(EXIT_FAILURE);
    }
    fseek(fs, 0, SEEK_END);
    len = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    if (!(raw = malloc(len + 1)))
    {
        fprintf(stderr, "%s", MESSAGE_MALLOC_FAILED);
        exit(EXIT_FAILURE);
    }
    fread(raw, 1, len, fs);
    raw[len] = '\0';
    fclose(fs);
    return (raw);
}

static void         fill_hash_ref(t_opt *opt, char *raw)
{
    unsigned int    i;
    unsigned int    tmp;

    i = 0;
    while (raw[i])
    {
        tmp = i;
        while ((raw[i] >= 'a' && raw[i] <= 'z') ||
               (raw[i] >= 'A' && raw[i] <= 'Z') ||
               (raw[i] >= '0' && raw[i] <= '9'))
        {
            i += 1;
        }
        if (i > 0 && ((raw[i - 1] >= 'a' && raw[i - 1] <= 'z') ||
                      (raw[i - 1] >= 'A' && raw[i - 1] <= 'Z') ||
                      (raw[i - 1] >= '0' && raw[i - 1] <= '9')))
        {
            add_hash_ref(opt, &raw[tmp]);
        }
        if (raw[i])
        {
            raw[i] = '\0';
            i += 1;
        }
        while (raw[i] && (raw[i] < 'a' || raw[i] > 'z') &&
                         (raw[i] < 'A' || raw[i] > 'Z') &&
                         (raw[i] < '0' || raw[i] > '9'))
        {
            i += 1;
        }
    }
}

void                get_hash(t_opt *opt)
{
    unsigned int    i;
    char            *raw;

    i = 0;
    raw = get_file(opt->hash_filepath);
    fill_hash_ref(opt, raw);
    while (opt->hash_ref[i])
    {
        if (!opt->quiet)
        {
            printf("Hash found in file: %s\n", opt->hash_ref[i]);
        }
        if (opt->output_filepath)
        {
            write_output(opt->output_filepath, "Hash found in file: ");
            write_output(opt->output_filepath, opt->hash_ref[i]);
            write_output(opt->output_filepath, "\n");
        }
        i += 1;
    }
}