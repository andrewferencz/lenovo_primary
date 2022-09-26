#include "dma.h"
#include "../main.h"

/**
  Prototype:        void DMA_Initialize(void)
  Input:            none
  Output:           none
  Description:      DMA_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            DMA_Initialize();
 */
void DMA_Initialize(void) 
{ 
    // DMAEN enabled; PRSSEL Fixed priority; 
    DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later
    // LADDR 4096; 
    DMAL= 0x1000;
    // HADDR 20479; 
    DMAH= 0x4FFF;

    DMACH0bits.RELOAD = 1;
    DMACH0bits.DAMODE = 0b01; //incremented
    DMACH0bits.TRMODE = 0b01; //repeated on-shot
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL SCCP1; HIGHIF disabled; 
    DMAINT0= 0x0100;
    // SADDR 0; 
    DMASRC0= (unsigned int)&ADCBUF1;
    // DADDR 0; 
    DMADST0= (signed int)an1_ipfc_dma;
    // CNT 8; 
    DMACNT0= 0x08;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = false;

    // CHEN enabled; SAMODE Unchanged; SIZE 16 bit; DAMODE Unchanged; CHREQ disabled; RELOAD disabled; TRMODE One-Shot; NULLW disabled; 
    DMACH1 = 0;//0x01 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL UART1 RX; 
    DMAINT1= 0;//0x400;
    // SADDR 0; 
    DMASRC1= 0;//(unsigned int) &U1RXREG;
    // DADDR 0; 
    DMADST1= 0;//(unsigned int) &rx_array.singles[0];
    // CNT 0; 
    DMACNT1= 0;//8;
    // Clearing Channel 1 Interrupt Flag;
    IFS0bits.DMA1IF = false;
    // Enabling Channel 1 Interrupt
    //IEC0bits.DMA1IE = true;
 
    DMACH2 = 0x24B & 0xFFFE;
    DMACH2bits.TRMODE = 0b00;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL UART1 TX; 
    DMAINT2= 0x500;
    // SADDR 0; 
    DMASRC2= 0;//(unsigned int) & tx_array;
    // DADDR 0; 
    DMADST2= (unsigned int) &U1TXREG;
    // CNT 0; 
    DMACNT2= 12;
    // Clearing Channel 2 Interrupt Flag;
    IFS1bits.DMA2IF = false;
    _DMA2IE = 1;

    // SAMODE Unchanged; CHEN disabled; SIZE 16 bit; DAMODE Unchanged; TRMODE One-Shot; NULLW disabled; CHREQ disabled; RELOAD disabled; 
    DMACH3 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL INT0; HIGHIF disabled; 
    DMAINT3= 0x00;
    // SADDR 0; 
    DMASRC3= 0x00;
    // DADDR 0; 
    DMADST3= 0x00;
    // CNT 0; 
    DMACNT3= 0x00;
    // Clearing Channel 3 Interrupt Flag;
    IFS1bits.DMA3IF = false;
    
    //Enable DMA
    DMACONbits.DMAEN = 1; 
    
    //Enable DMA Channel 0
    DMACH0bits.CHEN = 1;
    //Enable DMA Channel 1
//    DMACH1bits.CHEN = 1;
//    //Enable DMA Channel 2
//    DMACH2bits.CHEN = 1;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _DMA1Interrupt( void )
{
//    volatile uint16_t errorcheck;
//
//    errorcheck = rx_array.doubles[0] + rx_array.doubles[1] + rx_array.doubles[2];
//    if (rx_array.doubles[3] != errorcheck) {
//        newrxdata = false;
//    } else {
//        newrxdata = true;
//        rxtimeout = false;
//        rxtimeoutcounter = 0;
//        //average the +/- voltage for control, keeps the sum the same
//        V_llcPID.measuredOutput = rx_array.doubles[VOUT_ADC_INDEX];
//
//        I_llcPID.measuredOutput = rx_array.doubles[IOUT_ADC_INDEX];
//    }
//    system_status_sec = rx_array.doubles[SYSTEMSTATUS_SEC];
    _DMA1IF = 0;
}


void __attribute__((interrupt, no_auto_psv)) _DMA2Interrupt(void) {

    _DMA2IF = 0;
}

//not used, just in case 
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void) {

    _DMA0IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _DMA3Interrupt(void) {

    _DMA3IF = 0;
}