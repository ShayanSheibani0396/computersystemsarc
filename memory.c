/*
============================================================================
Name        : Lab6.c
Author      : Austin Tian
Revised by  : Shayan Sheibani
Version     :
Copyright   : Copyright 2023
Description : Lab 6 in C, ANSI-C Style
============================================================================
 */

#include "header.h"
#include <time.h>

// Menu
char *menu =
"\n"
" ***********Please select the following options**********************\n"
" *    This is the memory operation menu (Lab 6)                     *\n"
" ********************************************************************\n"
" *    1. Write a double-word (32-bit) to the memory                 *\n"
" ********************************************************************\n"
" *    2. Read a byte (8-bit) data from the memory                   *\n"
" *    3. Read a double-word (32-bit) data from the memory           *\n"
" ********************************************************************\n"
" *    4. Generate a memory dump from any memory location            *\n"
" ********************************************************************\n"
" *    e. To Exit, Type 'e'  or 'E'                                  *\n"
" ********************************************************************\n";

//---------------------------------------------------------------
unsigned char rand_generator()
{
    return rand() % 256;
}

/*---------------------------------------------------------------*/
void free_memory(char *base_address)
{
    free(base_address);
}

/*---------------------------------------------------------------*/
/* For Lab 7+ memory must be initialized to ZERO */
char *init_memory()
{
    char *mem = (char *)malloc(MEM_SIZE);

    if (mem == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    memset(mem, 0, MEM_SIZE);

    return mem;
}

/*---------------------------------------------------------------*/
void write_byte(const char *base_address, const int offset,
                const unsigned char byte_data)
{
    char *mem = (char *)base_address;
    mem[offset] = byte_data;
}

/*---------------------------------------------------------------*/
/* Write 32-bit value in LITTLE ENDIAN */
void write_dword(const char *base_address, const int offset,
                const unsigned int dword_data)
{
    char *mem = (char *)base_address;

    mem[offset]     = dword_data & 0xFF;
    mem[offset + 1] = (dword_data >> 8) & 0xFF;
    mem[offset + 2] = (dword_data >> 16) & 0xFF;
    mem[offset + 3] = (dword_data >> 24) & 0xFF;
}

/*---------------------------------------------------------------*/
/* Some lab files use write_word name */
void write_word(const char *base_address, const int offset,
                const unsigned int word_data)
{
    write_dword(base_address, offset, word_data);
}

/*---------------------------------------------------------------*/
unsigned char read_byte(const char *base_address, int offset)
{
    return (unsigned char)base_address[offset];
}

/*---------------------------------------------------------------*/
/* Read 32-bit LITTLE ENDIAN */
unsigned int read_dword(const char *base_address, int offset)
{
    unsigned int value = 0;

    value |= (unsigned char)base_address[offset];
    value |= ((unsigned char)base_address[offset + 1]) << 8;
    value |= ((unsigned char)base_address[offset + 2]) << 16;
    value |= ((unsigned char)base_address[offset + 3]) << 24;

    return value;
}

/*---------------------------------------------------------------*/
/* Some lab files use read_word name */
unsigned int read_word(const char *base_address, int offset)
{
    return read_dword(base_address, offset);
}

//---------------------------------------------------------------
void memory_dump(const char *base_address, const int offset, unsigned int dumpsize)
{
    unsigned int i, j;

    if (dumpsize < MIN_DUMP_SIZE)
        dumpsize = MIN_DUMP_SIZE;

    if (dumpsize > MEM_SIZE)
        dumpsize = MEM_SIZE;


    for (i = 0; i < dumpsize; i += DUMP_LINE)
    {
        printf("%08X  ", offset + i);

        // HEX
        for (j = 0; j < DUMP_LINE; j++)
        {
            printf("%02X ", (unsigned char)base_address[offset + i + j]);
        }

        printf(" ");

        // ASCII
        for (j = 0; j < DUMP_LINE; j++)
        {
            unsigned char c = base_address[offset + i + j];

            if (c >= 0x20 && c <= 0x7E)
                printf("%c", c);
            else
                printf(".");
        }

        printf("\n");
    }
}

//---------------------------------------------------------------
void setup_memory()
{
    char *mem = init_memory();
    char option = 0;
    unsigned int offset, dumpsize;
    unsigned int dword_data;
    char temp;

    do {
        if (option != '\n') {
            puts(menu);
            printf("\nBase Address: %p\n", mem);
            puts("Select option:");
        }

        option = getchar();

        switch (option)
        {
            case '1':
                printf("Enter offset (HEX): ");
                scanf("%x", &offset);
                printf("Enter 32-bit data (HEX): ");
                scanf("%x", &dword_data);
                write_dword(mem, offset, dword_data);
                break;

            case '2':
                printf("Enter offset (HEX): ");
                scanf("%x", &offset);
                read_byte(mem, offset);
                break;

            case '3':
                printf("Enter offset (HEX): ");
                scanf("%x", &offset);
                read_dword(mem, offset);
                break;

            case '4':
                printf("Enter offset (HEX): ");
                scanf("%x", &offset);
                printf("Enter dump size (256�1024): ");
                scanf("%u", &dumpsize);
                memory_dump(mem, offset, dumpsize);
                break;

            case 'e':
            case 'E':
                printf("Exiting...\n");
                free_memory(mem);
                return;

            default:
                break;
        }

        while ((temp = getchar()) != '\n' && temp != EOF);

    } while (1);
}
