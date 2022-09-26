#include "sccp1_compare.h"
#include "../main.h"
#include "pin_manager.h"

void SCCP1_COMPARE_Initialize (void)
{
    // CCPON enabled; MOD Dual Edge Compare, Buffered(PWM); CCSEL disabled; CCPSIDL disabled; T32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL REFO; TMRSYNC disabled; 
    CCP1CON1L = (0x8105 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN enabled; OPS Each Time Base Period Match; SYNC None; OPSSRC Timer Interrupt Event; 
    CCP1CON1H = 0x0;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP1CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC1; AUXOUT Timer Base Reset/Rollover; OCAEN disabled; OENSYNC enabled; 
    CCP1CON2H = 0x8008;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP1CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; ICGARM disabled; TRCLR disabled; 
    CCP1STATL = 0x00;
    //TMR 0; 
    CCP1TMRL = 0x00;
    //TMR 0; 
    CCP1TMRH = 0x00;
    //PR  
    CCP1PRL = SCCP1PERIOD;
    //PR 
    CCP1PRH = SCCP1PERIOD;
    //CMP 
    CCP1RA = 0x4;
    //CMP 0; 
    CCP1RB = 0x5;
    //BUF 0; 
    CCP1BUFL = 0x00;
    //BUF 0; 
    CCP1BUFH = 0x00;

    CCP1CON1Lbits.CCPON = 0x1; //Enabling CCP
//
    // Clearing IF flag before enabling the interrupt.
//    IFS0bits.CCP1IF = 0;
//    // Enabling SCCP1 interrupt.
//    IEC0bits.CCP1IE = 1;

    // Clearing IF flag before enabling the interrupt.
//    IFS0bits.CCT1IF = 0;
//    // Enabling SCCP1 interrupt.
//    IEC0bits.CCT1IE = 1;
}

void __attribute__((interrupt, no_auto_psv)) _CCP1Interrupt(void) {

    IFS0bits.CCP1IF = 0;

}

void __attribute__((interrupt, no_auto_psv)) _CCT1Interrupt(void) {

    IFS0bits.CCT1IF = 0;

}
