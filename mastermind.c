/*  mastermind.c */                      /* Emanuele Piras -  matricola: 000001 */

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "mastermind.h"

/*main function*/

int main(int argc, char *argv[]){

    _Bool bDebug=0;

    _Bool bDups=1;
    _Bool bRun=1;
    _Bool bUserSettings=0; // defaults

    int iChoice;
    int iSecretLength = DEF_LENGTH;
    int iColorsNum = DEF_COLORS;
    int iMaxTries = DEF_TRIES;

    int iOpt;
    while ((iOpt = getopt(argc, argv, ":d")) != -1) {

        if(iOpt=='d'){
            bDebug = 1;
            break;
        }
        fprintf(stderr, HELP_S);
        fprintf(stderr, HELP_E);
        exit(EXIT_FAILURE);
    }

    printf(CLEAR_SCREEN);

    while(bRun){
        SGame* pStheGame;

        printf(CLEAR_SCREEN);
        printMainMenu();
        
        iChoice=getChoice(1,4,0); // user choice

        switch(iChoice){

            case 1: /*play*/

                printf(CLEAR_SCREEN);
                printMasterMind();
                printf(GREEN" -> PLAY\n"COL_RESET);

                pStheGame=newGame(iSecretLength, iColorsNum, iMaxTries, bDups);
                genSecret(pStheGame);

                printSettings(pStheGame->iSecretLength,pStheGame->iColorsNum,pStheGame->iMaxTries,pStheGame->bDups);
                printLegenda(pStheGame->iColorsNum);

                playGame(pStheGame, bDebug);

                delGame(pStheGame);

                break;

            case 2: /*Settings*/ 

                printf(CLEAR_SCREEN);
                printMasterMind();
                printf(YELLOW" -> Settings\n"COL_RESET);
                printSettings(iSecretLength,iColorsNum,iMaxTries,bDups);
                printf("\n"YELLOW"1"COL_RESET" -> change\n\n"YELLOW"Enter"COL_RESET" to keep: ");
                int iUserChoice=getChoice(1,1,1);
                if(iUserChoice!=911)                                     //911 means no choice (default)
                    bUserSettings=iUserChoice;
                else
                    bUserSettings=0;
                if(bUserSettings){
                    printf("\nSecret code length\t(%d to %d)\t["YELLOW"%2d"COL_RESET"]  ",MIN_LENGTH,MAX_LENGTH,iSecretLength);
                    iUserChoice=getChoice(MIN_LENGTH,MAX_LENGTH,1);
                    if(iUserChoice!=911)                                     //911 means no choice (default)
                        iSecretLength=iUserChoice;
                    printf("Number of colors\t(%d or %d)\t["YELLOW"%2d"COL_RESET"]  ",MIN_COLORS,MAX_COLORS,iColorsNum);
                    iUserChoice=getChoice(MIN_COLORS,MAX_COLORS,1);
                    if(iUserChoice!=911)
                        iColorsNum=iUserChoice;
                    iMaxTries=(iSecretLength*iColorsNum/2)-2;
                    printf("Number of tries \t(adaptive)\t["YELLOW"%2d"COL_RESET"]",iMaxTries);
                    printf("\n\nDuplicated colors\n"YELLOW"0"COL_RESET" -> NO\n");
                    printf(YELLOW"1"COL_RESET" -> YES\t\t(0 or  1)\t["YELLOW"%2d"COL_RESET"]  ",bDups);
                    iUserChoice=getChoice(0,1,1); // 0 | 1 false | true
                    if(iUserChoice!=911)
                        bDups=iUserChoice;
                    printf(CLEAR_SCREEN);
                    printSettings(iSecretLength,iColorsNum,iMaxTries,bDups);
                    waitEnter();
	            }

                break;

            case 3: /*Instructions*/

                printf(CLEAR_SCREEN);
                printMasterMind();
                printf(HCYAN" -> Instructions\n\n"COL_RESET);
                printf("You have to guess the secret color combination, having a maximum number of attemps.\n");
                printf("Using the "YELLOW"Settings"COL_RESET" menu, you can change the length of the secret code,\n");
                printf("the number of possible colors, duplicated colors allowed or not.\n");
                printf(HCYAN"\nLegenda:\n\n"COL_RESET);
                printLegenda(DEF_COLORS);
                printf(COL_RESET);
                printf("\n\n%18s\n","Board sample");
                printf("  +-------------------+\n");
                printf("  | ");
                printColored('1',0); printColored('2',0); printColored('3',0); printColored('4',0); //numbers
                printf(SPACER);
                printf(BLACK_PEG""PEG);
                printf("|\n  | ");
                printColored('1',1); printColored('2',1); printColored('3',1); printColored('4',1); //pegs
                printf(SPACER);
                printf(PEG""NO_PEG);
                printf("|\n");
                printf("  +-------------------+\n");
                printf("%21s\n","1 3 6 2 as code\n");
                waitEnter();

                break;

            case 4: /*Quit*/

                printf("\nBye and thank you for playing ");
                printMasterMind();
                printf("!\n\n\n");
                bRun=0;

                break;

            default: // It mustn't arrive here

                printf("I can't believe it! This should never happen!"); 

                break;
        }
    }

	return 0;
}
