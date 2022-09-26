#include "sccp2_tmr.h"
#include "../main.h"

void SCCP2_TMR_Initialize(void) {
    // CCPON enabled; MOD 16-Bit/32-Bit Timer; CCSEL disabled; CCPSIDL disabled; T32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL REFO; TMRSYNC disabled; 
    CCP2CON1L = (0x81000 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; OPS Each Time Base Period Match; SYNC None; OPSSRC Timer Interrupt Event; 
    CCP2CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP2CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC2; AUXOUT Disabled; OCAEN disabled; OENSYNC disabled; 
    CCP2CON2H = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP2CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; ICGARM disabled; TRCLR disabled; 
    CCP2STATL = 0x00;
    //TMR 0; 
    CCP2TMRL = 0x00;
    //TMR 0; 
    CCP2TMRH = 0x00;
    //PR 1999; 
    CCP2PRL = 0x7CF;
    //PR 0; 
    CCP2PRH = 0x00;
    //CMP 0; 
    CCP2RA = 0x00;
    //CMP 0; 
    CCP2RB = 0x00;
    //BUF 0; 
    CCP2BUFL = 0x00;
    //BUF 0; 
    CCP2BUFH = 0x00;

    CCP2CON1Lbits.CCPON = 0x1; //Enabling CCP

    IFS1bits.CCP2IF = 0;

    IFS1bits.CCT2IF = 0;
    //      
    //    // Enabling SCCP2 interrupt.
    //    IEC1bits.CCP2IE = 1;

    // Enabling SCCP2 interrupt.
    IEC1bits.CCT2IE = 1;

}

void __attribute__((interrupt, no_auto_psv)) _CCT2Interrupt(void) {

    static int32_t vacrms_scaled_filt;

    vacrms = vacrms_scaled_filt >> 10;
    vacrms_scaled_filt = vacrms_scaled_filt - vacrms + vac_adc;
    IFS1bits.CCT2IF = 0;
//    if (++uarttimeout > 10) {
//        uarttimeout = 10;
//        systemstate_pfc = STANDBYPFC;   
//    }

}

void __attribute__((interrupt, no_auto_psv)) _CCP2Interrupt(void) {

    IFS1bits.CCP2IF = 0;

}
