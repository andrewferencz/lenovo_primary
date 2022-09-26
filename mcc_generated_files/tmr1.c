#include <stdio.h>
#include "tmr1.h"
#include "../main.h"

void TMR1_Initialize (void)
{
    //TMR 0; 
    TMR1 = 0x00;
    //Period = 0.001 s; Frequency = 100000000 Hz; PR 12499; 
    PR1 = 0x30D3;
    //TCKPS 1:8; PRWIP Write complete; TMWIP Write complete; TON enabled; TSIDL disabled; TCS FOSC/2; TECS T1CK; TSYNC disabled; TMWDIS disabled; TGATE disabled; 
    T1CON = 0x8010;

    IEC0bits.T1IE = true;

}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt() {

    static int txcounter = 0;
    if (lowvinstatus == true) {
        if (lowvin_ms_counter < 50) {
            ++lowvin_ms_counter;
        }
    }

    ++txcounter; //trigger for RS232 communication, every 5mS
    if ((txcounter > 5) && (txtrigger == 0)) {
        txtrigger = 1;
        txcounter = 0;
    }
    
    IFS0bits.T1IF = false;
}
