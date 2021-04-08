/* mastermind.h */                  /* Emanuele Piras -  matricola: 000001 */

#define MIN_LENGTH 3
#define MAX_LENGTH 5
#define MIN_COLORS 6
#define MAX_COLORS 8
#define DEF_LENGTH 4
#define DEF_COLORS 6
#define DEF_TRIES 10

#define HELP_S "\nUsage: %s [-d] [-h]\n",argv[0]
#define HELP_E "\n-d [Debug] prints out the secret code and adds a numeric output of pegs\n-h [Help]  this help\n\n"

#define CLEAR_SCREEN "\e[1;1H\e[2J"
#define COL_RESET "\033[0;0m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define HCYAN "\033[0;96m"
#define GREEN "\033[0;32m"
#define PURPLE "\033[0;35m"
#define RED "\033[0;31m"
#define HRED "\e[0;91m"
#define YELLOW "\033[0;33m"
#define HYELLOW "\033[0;93m"
#define BLACK_PEG "\u25CB "
#define NO_PEG "\u2715 "
#define PEG "\u25CF "
#define SPACER "::-:: "

struct SGame {
    _Bool bDups;
    _Bool* prgbCountFlags;
    int iSecretLength;
    int iColorsNum;
    int iMaxTries;
    int* prgiBlackPegs;
    int* prgiWhitePegs;
    char* prgcCode;
    char** prgcCodeBreakerTries;
};

typedef struct SGame SGame;

void exitOnErr(void);

void printMainMenu();
void printMasterMind();
void printColored(int iNumber, _Bool bPeg);
void printLegenda(int iColorsNum);
void celebrateGoodTimes();
void printSecret(SGame* pStheGame);
void printSettings(int iSecretLength, int iColorsNum, int iMaxTries, _Bool bDups);
void waitEnter();

int getChoice(int iMin, int iMax, _Bool bZeroLength);
int getTry(SGame* pStheGame, int iTry);
void genSecret(SGame* pStheGame);

int checkTry(SGame* pStheGame, int iTry);
void printGame(SGame* pStheGame, int iTry, _Bool bDebug);
void playGame(SGame* pStheGame, _Bool bDebug);

SGame* newGame(int iSecretLength, int iColorsNum, int iMaxTries, _Bool bDups);
void delGame(SGame* pStheGame);
