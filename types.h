//
// Created by Hervé Paulino on 19/03/2022.
//

#ifndef CAOSS_TYPES_H
#define CAOSS_TYPES_H

typedef unsigned char byte;
typedef unsigned short caoss_word;

typedef caoss_word caoss_address;
typedef caoss_word caoss_instruction;

#define MAX_MEM_SIZE (1 << 10)
#define NREGISTERS (1 << 3)

#define CAOSS_ERROR "caoss error"

#endif //CAOSS_TYPES_H
