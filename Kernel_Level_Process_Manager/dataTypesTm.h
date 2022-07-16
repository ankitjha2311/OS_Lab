#define NUMBER_OF_REGISTERS_TM 3
#define THREAD_COUNT_LIMIT 20
#define TQUEUE_SIZE_LIMIT 21

unsigned int prtLocatorTd = 0;
char *videoPointerTd = (char*)0xb8000;
struct threadControlBlock {
char tid;
char tPid;
char tsw;
char tdReg[NUMBER_OF_REGISTERS_TM];
int priorityTd;
struct threadControlBlock *nextTcb, *prevTcb;
};
struct threadControlBlock newTcb[THREAD_COUNT_LIMIT];
struct threadControlBlock readyTcb[THREAD_COUNT_LIMIT];
struct threadControlBlock runningTcb[THREAD_COUNT_LIMIT];
struct threadControlBlock waitingTcb[THREAD_COUNT_LIMIT];
struct threadControlBlock doneTcb[THREAD_COUNT_LIMIT];

typedef struct threadControlBlock tcbNode;
tcbNode *tFrontNew = 0, *tFrontReady = 0,  *tFrontRunning = 0,*tFrontWaiting = 0,*tFrontDone = 0;
tcbNode *tRearNew = 0,*tRearReady = 0, *tRearRunning = 0, *tRearWaiting = 0, *tRearDone = 0;

int tNewSize = 0,tReadySize = 0,tRunningSize = 0,tWaitingSize = 0,tDoneSize = 0;
int initCounNewTd = -1,initCounReadyTd = -1,initCounRunningTd = -1,initCounwaitTDingTd = -1,initCounDoneTd = -1;
int endCounNewTd = -1,endCounReadyTd = -1,endCounRunningTd = -1,endCounwaitTDingTd = -1,endCounDoneTd = -1;
