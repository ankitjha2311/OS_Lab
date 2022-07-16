#define NUMBER_OF_REGISTERS 3
#define PROCESS_COUNT_LIMIT 20
#define QUEUE_SIZE_LIMIT 21

unsigned int prtLocator = 0;
char *videoPointer = (char*)0xb8000;
struct processControlBlock {
char pid;
char psw;
char page_table;
char regs[NUMBER_OF_REGISTERS];
int priority;
struct processControlBlock *next, *prev;
};
struct processControlBlock newPcb[PROCESS_COUNT_LIMIT];
struct processControlBlock readyPcb[PROCESS_COUNT_LIMIT];
struct processControlBlock runningPcb[PROCESS_COUNT_LIMIT];
struct processControlBlock waitingPcb[PROCESS_COUNT_LIMIT];
struct processControlBlock donePcb[PROCESS_COUNT_LIMIT];

typedef struct processControlBlock pcbNode;
pcbNode *frontNew = 0, *frontReady = 0,  *frontRunning = 0,*frontWaiting = 0,*frontDone = 0;
pcbNode *rearNew = 0,*rearReady = 0, *rearRunning = 0, *rearWaiting = 0, *rearDone = 0;

int newSize = 0,readySize = 0,runningSize = 0,waitingSize = 0,doneSize = 0;
int initCounNew = -1,initCounReady = -1,initCounRunning = -1,initCounWaiting = -1,initCounDone = -1;
int endCounNew = -1,endCounReady = -1,endCounRunning = -1,endCounWaiting = -1,endCounDone = -1;


