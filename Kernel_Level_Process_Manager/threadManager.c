#include "dataTypesTm.h"

int tQuOvrFlow(int tState)
{
if (tState == 1)
{
if ((initCounNewTd - endCounNewTd) >= 19 || (endCounNewTd - initCounNewTd) >= 19)
return 1;
return 0;
}
else if (tState == 2)
{
if ((initCounReadyTd - endCounReadyTd) >= 19 || (endCounReadyTd - initCounReadyTd) >= 19)
return 1;
return 0;
}
else if (tState == 3)
{
if ((initCounRunningTd - endCounRunningTd) >= 19 || (endCounRunningTd - initCounRunningTd) >= 19)
return 1;
return 0;
}
else if (tState == 4)
{
if ((initCounwaitTDingTd - endCounwaitTDingTd) >= 19 || (endCounwaitTDingTd - initCounwaitTDingTd) >= 19)
return 1;
return 0;
}
else if (tState == 5)
{
if ((initCounDoneTd - endCounDoneTd) >= 19 || (endCounDoneTd - initCounDoneTd) >= 19)
return 1;
return 0;
}
}

int tQuUnflo(int tState)
{
if (tState == 1)
{
if ((initCounNewTd - endCounNewTd) == 0)
return 1;
return 0;
}

if (tState == 2)
{
if ((initCounReadyTd - endCounReadyTd) == 0)
return 1;
return 0;
}

if (tState == 3)
{
if ((initCounRunningTd - endCounRunningTd) == 0)
return 1;
return 0;
}
if (tState == 4)
{
if ((initCounwaitTDingTd - endCounwaitTDingTd) == 0)
return 1;
return 0;
}
if (tState == 5)
{
if ((initCounDoneTd - endCounDoneTd) == 0)
return 1;
return 0;
}
}

void enqueTd(char tid, char tPid, char tsw, char tdReg0, char tdReg1, char tdReg2, int tState)
{
if (tState == 1)
{
if (tQuOvrFlow(1) == 0)
{
if (tFrontNew == 0)
{
endCounNewTd = (endCounNewTd + 1) % THREAD_COUNT_LIMIT;
newTcb[endCounNewTd].tid = tid;
newTcb[endCounNewTd].tPid = tPid;
newTcb[endCounNewTd].tsw = tsw;
newTcb[endCounNewTd].tdReg[0] = tdReg0;
newTcb[endCounNewTd].tdReg[1] = tdReg1;
newTcb[endCounNewTd].tdReg[2] = tdReg2;
tFrontNew = &newTcb[endCounNewTd];

tRearNew = tFrontNew;
}
else
{
endCounNewTd = (endCounNewTd + 1) % THREAD_COUNT_LIMIT;

newTcb[endCounNewTd].tid = tid;
newTcb[endCounNewTd].tPid = tPid;
newTcb[endCounNewTd].tsw = tsw;
newTcb[endCounNewTd].tdReg[0] = tdReg0;
newTcb[endCounNewTd].tdReg[1] = tdReg1;
newTcb[endCounNewTd].tdReg[2] = tdReg2;
tRearNew->nextTcb = &newTcb[endCounNewTd];
tRearNew->nextTcb->prevTcb = tRearNew;
tRearNew = &newTcb[endCounNewTd];
}
}

}

else if (tState == 3)
{
if (tQuOvrFlow(3) == 0)
{
if (tFrontRunning == 0)
{
endCounRunningTd = (endCounRunningTd + 1) % THREAD_COUNT_LIMIT;
runningTcb[endCounRunningTd].tid = tid;
runningTcb[endCounRunningTd].tPid = tPid;
runningTcb[endCounRunningTd].tsw = tsw;
runningTcb[endCounRunningTd].tdReg[0] = tdReg0;
runningTcb[endCounRunningTd].tdReg[1] = tdReg1;
runningTcb[endCounRunningTd].tdReg[2] = tdReg2;
tFrontRunning = &runningTcb[endCounRunningTd];
tRearRunning = tFrontRunning;
// videoPointerTd[prtLocatorTd++] = ‘H’;
// videoPointerTd[prtLocatorTd++] = 0x07;
// videoPointerTd[prtLocatorTd++] = ' ';
// videoPointerTd[prtLocatorTd++] = 0x07;
}
else
{
endCounRunningTd = (endCounRunningTd + 1) % THREAD_COUNT_LIMIT;

runningTcb[endCounRunningTd].tid = tid;
runningTcb[endCounRunningTd].tPid = tPid;
runningTcb[endCounRunningTd].tsw = tsw;
runningTcb[endCounRunningTd].tdReg[0] = tdReg0;
runningTcb[endCounRunningTd].tdReg[1] = tdReg1;
runningTcb[endCounRunningTd].tdReg[2] = tdReg2;
tRearRunning->nextTcb = &runningTcb[endCounRunningTd];
tRearRunning->nextTcb->prevTcb = tRearRunning;
tRearRunning = &runningTcb[endCounRunningTd];
}
}
}
else if (tState == 4)
{
if (tQuOvrFlow(4) == 0)
{
if (tFrontWaiting == 0)
{
endCounwaitTDingTd = (endCounwaitTDingTd + 1) % THREAD_COUNT_LIMIT;
waitingTcb[endCounwaitTDingTd].tid = tid;
waitingTcb[endCounwaitTDingTd].tPid = tPid;
waitingTcb[endCounwaitTDingTd].tsw = tsw;
waitingTcb[endCounwaitTDingTd].tdReg[0] = tdReg0;
waitingTcb[endCounwaitTDingTd].tdReg[1] = tdReg1;
waitingTcb[endCounwaitTDingTd].tdReg[2] = tdReg2;
tFrontWaiting = &waitingTcb[endCounwaitTDingTd];
tRearWaiting = tFrontWaiting;
}
else
{
endCounwaitTDingTd = (endCounwaitTDingTd + 1) % THREAD_COUNT_LIMIT;

waitingTcb[endCounwaitTDingTd].tid = tid;
waitingTcb[endCounwaitTDingTd].tPid = tPid;
waitingTcb[endCounwaitTDingTd].tsw = tsw;
waitingTcb[endCounwaitTDingTd].tdReg[0] = tdReg0;
waitingTcb[endCounwaitTDingTd].tdReg[1] = tdReg1;
waitingTcb[endCounwaitTDingTd].tdReg[2] = tdReg2;
tRearWaiting->nextTcb = &waitingTcb[endCounwaitTDingTd];
tRearWaiting = &waitingTcb[endCounwaitTDingTd];
tRearWaiting->nextTcb->prevTcb = tRearWaiting;
}
}
}
else if (tState == 5)
{
if (tQuOvrFlow(5) == 0)
{
if (tFrontDone == 0)
{
endCounDoneTd = (endCounDoneTd + 1) % THREAD_COUNT_LIMIT;
doneTcb[endCounDoneTd].tid = tid;
doneTcb[endCounDoneTd].tPid = tPid;
doneTcb[endCounDoneTd].tsw = tsw;
doneTcb[endCounDoneTd].tdReg[0] = tdReg0;
doneTcb[endCounDoneTd].tdReg[1] = tdReg1;
doneTcb[endCounDoneTd].tdReg[2] = tdReg2;
tFrontDone = &doneTcb[endCounDoneTd];
tRearDone = tFrontDone;
}
else
{
endCounDoneTd = (endCounDoneTd + 1) % THREAD_COUNT_LIMIT;

doneTcb[endCounDoneTd].tid = tid;
doneTcb[endCounDoneTd].tPid = tPid;
doneTcb[endCounDoneTd].tsw = tsw;
doneTcb[endCounDoneTd].tdReg[0] = tdReg0;
doneTcb[endCounDoneTd].tdReg[1] = tdReg1;
doneTcb[endCounDoneTd].tdReg[2] = tdReg2;
tRearDone->nextTcb = &doneTcb[endCounDoneTd];
tRearDone = &doneTcb[endCounDoneTd];
tRearDone->nextTcb->prevTcb = tRearDone;
}
}
}
}
struct threadControlBlock* deleteTd(char tid, int tState)
{
if (tState == 1)
{
int m = 0;
tcbNode*currTd= tFrontNew;
int findTd = 1;
struct threadControlBlock *tempTcb_1;
int tempTcb_2 = initCounNewTd;
if (tQuUnflo(1) == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = tFrontNew;
m++; initCounNewTd++; tFrontNew = tFrontNew->nextTcb;
newTcb[initCounNewTd].prevTcb = 0;
}
else if (tRearNew->tid == tid)
{
tempTcb_1 = tRearNew;
endCounNewTd--;
tRearNew = tRearNew->prevTcb;
newTcb[endCounNewTd].nextTcb = 0;
}
else if (currTd->nextTcb == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = currTd;
initCounNewTd = -1;
}

}
else
{
while (currTd->nextTcb != 0 && findTd == 1)
{
m++; tempTcb_2++;
if (currTd->nextTcb->tid == tid)
{
tempTcb_1 = currTd->nextTcb;
findTd = 0;
}
else
currTd= currTd->nextTcb;
}

if (findTd == 0)
{
int i;
for (i = m; i < endCounNewTd - 1; i++) { newTcb[i] = newTcb[i + 1]; }
endCounNewTd--;
newTcb[endCounNewTd].nextTcb = 0;

}
}
}

return tempTcb_1;
}
else if (tState == 3)
{
int m = 0;
tcbNode*currTd= tFrontRunning;
int findTd = 1;
struct threadControlBlock*tempTcb_1;
int tempTcb_2 = initCounReadyTd;
if (tQuUnflo(3) == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = tFrontRunning;
m++; initCounReadyTd++; tFrontRunning = tFrontRunning->nextTcb;
runningTcb[initCounReadyTd].prevTcb = 0;
}
else if (tRearRunning->tid == tid)
{
tempTcb_1 = tRearRunning;
endCounRunningTd--;
tRearRunning = tRearRunning->prevTcb;
runningTcb[endCounRunningTd].nextTcb = 0;
}
else if (currTd->nextTcb == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = currTd;
initCounReadyTd = -1;
}

}
else
{
while (currTd->nextTcb != 0 && findTd == 1)
{
m++; tempTcb_2++;
if (currTd->nextTcb->tid == tid)
{
tempTcb_1 = currTd->nextTcb;
findTd = 0;
}
else
currTd= currTd->nextTcb;
}

if (findTd == 0)
{
int i;
for (i = m; i < endCounRunningTd - 1; i++) { runningTcb[i] = runningTcb[i + 1]; }
endCounRunningTd--;
runningTcb[endCounRunningTd].nextTcb = 0;

}
}
}

return tempTcb_1;
}
else if (tState == 4)
{
int m = 0;
tcbNode*currTd= tFrontWaiting;
int findTd = 1;
struct threadControlBlock*tempTcb_1;
int tempTcb_2 = initCounwaitTDingTd;
if (tQuUnflo(1) == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = tFrontWaiting;
m++; initCounwaitTDingTd++; tFrontWaiting = tFrontWaiting->nextTcb;
waitingTcb[initCounwaitTDingTd].prevTcb = 0;
}
else if (tRearWaiting->tid == tid)
{
tempTcb_1 = tRearWaiting;
endCounwaitTDingTd--;
tRearWaiting = tRearWaiting->prevTcb;
waitingTcb[endCounwaitTDingTd].nextTcb = 0;
}
else if (currTd->nextTcb == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = currTd;
initCounwaitTDingTd = -1;
}

}
else
{
while (currTd->nextTcb != 0 && findTd == 1)
{
m++; tempTcb_2++;
if (currTd->nextTcb->tid == tid)
{
tempTcb_1 = currTd->nextTcb;
findTd = 0;
}
else
currTd= currTd->nextTcb;
}

if (findTd == 0)
{
int i;
for (i = m; i < endCounwaitTDingTd - 1; i++) { waitingTcb[i] = waitingTcb[i + 1]; }
endCounwaitTDingTd--;
waitingTcb[endCounwaitTDingTd].nextTcb = 0;

}
}
}

return tempTcb_1;
}
else if (tState == 5)
{
int m = 0;
tcbNode*currTd= tFrontDone;
int findTd = 1;
struct threadControlBlock*tempTcb_1;
int tempTcb_2 = initCounDoneTd;
if (tQuUnflo(1) == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = tFrontDone;
m++; initCounDoneTd++; tFrontDone = tFrontDone->nextTcb;
doneTcb[initCounDoneTd].prevTcb = 0;
}
else if (tRearDone->tid == tid)
{
tempTcb_1 = tRearDone;
endCounDoneTd--;
tRearDone = tRearDone->prevTcb;
doneTcb[endCounDoneTd].nextTcb = 0;
}
else if (currTd->nextTcb == 0)
{
if (currTd->tid == tid)
{
tempTcb_1 = currTd;
initCounDoneTd = -1;
}

}
else
{
while (currTd->nextTcb != 0 && findTd == 1)
{
m++; tempTcb_2++;
if (currTd->nextTcb->tid == tid)
{
tempTcb_1 = currTd->nextTcb;
findTd = 0;
}
else
currTd= currTd->nextTcb;
}

if (findTd == 0)
{
int i;
for (i = m; i < endCounDoneTd - 1; i++) { doneTcb[i] = doneTcb[i + 1]; }
endCounDoneTd--;
doneTcb[endCounDoneTd].nextTcb = 0;

}
}
}

return tempTcb_1;
}
}
struct threadControlBlock* dequeTd(int tState)
{
if (tState == 1)
{

tcbNode*temp = tFrontNew;
tFrontNew = tFrontNew->nextTcb;
initCounNewTd = (initCounNewTd + 1) % THREAD_COUNT_LIMIT;
return temp;
}

else if (tState == 3)
{

tcbNode*temp = tFrontRunning;
tFrontRunning = tFrontRunning->nextTcb;
initCounReadyTd = (initCounReadyTd + 1) % THREAD_COUNT_LIMIT;
return temp;
}

else if (tState == 4)
{

tcbNode*temp = tFrontWaiting;
tFrontWaiting = tFrontWaiting->nextTcb;
initCounwaitTDingTd = (initCounwaitTDingTd + 1) % THREAD_COUNT_LIMIT;
return temp;
}

else if (tState == 5)
{

tcbNode*temp = tFrontDone;
tFrontDone = tFrontDone->nextTcb;
initCounDoneTd = (initCounDoneTd + 1) % THREAD_COUNT_LIMIT;
return temp;
}
}
struct threadControlBlock* tReturnHead(int tState)
{
if (tState == 1){ return tFrontNew; }
if (tState == 2){ return tFrontReady; }
if (tState == 3){ return tFrontRunning; }
if (tState == 4){ return tFrontWaiting; }
if (tState == 5){ return tFrontDone; }
}
struct threadControlBlock* tReturnTail(int tState)
{
if (tState == 1){ return tRearNew; }
if (tState == 2){ return tRearReady; }
if (tState == 3){ return tRearRunning; }
if (tState == 4){ return tRearWaiting; }
if (tState == 5){ return tRearDone; }
}

void listTd(int tState,int b)
{
if (tState == 1)
{
tcbNode*currTd= tFrontNew;
prtLocatorTd = b;
while (currTd!= 0)
{
videoPointerTd[prtLocatorTd++] = currTd->tid;
videoPointerTd[prtLocatorTd++] = 0x07;
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
currTd= currTd->nextTcb;
}

int tState = 0;
while (tState != 10)
{
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
tState++;
}
}

if (tState == 2)
{
if(!tQuUnflo(1))
{
videoPointerTd[prtLocatorTd++] = tReturnHead(1)->tid;
videoPointerTd[prtLocatorTd++] = 0x07;

}
}

if (tState == 3)
{

tcbNode*currTd= tFrontRunning;
prtLocatorTd = b;

int i;
while (currTd!= 0)
{
videoPointerTd[prtLocatorTd++] = currTd->tid;
videoPointerTd[prtLocatorTd++] = 0x07;
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
currTd= currTd->nextTcb;
}

int tState = 0;
while (tState != 10)
{
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
tState++;
}
}

if (tState == 4)
{

tcbNode*currTd= tFrontWaiting;
prtLocatorTd = b;
while (currTd!= 0)
{
videoPointerTd[prtLocatorTd++] = currTd->tid;
videoPointerTd[prtLocatorTd++] = 0x07;
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
currTd= currTd->nextTcb;
}

int tState = 0;
while (tState != 10)
{
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
tState++;
}
}

if (tState == 5)
{

tcbNode *currTd= tFrontDone;
prtLocatorTd = b;
while (currTd!= 0)
{
videoPointerTd[prtLocatorTd++] = currTd->tid;
videoPointerTd[prtLocatorTd++] = 0x07;
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
currTd= currTd->nextTcb;
}

int tState = 0;
while (tState != 10)
{
videoPointerTd[prtLocatorTd++] = ' ';
videoPointerTd[prtLocatorTd++] = 0x07;
tState++;
}
}
}

int sizeTd(int tState)
{
if (tState == 1)
{

return (endCounNewTd - initCounNewTd);
}
if (tState == 2)
{

return (endCounReadyTd - initCounReadyTd);
}
if (tState == 3)
{

return (endCounRunningTd - initCounReadyTd);
}
if (tState == 4)
{

return (endCounwaitTDingTd - initCounwaitTDingTd);
}
if (tState == 5)
{

return (endCounDoneTd - initCounDoneTd);
}
}

void initTdQ(int tState)
{
if (tState == 1)
{
initCounNewTd = endCounNewTd = -1;
tFrontNew = tRearNew = 0; int i;
for (i = 0; i < 20; i++)
{
newTcb[i].tid = -2;
newTcb[i].tPid = -2;
}
}
else if (tState == 2)
{
initCounReadyTd = endCounReadyTd = -1;
tFrontReady = tRearReady = 0; int i;
for (i = 0; i < 20; i++)
{
readyTcb[i].tid = -2;
readyTcb[i].tPid = -2;
}
}

else if (tState == 3)
{
initCounReadyTd = endCounRunningTd = -1;
tFrontRunning = tRearRunning = 0; int i;
for (i = 0; i < 20; i++)
{
runningTcb[i].tid = -2;
runningTcb[i].tPid = -2;
}
}

else if (tState == 4)
{
initCounwaitTDingTd = endCounwaitTDingTd = -1;
tFrontWaiting = tRearWaiting = 0; int i;
for (i = 0; i < 20; i++)
{
waitingTcb[i].tid = -2;
waitingTcb[i].tPid = -2;
}
}

else if (tState == 5)
{
initCounDoneTd = endCounDoneTd = -1;
tFrontDone = tRearDone = 0; int i;
for (i = 0; i < 20; i++)
{
doneTcb[i].tid = -2;
doneTcb[i].tPid = -2;
}
}
};

struct threadControlBlock* tempTcbQ;

int totalThread = 0;
void initTdQue()
{
initTdQ(1);
initTdQ(3);
initTdQ(4);
initTdQ(5);
}

void execTd()
{
tempTcbQ = dequeTd(1);
tNewSize--;

videoPointerTd[prtLocatorTd++] = tempTcbQ->tid;
videoPointerTd[prtLocatorTd++] = 0x07;

enqueTd(tempTcbQ->tid, tempTcbQ->tPid, tempTcbQ->tsw, tempTcbQ->tdReg[0],tempTcbQ->tdReg[1], tempTcbQ->tdReg[2], 3);
tRunningSize++;
}

int unwaitTd(int tid)
{
tempTcbQ = deleteTd(tid, 4);
tWaitingSize--;
enqueTd(tempTcbQ->tid, tempTcbQ->tPid, tempTcbQ->tsw, tempTcbQ->tdReg[0], tempTcbQ->tdReg[1], tempTcbQ->tdReg[2], 1);
tNewSize++;
return 0;
}

int eoQuantTd()
{
tempTcbQ = dequeTd(3);
tRunningSize--;
enqueTd(tempTcbQ->tid, tempTcbQ->tPid, tempTcbQ->tsw, tempTcbQ->tdReg[0],tempTcbQ->tdReg[1], tempTcbQ->tdReg[2], 1);
tNewSize++;
return 0;
}

int eolifeTd()
{
tempTcbQ = dequeTd(3);
tRunningSize--;
enqueTd(tempTcbQ->tid, tempTcbQ->tPid, tempTcbQ->tsw, tempTcbQ->tdReg[0],tempTcbQ->tdReg[1], tempTcbQ->tdReg[2], 5);
tDoneSize++;
return 0;
}

int waitTd()
{
tempTcbQ = dequeTd(3);
tRunningSize--;
enqueTd(tempTcbQ->tid, tempTcbQ->tPid, tempTcbQ->tsw, tempTcbQ->tdReg[0],tempTcbQ->tdReg[1], tempTcbQ->tdReg[2], 4);
tWaitingSize++;
return 0;
}