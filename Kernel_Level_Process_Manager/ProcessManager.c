#include "datatypes.h"

int queueOveflow(int state)
{
if (state == 1)
{
if ((initCounNew - endCounNew) >= 19 || (endCounNew - initCounNew) >= 19)
return 1;
return 0;
}
else if (state == 2)
{
if ((initCounReady - endCounReady) >= 19 || (endCounReady - initCounReady) >= 19)
return 1;
return 0;
}
else if (state == 3)
{
if ((initCounRunning - endCounRunning) >= 19 || (endCounRunning - initCounRunning) >= 19)
return 1;
return 0;
}
else if (state == 4)
{
if ((initCounWaiting - endCounWaiting) >= 19 || (endCounWaiting - initCounWaiting) >= 19)
return 1;
return 0;
}
else if (state == 5)
{
if ((initCounDone - endCounDone) >= 19 || (endCounDone - initCounDone) >= 19)
return 1;
return 0;
}
}

int queueUnderflow(int state)
{
if (state == 1)
{
if ((initCounNew - endCounNew) == 0)
return 1;
return 0;
}

if (state == 2)
{
if ((initCounReady - endCounReady) == 0)
return 1;
return 0;
}

if (state == 3)
{
if ((initCounRunning - endCounRunning) == 0)
return 1;
return 0;
}
if (state == 4)
{
if ((initCounWaiting - endCounWaiting) == 0)
return 1;
return 0;
}
if (state == 5)
{
if ((initCounDone - endCounDone) == 0)
return 1;
return 0;
}
}

void enque(char pid, char psw, char page_table, char regs0, char regs1, char regs2, int state)
{
if (state == 1)
{
if (queueOveflow(1) == 0)
{
if (frontNew == 0)
{
endCounNew = (endCounNew + 1) % PROCESS_COUNT_LIMIT;
newPcb[endCounNew].pid = pid;
newPcb[endCounNew].psw = psw;
newPcb[endCounNew].page_table = page_table;
newPcb[endCounNew].regs[0] = regs0;
newPcb[endCounNew].regs[1] = regs1;
newPcb[endCounNew].regs[2] = regs2;
frontNew = &newPcb[endCounNew];

rearNew = frontNew;
}
else
{
endCounNew = (endCounNew + 1) % PROCESS_COUNT_LIMIT;

newPcb[endCounNew].pid = pid;
newPcb[endCounNew].psw = psw;
newPcb[endCounNew].page_table = page_table;
newPcb[endCounNew].regs[0] = regs0;
newPcb[endCounNew].regs[1] = regs1;
newPcb[endCounNew].regs[2] = regs2;
rearNew->next = &newPcb[endCounNew];
rearNew->next->prev = rearNew;
rearNew = &newPcb[endCounNew];
}
}

}

else if (state == 3)
{
if (queueOveflow(3) == 0)
{
if (frontRunning == 0)
{
endCounRunning = (endCounRunning + 1) % PROCESS_COUNT_LIMIT;
runningPcb[endCounRunning].pid = pid;
runningPcb[endCounRunning].psw = psw;
runningPcb[endCounRunning].page_table = page_table;
runningPcb[endCounRunning].regs[0] = regs0;
runningPcb[endCounRunning].regs[1] = regs1;
runningPcb[endCounRunning].regs[2] = regs2;
frontRunning = &runningPcb[endCounRunning];
rearRunning = frontRunning;
// videoPointer[prtLocator++] = ‘H’;
// videoPointer[prtLocator++] = 0x07;
// videoPointer[prtLocator++] = ' ';
// videoPointer[prtLocator++] = 0x07;
}
else
{
endCounRunning = (endCounRunning + 1) % PROCESS_COUNT_LIMIT;

runningPcb[endCounRunning].pid = pid;
runningPcb[endCounRunning].psw = psw;
runningPcb[endCounRunning].page_table = page_table;
runningPcb[endCounRunning].regs[0] = regs0;
runningPcb[endCounRunning].regs[1] = regs1;
runningPcb[endCounRunning].regs[2] = regs2;
rearRunning->next = &runningPcb[endCounRunning];
rearRunning->next->prev = rearRunning;
rearRunning = &runningPcb[endCounRunning];
}
}
}
else if (state == 4)
{
if (queueOveflow(4) == 0)
{
if (frontWaiting == 0)
{
endCounWaiting = (endCounWaiting + 1) % PROCESS_COUNT_LIMIT;
waitingPcb[endCounWaiting].pid = pid;
waitingPcb[endCounWaiting].psw = psw;
waitingPcb[endCounWaiting].page_table = page_table;
waitingPcb[endCounWaiting].regs[0] = regs0;
waitingPcb[endCounWaiting].regs[1] = regs1;
waitingPcb[endCounWaiting].regs[2] = regs2;
frontWaiting = &waitingPcb[endCounWaiting];
rearWaiting = frontWaiting;
}
else
{
endCounWaiting = (endCounWaiting + 1) % PROCESS_COUNT_LIMIT;

waitingPcb[endCounWaiting].pid = pid;
waitingPcb[endCounWaiting].psw = psw;
waitingPcb[endCounWaiting].page_table = page_table;
waitingPcb[endCounWaiting].regs[0] = regs0;
waitingPcb[endCounWaiting].regs[1] = regs1;
waitingPcb[endCounWaiting].regs[2] = regs2;
rearWaiting->next = &waitingPcb[endCounWaiting];
rearWaiting = &waitingPcb[endCounWaiting];
rearWaiting->next->prev = rearWaiting;
}
}
}
else if (state == 5)
{
if (queueOveflow(5) == 0)
{
if (frontDone == 0)
{
endCounDone = (endCounDone + 1) % PROCESS_COUNT_LIMIT;
donePcb[endCounDone].pid = pid;
donePcb[endCounDone].psw = psw;
donePcb[endCounDone].page_table = page_table;
donePcb[endCounDone].regs[0] = regs0;
donePcb[endCounDone].regs[1] = regs1;
donePcb[endCounDone].regs[2] = regs2;
frontDone = &donePcb[endCounDone];
rearDone = frontDone;
}
else
{
endCounDone = (endCounDone + 1) % PROCESS_COUNT_LIMIT;

donePcb[endCounDone].pid = pid;
donePcb[endCounDone].psw = psw;
donePcb[endCounDone].page_table = page_table;
donePcb[endCounDone].regs[0] = regs0;
donePcb[endCounDone].regs[1] = regs1;
donePcb[endCounDone].regs[2] = regs2;
rearDone->next = &donePcb[endCounDone];
rearDone = &donePcb[endCounDone];
rearDone->next->prev = rearDone;
}
}
}
}
struct processControlBlock* delete1(char pid, int state)
{
if (state == 1)
{
int m = 0;
pcbNode*curr = frontNew;
int find = 1;
struct processControlBlock *tempPcb_1;
int tempPcb_2 = initCounNew;
if (queueUnderflow(1) == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = frontNew;
m++; initCounNew++; frontNew = frontNew->next;
newPcb[initCounNew].prev = 0;
}
else if (rearNew->pid == pid)
{
tempPcb_1 = rearNew;
endCounNew--;
rearNew = rearNew->prev;
newPcb[endCounNew].next = 0;
}
else if (curr->next == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = curr;
initCounNew = -1;
}

}
else
{
while (curr->next != 0 && find == 1)
{
m++; tempPcb_2++;
if (curr->next->pid == pid)
{
tempPcb_1 = curr->next;
find = 0;
}
else
curr = curr->next;
}

if (find == 0)
{
int i;
for (i = m; i < endCounNew - 1; i++) { newPcb[i] = newPcb[i + 1]; }
endCounNew--;
newPcb[endCounNew].next = 0;

}
}
}

return tempPcb_1;
}
else if (state == 3)
{
int m = 0;
pcbNode*curr = frontRunning;
int find = 1;
struct processControlBlock*tempPcb_1;
int tempPcb_2 = initCounReady;
if (queueUnderflow(3) == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = frontRunning;
m++; initCounReady++; frontRunning = frontRunning->next;
runningPcb[initCounReady].prev = 0;
}
else if (rearRunning->pid == pid)
{
tempPcb_1 = rearRunning;
endCounRunning--;
rearRunning = rearRunning->prev;
runningPcb[endCounRunning].next = 0;
}
else if (curr->next == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = curr;
initCounReady = -1;
}

}
else
{
while (curr->next != 0 && find == 1)
{
m++; tempPcb_2++;
if (curr->next->pid == pid)
{
tempPcb_1 = curr->next;
find = 0;
}
else
curr = curr->next;
}

if (find == 0)
{
int i;
for (i = m; i < endCounRunning - 1; i++) { runningPcb[i] = runningPcb[i + 1]; }
endCounRunning--;
runningPcb[endCounRunning].next = 0;

}
}
}

return tempPcb_1;
}
else if (state == 4)
{
int m = 0;
pcbNode*curr = frontWaiting;
int find = 1;
struct processControlBlock*tempPcb_1;
int tempPcb_2 = initCounWaiting;
if (queueUnderflow(1) == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = frontWaiting;
m++; initCounWaiting++; frontWaiting = frontWaiting->next;
waitingPcb[initCounWaiting].prev = 0;
}
else if (rearWaiting->pid == pid)
{
tempPcb_1 = rearWaiting;
endCounWaiting--;
rearWaiting = rearWaiting->prev;
waitingPcb[endCounWaiting].next = 0;
}
else if (curr->next == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = curr;
initCounWaiting = -1;
}

}
else
{
while (curr->next != 0 && find == 1)
{
m++; tempPcb_2++;
if (curr->next->pid == pid)
{
tempPcb_1 = curr->next;
find = 0;
}
else
curr = curr->next;
}

if (find == 0)
{
int i;
for (i = m; i < endCounWaiting - 1; i++) { waitingPcb[i] = waitingPcb[i + 1]; }
endCounWaiting--;
waitingPcb[endCounWaiting].next = 0;

}
}
}

return tempPcb_1;
}
else if (state == 5)
{
int m = 0;
pcbNode*curr = frontDone;
int find = 1;
struct processControlBlock*tempPcb_1;
int tempPcb_2 = initCounDone;
if (queueUnderflow(1) == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = frontDone;
m++; initCounDone++; frontDone = frontDone->next;
donePcb[initCounDone].prev = 0;
}
else if (rearDone->pid == pid)
{
tempPcb_1 = rearDone;
endCounDone--;
rearDone = rearDone->prev;
donePcb[endCounDone].next = 0;
}
else if (curr->next == 0)
{
if (curr->pid == pid)
{
tempPcb_1 = curr;
initCounDone = -1;
}

}
else
{
while (curr->next != 0 && find == 1)
{
m++; tempPcb_2++;
if (curr->next->pid == pid)
{
tempPcb_1 = curr->next;
find = 0;
}
else
curr = curr->next;
}

if (find == 0)
{
int i;
for (i = m; i < endCounDone - 1; i++) { donePcb[i] = donePcb[i + 1]; }
endCounDone--;
donePcb[endCounDone].next = 0;

}
}
}

return tempPcb_1;
}
}
struct processControlBlock* deque(int state)
{
if (state == 1)
{

pcbNode*temp = frontNew;
frontNew = frontNew->next;
initCounNew = (initCounNew + 1) % PROCESS_COUNT_LIMIT;
return temp;
}

else if (state == 3)
{

pcbNode*temp = frontRunning;
frontRunning = frontRunning->next;
initCounReady = (initCounReady + 1) % PROCESS_COUNT_LIMIT;
return temp;
}

else if (state == 4)
{

pcbNode*temp = frontWaiting;
frontWaiting = frontWaiting->next;
initCounWaiting = (initCounWaiting + 1) % PROCESS_COUNT_LIMIT;
return temp;
}

else if (state == 5)
{

pcbNode*temp = frontDone;
frontDone = frontDone->next;
initCounDone = (initCounDone + 1) % PROCESS_COUNT_LIMIT;
return temp;
}
}
struct processControlBlock* returnhead(int state)
{
if (state == 1){ return frontNew; }
if (state == 2){ return frontReady; }
if (state == 3){ return frontRunning; }
if (state == 4){ return frontWaiting; }
if (state == 5){ return frontDone; }
}
struct processControlBlock* returntail(int state)
{
if (state == 1){ return rearNew; }
if (state == 2){ return rearReady; }
if (state == 3){ return rearRunning; }
if (state == 4){ return rearWaiting; }
if (state == 5){ return rearDone; }
}

void list(int state,int b)
{
if (state == 1)
{
pcbNode*curr = frontNew;
prtLocator = b;
while (curr != 0)
{
videoPointer[prtLocator++] = curr->pid;
videoPointer[prtLocator++] = 0x07;
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
curr = curr->next;
}

int state = 0;
while (state != 10)
{
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
state++;
}
}

if (state == 2)
{
if(!queueUnderflow(1))
{
videoPointer[prtLocator++] = returnhead(1)->pid;
videoPointer[prtLocator++] = 0x07;

}
}

if (state == 3)
{

pcbNode*curr = frontRunning;
prtLocator = b;

int i;
while (curr != 0)
{
videoPointer[prtLocator++] = curr->pid;
videoPointer[prtLocator++] = 0x07;
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
curr = curr->next;
}

int state = 0;
while (state != 10)
{
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
state++;
}
}

if (state == 4)
{

pcbNode*curr = frontWaiting;
prtLocator = b;
while (curr != 0)
{
videoPointer[prtLocator++] = curr->pid;
videoPointer[prtLocator++] = 0x07;
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
curr = curr->next;
}

int state = 0;
while (state != 10)
{
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
state++;
}
}

if (state == 5)
{

pcbNode*curr = frontDone;
prtLocator = b;
while (curr != 0)
{
videoPointer[prtLocator++] = curr->pid;
videoPointer[prtLocator++] = 0x07;
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
curr = curr->next;
}

int state = 0;
while (state != 10)
{
videoPointer[prtLocator++] = ' ';
videoPointer[prtLocator++] = 0x07;
state++;
}
}
}

int size(int state)
{
if (state == 1)
{

return (endCounNew - initCounNew);
}
if (state == 2)
{

return (endCounReady - initCounReady);
}
if (state == 3)
{

return (endCounRunning - initCounReady);
}
if (state == 4)
{

return (endCounWaiting - initCounWaiting);
}
if (state == 5)
{

return (endCounDone - initCounDone);
}
}

void init_q(int state)
{
if (state == 1)
{
initCounNew = endCounNew = -1;
frontNew = rearNew = 0; int i;
for (i = 0; i < 20; i++)
{
newPcb[i].pid = -2;
newPcb[i].psw = -2;
}
}
else if (state == 2)
{
initCounReady = endCounReady = -1;
frontReady = rearReady = 0; int i;
for (i = 0; i < 20; i++)
{
readyPcb[i].pid = -2;
readyPcb[i].psw = -2;
}
}

else if (state == 3)
{
initCounReady = endCounRunning = -1;
frontRunning = rearRunning = 0; int i;
for (i = 0; i < 20; i++)
{
runningPcb[i].pid = -2;
runningPcb[i].psw = -2;
}
}

else if (state == 4)
{
initCounWaiting = endCounWaiting = -1;
frontWaiting = rearWaiting = 0; int i;
for (i = 0; i < 20; i++)
{
waitingPcb[i].pid = -2;
waitingPcb[i].psw = -2;
}
}

else if (state == 5)
{
initCounDone = endCounDone = -1;
frontDone = rearDone = 0; int i;
for (i = 0; i < 20; i++)
{
donePcb[i].pid = -2;
donePcb[i].psw = -2;
}
}
};

struct processControlBlock* tempQ;

int totalProcesses = 0;
void initializeQueues()
{
init_q(1);
init_q(3);
init_q(4);
init_q(5);
}

void exec1()
{
tempQ = deque(1);
newSize--;

videoPointer[prtLocator++] = tempQ->pid;
videoPointer[prtLocator++] = 0x07;

enque(tempQ->pid, tempQ->psw, tempQ->page_table, tempQ->regs[0],tempQ->regs[1], tempQ->regs[2], 3);
runningSize++;
}


int unwait(int PID)
{
tempQ = delete1(PID, 4);
waitingSize--;
enque(tempQ->pid, tempQ->psw, tempQ->page_table, tempQ->regs[0], tempQ->regs[1], tempQ->regs[2], 1);
newSize++;
return 0;
}

int eoquantum()
{
tempQ = deque(3);
runningSize--;
enque(tempQ->pid, tempQ->psw, tempQ->page_table, tempQ->regs[0],tempQ->regs[1], tempQ->regs[2], 1);
newSize++;
return 0;
}


int eolife()
{
tempQ = deque(3);
runningSize--;
enque(tempQ->pid, tempQ->psw, tempQ->page_table, tempQ->regs[0],tempQ->regs[1], tempQ->regs[2], 5);
doneSize++;
return 0;
}


int wait()
{
tempQ = deque(3);
runningSize--;
enque(tempQ->pid, tempQ->psw, tempQ->page_table, tempQ->regs[0],tempQ->regs[1], tempQ->regs[2], 4);
waitingSize++;
return 0;
}