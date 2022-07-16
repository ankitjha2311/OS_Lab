#include "keyMapping.h"
#include "ProcessManager.c"
#include "threadManager.c"
#include "manual.h"
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define ENTER_KEY_CODE 0x1C
#define KEY_DATA_PORT 0x60
#define KEY_STATUS_PORT 0x64
#define IDT_SIZE 256
#define LINES 35
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT *COLUMNS_IN_LINE *LINES


extern char readPort(unsigned short port);
extern void writePort(unsigned short port, unsigned char data);
extern void loadIDT(unsigned long *idtPtr);
extern unsigned char keyMap[128];
extern void keyHandler(void);




/* current cursor location */
unsigned int current_loc = 0;
/* video memory begins at address 0xb8000 */
char *vidptr = (char *)0xb8000;
char in;
int count;
unsigned char temp;
unsigned char arr[100];
char *str = "Assignment@OS #:";
char *msg = "Command man to open manual and if screen is full clrsr";
int count1 = 0;
struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void initIDT(void)
{
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idtPtr[2];

    /* populate IDT entry of keyboard’s interrupt */
    keyboard_address = (unsigned long)keyHandler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = INTERRUPT_GATE;
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    writePort(0x20, 0x11);
    writePort(0xA0, 0x11);

    writePort(0x21, 0x20);
    writePort(0xA1, 0x28);

    writePort(0x21, 0x00);
    writePort(0xA1, 0x00);

    writePort(0x21, 0x01);
    writePort(0xA1, 0x01);

    writePort(0x21, 0xff);
    writePort(0xA1, 0xff);

    /* fill the IDT descriptor */
    idt_address = (unsigned long)IDT;
    idtPtr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idtPtr[1] = idt_address >> 16;

    loadIDT(idtPtr);
}

void initKeyBoard(void)
{
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
    writePort(0x21, 0xFD);
}

void kprint(char *str)
{
    unsigned int i = 0;
    while (str[i] != 0)
    {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x07;
    }
}

void printNuline(void)
{
    unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
    current_loc = current_loc + (line_size - current_loc % (line_size));
    count1 = count1 + 160;
}
void manual(){
     kprint(line1);
     printNuline(); 
     kprint(line2);
     printNuline(); 
     kprint(line3);
     printNuline(); 
     kprint(line4);
     printNuline();
     printNuline();  
     kprint(line5);
     printNuline(); 
     kprint(line6);
     printNuline(); 
     kprint(line7);
     printNuline(); 
     kprint(line8);
     printNuline(); 
     kprint(line9);
     printNuline(); 
     kprint(line10);
     printNuline(); 
     kprint(line11);
     printNuline();
     printNuline();  
     kprint(line12);
     printNuline(); 
     kprint(line13);
     printNuline(); 
     kprint(line14);
     printNuline(); 
     kprint(line15);
     printNuline(); 
     kprint(line16);
     printNuline();
     kprint(line17);
     printNuline(); 
     kprint(line18);
     printNuline(); 
}
 
 void clearScreen(void)

{
    unsigned int i = 0;
    while (i < SCREENSIZE)
    {
        vidptr[i++] = ' ';
        vidptr[i++] = 0x07;
    }
}

void terminal_input(unsigned char arr[])
{
    /*——————————To open Manual————————————-*/
    if(arr[0] =='m' && arr[1]=='a' && arr[2]=='n'){
        manual();
    }
    /*——————————To Clear Screen————————————-*/
    else if (arr[0] =='c' && arr[1]=='l' && arr[2]=='r' && arr[3]=='s' && arr[4]=='r')
    {
        clearScreen();
        initIDT();
        initKeyBoard();
    }
   /*——————————-Process Manager————————————-*/
    else if (arr[0] =='c' && arr[1]=='r' && arr[2]=='t' && arr[3]=='p' && arr[4]=='r')
    {
        enque(arr[6], arr[8], arr[10], arr[12], arr[14], arr[16], arr[18]);
    }
    else if (arr[0] == 'w' && arr[1] == 'a' && arr[2] == 't' && arr[3] == 'p' && arr[4] == 'r')
    {
        wait();
    }
    else if (arr[0] == 'u' && arr[1] == 'n' && arr[2] == 'w' && arr[3] == 't' && arr[4] == 'p' && arr[5] == 'r')
    {
        unwait(arr[5]);
    }
    else if (arr[0] == 'e' && arr[1] == 'o' && arr[2] == 'q' && arr[3] == 'p' && arr[4] == 'r')
    {
        eoquantum();
    }
    else if (arr[0] == 'e' && arr[1] == 'o' && arr[2] == 'l' && arr[3] == 'p' && arr[4] == 'r')
    {
        eolife();
    }
    else if (arr[0] == 'e' && arr[1] == 'x' && arr[2] == 'e' && arr[3] == 'p' && arr[4] == 'r')
    {
        exec1();
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 'p' && arr[3] == 'r' && arr[5] == 'r' && arr[6] == 'd' && arr[7] == 'y')
    {
        list(1, count1);
        printNuline();
        kprint(str);
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 'p' && arr[3] == 'r' && arr[5] == 'r' && arr[6] == 'n' && arr[7] == 'g')
    {
        list(3, count1);
        printNuline();
        kprint(str);
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 'p' && arr[3] == 'r' && arr[5] == 'w' && arr[6] == 't' && arr[7] == 'g')
    {
        list(4, count1);
        printNuline();
        kprint(str);
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 'p' && arr[3] == 'r' && arr[5] == 'd' && arr[6] == 'o' && arr[7] == 'n')
    {
        list(5, count1);
        printNuline();
        kprint(str);
    }
           /*——————————-Thread Manager————————————-*/
    else if (arr[0] =='c' && arr[1]=='r' && arr[2]=='t' && arr[3]=='t' && arr[4]=='d')
    {
        enqueTd(arr[6], arr[8], arr[10], arr[12], arr[14], arr[16], arr[18]);
    }
    else if (arr[0] == 'w' && arr[1] == 'a' && arr[2] == 't' && arr[3] == 't' && arr[4] == 'd')
    {
        waitTd();
    }
    else if (arr[0] == 'u' && arr[1] == 'n' && arr[2] == 'w' && arr[3] == 't' && arr[4] == 't' && arr[5] == 'd')
    {
        unwaitTd(arr[5]);
    }
    else if (arr[0] == 'e' && arr[1] == 'o' && arr[2] == 'q' && arr[3] == 't' && arr[4] == 'd')
    {
        eoQuantTd();
    }
    else if (arr[0] == 'e' && arr[1] == 'o' && arr[2] == 'l' && arr[3] == 't' && arr[4] == 'd')
    {
        eolifeTd();
    }
    else if (arr[0] == 'e' && arr[1] == 'x' && arr[2] == 'e' && arr[3] == 't' && arr[4] == 'd')
    {
        execTd();
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 't' && arr[3] == 'd' && arr[5] == 'r' && arr[6] == 'd' && arr[7] == 'y')
    {
        listTd(1, count1);
        printNuline();
        kprint(str);
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 't' && arr[3] == 'd' && arr[5] == 'r' && arr[6] == 'n' && arr[7] == 'g')
    {
        listTd(3, count1);
        printNuline();
        kprint(str);
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 't' && arr[3] == 'd' && arr[5] == 'w' && arr[6] == 't' && arr[7] == 'g')
    {
        listTd(4, count1);
        printNuline();
        kprint(str);
    }

    else if (arr[0] == 'l' && arr[1] == 's' && arr[2] == 't' && arr[3] == 'd' && arr[5] == 'd' && arr[6] == 'o' && arr[7] == 'n')
    {
        listTd(5, count1);
        printNuline();
        kprint(str);
    }
}


void keyController(void)
{
    while (1)
    {

        unsigned char status;
        char keycode;

        /* write EOI */
        writePort(0x20, 0x20);

        status = readPort(KEY_STATUS_PORT);
        /* Lowest bit of status will be set if buffer is not empty */
        if (status & 0x01)
        {
            keycode = readPort(KEY_DATA_PORT);
            if (keycode < 0)
                return;

            if (keycode == ENTER_KEY_CODE)
            {

                printNuline();
                kprint(str);
                count = 0;
                terminal_input(arr);
                return;
            }
            vidptr[current_loc++] = keyMap[(unsigned char)keycode];
            vidptr[current_loc++] = 0x07;
            temp = keyMap[(unsigned char)keycode];
            arr[count] = temp;
            count++;
        }
    }
}

void kmsg(){
     kprint(msg);
     printNuline(); 
     kprint(str);

}
  
void kmain(void)
{
   clearScreen();
    kmsg();
    initIDT();
    initKeyBoard();
}
