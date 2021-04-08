/* mastermind_functions.c */                     /* Emanuele Piras -  matricola: 000001 */

#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mastermind.h"

void waitEnter(){
    printf("\nPress "CYAN"ENTER"COL_RESET" to continue...");
    while( getchar() != '\n' );
}

void printMasterMind(){
    printf(RED"M"CYAN"aster"RED"M"CYAN"ind"COL_RESET);
}

void printMainMenu(){
    printMasterMind();
    printf(GREEN"\n\n1 - Play\n");
    printf(YELLOW"2 - Settings\n");
    printf(HCYAN"3 - Instructions\n");
    printf(RED"4 - Quit\n\n"COL_RESET);
    printf("Make your choice: ");
}

void printLegenda(int iColorsNum){
    printf(BLACK_PEG);
    printf("\tright color and position\n");
    printf(PEG);
    printf("\tright color in wrong position\n");
    printf(NO_PEG);
    printf("\tmissing color\n");
    printf(RED"Q"COL_RESET"\tto quit the match\n");
    printf("Colors  ");
    for(int i=1; i<=iColorsNum; i++){
        printColored(i+'0',0);                  //0 print a colored number (ascii)
    }
    printf("\n");
}

void printSecret(SGame* pSTheGame){
    printf("\n%11s\n%4s","The code","");
    int i;
    for(i=0; i<pSTheGame->iSecretLength; i++){
        printColored(pSTheGame->prgcCode[i],0); //print a colored number
    }
    printf("\n%4s","");
    for(i=0; i<pSTheGame->iSecretLength; i++){
        printColored(pSTheGame->prgcCode[i],1); //print a colored pin
    }
    printf("\n");
}

void printSettings(int iSecretLength, int iColorsNum, int iMaxTries, _Bool bDups) {
    printf("\nSecret code length\t ["YELLOW"%2d"COL_RESET"]\n",iSecretLength);
    printf("Number of colors\t ["YELLOW"%2d"COL_RESET"]\n",iColorsNum);
    printf("Number of attempts\t ["YELLOW"%2d"COL_RESET"]\n",iMaxTries);
    if(bDups)
        printf("Duplicated colors\t["YELLOW"YES"COL_RESET"]\n");
    else
        printf("Duplicated colors\t ["YELLOW"NO"COL_RESET"]\n");
}

void printColored(int iNumber, _Bool bPeg){

    switch(iNumber){
        case '1':
            bPeg ? printf(GREEN PEG) : printf(GREEN"1 ");
            break;

        case '2':
            bPeg ? printf(YELLOW PEG) : printf(YELLOW"2 ");
            break;

        case '3':
            bPeg ? printf(HCYAN PEG) : printf(HCYAN"3 ");
            break;

        case '4':
            bPeg ? printf(RED PEG) : printf(RED"4 ");
            break;

        case '5':
            bPeg ? printf(PURPLE PEG) : printf(PURPLE"5 ");
            break;

        case '6':
            bPeg ? printf(CYAN PEG) : printf(CYAN"6 ");
            break;

        case '7':
            bPeg ? printf(HYELLOW PEG) : printf(HYELLOW"7 ");
            break;

        case '8':
            bPeg ? printf(BLUE PEG) : printf(BLUE"8 ");
            break;
    }
    printf(COL_RESET);
}

void printGame(SGame* pSTheGame, int iTry, _Bool bDebug){

    int pPegs,noPegs,pNoPegs,pWhitePegs,pBlackPegs;
    int iHalfLength=pSTheGame->iSecretLength/2;
    _Bool bIsOdd=pSTheGame->iSecretLength%2;
    int iBoardWidth=(pSTheGame->iSecretLength *3) +5 +2 +bIsOdd; //3 '-' per char + spacer (5) + 1 if odd

    printf("\n");
    for(int i=0; i<=iTry; i++){
        pPegs=pBlackPegs=pWhitePegs=pNoPegs=0;
        noPegs=pSTheGame->iSecretLength - pSTheGame->prgiBlackPegs[i] - pSTheGame->prgiWhitePegs[i];
        if(i==0){
            printf("  +");
            for(int j=0; j<iBoardWidth; j++)
                printf("-");
            printf("+\n");
        }
        printf("  | ");
        for(int j=0; j<pSTheGame->iSecretLength; j++){
            printColored(pSTheGame->prgcCodeBreakerTries[i][j],0); //print a colored number
        }
        printf(SPACER);
        while(pPegs<iHalfLength && pBlackPegs<pSTheGame->prgiBlackPegs[i]){
            printf(BLACK_PEG);
            pPegs++;
            pBlackPegs++;
        }
        while(pPegs<iHalfLength && pWhitePegs<pSTheGame->prgiWhitePegs[i]){
            printf(PEG);
            pPegs++;
            pWhitePegs++;
        }
        while(pPegs<iHalfLength && pNoPegs<noPegs){
            printf(NO_PEG);
            pPegs++;
            pNoPegs++;
        }
        if(bIsOdd)
            printf("  ");
        printf("|\n%-2d| ",pSTheGame->iMaxTries -(i+1)); // print remaining attempts
        for(int j=0; j<pSTheGame->iSecretLength; j++){
            printColored(pSTheGame->prgcCodeBreakerTries[i][j],1); //print a colored pin
        }
        printf(SPACER);
        while(pPegs<pSTheGame->iSecretLength && pBlackPegs<pSTheGame->prgiBlackPegs[i]){
            printf(BLACK_PEG);
            pPegs++;
            pBlackPegs++;
        }
        while(pPegs<pSTheGame->iSecretLength && pWhitePegs<pSTheGame->prgiWhitePegs[i]){
            printf(PEG);
            pPegs++;
            pWhitePegs++;
        }
        while(pPegs<pSTheGame->iSecretLength && pNoPegs<noPegs){
            printf(NO_PEG);
            pPegs++;
            pNoPegs++;
        }
        printf("|\n  +");
        for(int j=0; j<iBoardWidth; j++){
            printf("-");
        }
        printf("+\n");
    }
    if(bDebug){
        printf("\nblack pegs: %d ",pSTheGame->prgiBlackPegs[iTry]);
        printf("- white pegs: %d",pSTheGame->prgiWhitePegs[iTry]);
    }
}

void genSecret(SGame* pSTheGame){

    srand(time(NULL));                                        //It uses current time to create a seed for pseudo-random generator

    int i=0;
    while( i<pSTheGame->iSecretLength ){                         // number of cycle can vary if bDups == 0
        pSTheGame->prgcCode[i] = rand() % pSTheGame->iColorsNum+'0'+1; // rand generate from 0 and RAND_MAX (at least 32767)
        if(!pSTheGame->bDups)                                    // rand mod (max colors +1) ascii converted
        {
            int j=i;
            while( j>0 ){
                if(pSTheGame->prgcCode[i] == pSTheGame->prgcCode[j-1]){     // seach backwards in the array elements
                    i--;    //back to the same element
                    break;
                }
                j--;
            }
        }
        i++;
    }
}

void getString(char* rgBuffer) {

    char* rgCleanStr=rgBuffer;
    fgets(rgBuffer, 128, stdin);

    for (size_t i=0,j=0; i<strlen(rgBuffer); i++)    //clean up anything but numbers, exit char and terminator
    {
        if((rgBuffer[i]>='0' && rgBuffer[i]<='9') || rgBuffer[i]=='Q' || rgBuffer[i]=='q')
            rgCleanStr[j++]=rgBuffer[i];

        else if(rgBuffer[i]=='\n')
            rgCleanStr[j++]='\0';
    }
}

int getChoice(int iMin, int iMax, _Bool bZeroLength) {

    char rgBuffer[128];
    int iNumber;

    while(1){    // true
        getString(rgBuffer);

        if(strlen(rgBuffer)==0 && bZeroLength){
            iNumber=911;
            break;
        }
        
        if ( sscanf(rgBuffer, "%d", &iNumber ) == 1 && (iNumber >= iMin && iNumber <= iMax) )
            break;

        printf(CYAN"\nInvalid input! ->"COL_RESET" Insert a value from %d to %d: ", iMin, iMax);
    }
    return iNumber;
}

int getTry(SGame* pSTheGame, int iTry){

    char rgBuffer[128];
    int iRun = 1;

    while (iRun==1) {

        getString(rgBuffer); // elements contain ascii

        if(rgBuffer[0] == 'Q' || rgBuffer[0] == 'q') // when the user wantis to leave before finishing the match
            iRun=2;
        else if((int)strlen(rgBuffer) != pSTheGame->iSecretLength){ //size_t to int
            printf(CYAN"\nInvalid input! ->"COL_RESET" Enter a %d digits code: ",pSTheGame->iSecretLength);
            iRun=1;
        }else{
            iRun=0;
            int i=0;
            while(i<pSTheGame->iSecretLength){
                
                if(rgBuffer[i] < 1+'0' || rgBuffer[i] > pSTheGame->iColorsNum+'0'){ // ascii
                    printf(CYAN"\nInvalid input! ->"COL_RESET" Color range is [%d to %d]\n\nGuess the secret code: ",1,pSTheGame->iColorsNum);
                    iRun = 1;
                    break;
                }
                if(!pSTheGame->bDups){
                    int j=0;
                    while( j<pSTheGame->iSecretLength){
                        if(rgBuffer[i]==rgBuffer[j] && i!=j){
                            printf(CYAN"\nInvalid input! ->"COL_RESET" Duplicated color\nGuess the secret code: ");
                            iRun = 1;
                            break;
                        }
                    j++;
                    }
                }
                if(iRun)
                    break;
                pSTheGame->prgcCodeBreakerTries[iTry][i]=rgBuffer[i]; // ascii
                i++;
            }

        }
    }
    return iRun;
}

int checkTry(SGame* pSTheGame, int iTry){

    _Bool bResult=0;

    for(int i=0; i<pSTheGame->iSecretLength; i++){                 //looking for black pegs
        pSTheGame->prgbCountFlags[i]=0;                               //reset flags
        if(pSTheGame->prgcCodeBreakerTries[iTry][i]==pSTheGame->prgcCode[i]){
            pSTheGame->prgiBlackPegs[iTry]++;
            pSTheGame->prgbCountFlags[i]=1;
        }
    }

    if(pSTheGame->prgiBlackPegs[iTry] == pSTheGame->iSecretLength)     // then look for the white pegs
        bResult = 1;
    else
    {
        for(int i=0; i<pSTheGame->iSecretLength; i++){ 
            if(pSTheGame->prgcCodeBreakerTries[iTry][i] != pSTheGame->prgcCode[i]){
                int j=0;
                while(j<pSTheGame->iSecretLength){
                    if( pSTheGame->prgcCodeBreakerTries[iTry][i] == pSTheGame->prgcCode[j] && !pSTheGame->prgbCountFlags[j] ){
                        pSTheGame->prgbCountFlags[j]=1;
                        pSTheGame->prgiWhitePegs[iTry]++;
                        break;
                    }
                    j++;
                }
            }
        }
    }

    return bResult;
}

void playGame(SGame* pSTheGame, _Bool bDebug){
    int iTry=0;
    _Bool bResult=0;
    while(iTry<pSTheGame->iMaxTries && !bResult){
        printf("\n");
        if(bDebug){
            printSecret(pSTheGame);
            printf(RED"\nDebug mode -> "COL_RESET"Insert the combination"RED":~$ "COL_RESET);
        }
        else{
            if(iTry == pSTheGame->iMaxTries - 1)
                printf(HRED"Last chance! ");
            printf("Guess the secret code: "COL_RESET);
        }
        int iRetVal=getTry(pSTheGame, iTry);
        if(iRetVal==2){
            printf(GREEN"\nQuitting the match!\n"COL_RESET);
            waitEnter();
            break;
        }
        printf(CLEAR_SCREEN);
        printMasterMind();
        printf(GREEN" -> PLAY\n"COL_RESET);
        printSettings(pSTheGame->iSecretLength,pSTheGame->iColorsNum,pSTheGame->iMaxTries,pSTheGame->bDups);
        printLegenda(pSTheGame->iColorsNum);
        bResult=checkTry(pSTheGame, iTry);
        printGame(pSTheGame, iTry, bDebug);
        if(bResult){
            celebrateGoodTimes();
            printSecret(pSTheGame);
            waitEnter();
        }
        else if(!bResult && iTry==pSTheGame->iMaxTries-1){
            iTry++;
            printSecret(pSTheGame);
            printf(YELLOW"\nYou lost this match, but don't give up. Try one more time!\n"COL_RESET);
            waitEnter();
        }
        iTry++;
    }
}

void celebrateGoodTimes(){
    printf(GREEN"\n\nReally good, you've done it!\n"COL_RESET); 
    sleep(3);
    char rgMessage[256]="\n";
    char* prgStrings[5]={"YOU"," WON"," THIS"," MATCH"," !!!!"};
    printf(RED); 
    for (int i=0; i<5; i++){
        printf(CLEAR_SCREEN);
        strcat (rgMessage, prgStrings[i]);
        printf("%s\n",rgMessage);
        usleep(500000);
    }
    usleep(500000);
    printf(GREEN"\nLets play again!\n"COL_RESET);
    usleep(500000);
}
