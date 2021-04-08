/* mastermind_data_struct.c */                   /* Emanuele Piras -  matricola: 000001 */

#include <stdlib.h>
#include <stdio.h>
#include "mastermind.h"

SGame* newGame(int iSecretLength, int iColorsNum, int iMaxTries, _Bool bDups){
    SGame* pStruct = malloc (sizeof (SGame)); // Try to allocate data structures
    if (pStruct == NULL)
        exitOnErr();

    pStruct->prgcCode = malloc (iSecretLength * sizeof (char)); // Try to allocate code vector, exit if fail.
    if (pStruct->prgcCode == NULL)
        exitOnErr();
    
    pStruct->prgiBlackPegs = calloc (iMaxTries, sizeof (int)); // prgiBlackPegs 0 filled
    if (pStruct->prgiBlackPegs == NULL)
        exitOnErr();
    
    pStruct->prgiWhitePegs = calloc (iMaxTries, sizeof (int)); // prgiWhitePegs 0 filled
    if (pStruct->prgiWhitePegs == NULL)
        exitOnErr();
    
    pStruct->prgbCountFlags = malloc (iSecretLength * sizeof (_Bool)); // flags for white pegs check. will be inizialized in other function
    if (pStruct->prgbCountFlags == NULL)
        exitOnErr();
    
    pStruct->prgcCodeBreakerTries = malloc (iMaxTries * sizeof (char*)); // player attempts matrix
    if (pStruct->prgcCodeBreakerTries == NULL)
        exitOnErr();
    for(int i=0; i<iMaxTries; i++){
        pStruct->prgcCodeBreakerTries[i] = calloc (iSecretLength, sizeof (char)); // 0 filled
        if (pStruct->prgcCodeBreakerTries[i] == NULL)
            exitOnErr();
    }

    pStruct->iSecretLength = iSecretLength;    // Set values and return pointer
    pStruct->iColorsNum = iColorsNum;
    pStruct->iMaxTries = iMaxTries;
    pStruct->bDups = bDups;

    return pStruct;
}

void delGame(SGame* pSTheGame){ //no check before deleting because of the exit on allocation failure

    for(int i=0; i<pSTheGame->iMaxTries; i++)
        free(pSTheGame->prgcCodeBreakerTries[i]);
    free(pSTheGame->prgcCodeBreakerTries);

    free(pSTheGame->prgcCode);
    free(pSTheGame->prgiBlackPegs);
    free(pSTheGame->prgiWhitePegs);
    free(pSTheGame->prgbCountFlags);

    free(pSTheGame);
}

void exitOnErr(){
    fprintf(stderr, "\nERROR: dynamic memory allocation failed!\n\n");
    exit(-1); // it uses a specific code for memory allocation failures
}
