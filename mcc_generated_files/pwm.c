/**
  Section: Included Files
*/

#include "pwm.h"
#include "../main.h"
#include "pin_manager.h"

/**
 Section: Driver Interface Function Definitions
*/

void PWM_Initialize (void)
{
    // MCLKSEL AFVCO/2 - Auxiliary VCO divided by 2; HRERR disabled; LOCK disabled; DIVSEL 1:2; 
    PCLKCON = 0x01;
    // FSCL 0; 
    FSCL = 0x00;
    // FSMINPER 0; 
    FSMINPER = 0x00;
    // MPHASE 0; 
    MPHASE = 0x00;
    // MDC 0; 
    MDC = 0x00;
    // MPER 16; 
    MPER = 0x10;
    // LFSR 0; 
    LFSR = 0x00;
    // CTA7EN disabled; CTA8EN disabled; CTA1EN disabled; CTA2EN disabled; CTA5EN disabled; CTA6EN disabled; CTA3EN disabled; CTA4EN disabled; 
    CMBTRIGL = 0x00;
    // CTB8EN disabled; CTB3EN disabled; CTB2EN disabled; CTB1EN disabled; CTB7EN disabled; CTB6EN disabled; CTB5EN disabled; CTB4EN disabled; 
    CMBTRIGH = 0x00;
    // PWMLFA PWMS1 or PWMS2;; S1APOL Positive logic; S2APOL Positive logic; PWMLFAD No Assignment; PWMS1A PWM1H; PWMS2A PWM1H; 
    LOGCONA = 0x00;
    // PWMLFB PWMS1 | PWMS2; S2BPOL Positive logic; PWMLFBD No Assignment; S1BPOL Positive logic; PWMS2B PWM1H; PWMS1B PWM1H; 
    LOGCONB = 0x00;
    // PWMLFC PWMS1 | PWMS2; PWMLFCD No Assignment; S2CPOL Positive logic; S1CPOL Positive logic; PWMS1C PWM1H; PWMS2C PWM1H; 
    LOGCONC = 0x00;
    // PWMS1D PWM1H; S1DPOL Positive logic; PWMLFD PWMS1 | PWMS2; PWMLFDD No Assignment; S2DPOL Positive logic; PWMS2D PWM1H; 
    LOGCOND = 0x00;
    // PWMS1E PWM1H; PWMS2E PWM1H; S1EPOL Positive logic; PWMLFE PWMS1 | PWMS2; S2EPOL Positive logic; PWMLFED No Assignment; 
    LOGCONE = 0x00;
    // S1FPOL Positive logic; PWMS2F PWM1H; PWMS1F PWM1H; S2FPOL Positive logic; PWMLFFD No Assignment; PWMLFF PWMS1 | PWMS2; 
    LOGCONF = 0x00;
    // EVTASEL PGTRGSEL bits; EVTASYNC Not synchronized; EVTAPOL Active-high; EVTAPGS PG1; EVTASTRD Stretched to 8 PWM clock cycles minimum; EVTAOEN disabled; 
    PWMEVTA = 0x00;
    // EVTBPGS PG1; EVTBSYNC Not synchronized; EVTBPOL Active-high; EVTBSEL PGTRGSEL bits; EVTBSTRD Stretched to 8 PWM clock cycles minimum; EVTBOEN disabled; 
    PWMEVTB = 0x00;
    // EVTCPGS PG1; EVTCPOL Active-high; EVTCSEL PGTRGSEL bits; EVTCSTRD Stretched to 8 PWM clock cycles minimum; EVTCSYNC Not synchronized; EVTCOEN disabled; 
    PWMEVTC = 0x00;
    // EVTDOEN disabled; EVTDSTRD Stretched to 8 PWM clock cycles minimum; EVTDPOL Active-high; EVTDPGS PG1; EVTDSEL PGTRGSEL bits; EVTDSYNC Not synchronized; 
    PWMEVTD = 0x00;
    // EVTEOEN disabled; EVTEPOL Active-high; EVTEPGS PG1; EVTESTRD Stretched to 8 PWM clock cycles minimum; EVTESEL PGTRGSEL bits; EVTESYNC Not synchronized; 
    PWMEVTE = 0x00;
    // EVTFPOL Active-high; EVTFPGS PG1; EVTFSTRD Stretched to 8 PWM clock cycles minimum; EVTFSEL PGTRGSEL bits; EVTFOEN disabled; EVTFSYNC Not synchronized; 
    PWMEVTF = 0x00;
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Self-trigger; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    PG2CONH = 0x00;
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Trigger output selected by PG2 or PG6; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    PG3CONH = 0x02;
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG2STAT = 0x00;
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG3STAT = 0x00;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH disabled; OVRENL disabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 0; 
    PG2IOCONLbits.SWAP = 1;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH disabled; OVRENL disabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 0; 
    PG3IOCONLbits.SWAP = 1;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH enabled; CAPSRC Software; POLH Active-high; 
//    PG1IOCONH = 0x0C;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH disabled; CAPSRC Software; POLH Active-high; 
    PG2IOCONH = 0x04;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH disabled; CAPSRC Software; POLH Active-high; 
    PG3IOCONH = 0x04;
    // UPDTRG Duty Cycle; ADTR1PS 1:1; PGTRGSEL EOC event; ADTR1EN3 disabled; ADTR1EN1 disabled; ADTR1EN2 disabled; 
//    PG1EVTL = 0x08;
    // ADTRI1EN3, PS=1:1, update on DC, TRIGB OUTPUT 
    PG2EVTL = 0x040A;
    // update on DC 
    PG3EVTL = 0x0008;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
//    PG1EVTH = 0x00;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 enabled; 
    PG2EVTH = 0x80;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
    PG3EVTH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1FPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2FPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG3FPCIL = 0x00;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
//    PG1FPCIH = 0x00;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2FPCIH = 0x00;
    // TQPS Not inverted; LATMOD disabled; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG3FPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1CLPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2CLPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG3CLPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
//    PG1CLPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2CLPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG3CLPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
//    PG1FFPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2FFPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG3FFPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
//    PG1FFPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2FFPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG3FFPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
//    PG1SPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2SPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG3SPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
//    PG1SPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2SPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG3SPCIH = 0x00;
    // LEB 0; 
    PG1LEBL = 0x00;
    // LEB 0; 
    PG2LEBL = 0x00;
    // LEB 0; 
    PG3LEBL = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG1LEBH = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG2LEBH = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG3LEBH = 0x00;
    // PHASE 0; 
    PG1PHASE = 0x00;
    // PHASE 0; 
    PG2PHASE = 0x00;
    // PHASE 0; 
    PG3PHASE = 0x00;
    // DC 2500; 
    PG1DC = 0x9C4;
    // DC 0; 
    PG2DC = 0x00;
    // DC 0; 
    PG3DC = 0x00;
    // DCA 0; 
    PG1DCA = 0x00;
    // DCA 0; 
    PG2DCA = 0x00;
    // DCA 0; 
    PG3DCA = 0x00;
    // PER 4999; 
//    PG1PER = 0x1387;
    // PER 3332; 
    PG2PER = PFC_PERIOD;
    // PER 3332; 
    PG3PER = PFC_PERIOD;
    // TRIGA 1666; 
    PG2TRIGA = 0x682;
    // TRIGA 0; 
    PG3TRIGA = 0x00;
    // TRIGB 1250; 
    PG2TRIGB = (PFC_PERIOD+1)>>1;
    // TRIGB 0; 
    PG3TRIGB = 0x00;
    // TRIGC 625; 
    PG2TRIGC = 0x271;
    // TRIGC 0; 
    PG3TRIGC = 0x00;

    
    //PWM Generator 2 Interrupt
    IFS4bits.PWM2IF = 0;
    IEC4bits.PWM2IE = 1;
    
    // HREN disabled; MODSEL Independent Edge; TRGCNT 1; CLKSEL Master clock; ON enabled; 
//    PG1CONL = 0x8008;
    // HREN disabled; MODSEL Independent Edge; TRGCNT 1; CLKSEL Master clock; ON enabled; 
    PG2CONL = 0x8008;
    // HREN disabled; MODSEL Independent Edge; TRGCNT 1; CLKSEL Master clock; ON disabled; 
    PG3CONL = 0x8008;
}



void __attribute__ ( ( interrupt, no_auto_psv ) ) _PWM2Interrupt (  )
{
    volatile int16_t tempint2;
    
    
    FASTSUM(an1_ipfc_dma, &isenpfc_adc);
    isenpfc_adc -= 950; // CHANGED AFTER CHANGING GAIN RESISTOR FROM 7.5K TO 5.11K//1400; //offset is about 1500-1700
    //move PID here for current to be fastest for greatest phase margin

   
    IpfcPID.measuredOutput = isenpfc_adc>>1;  //Q14 number, fast sum gathers 8 values
    if (systemstate_pfc >= SOFTSTARTPFC) {
        PID(&IpfcPID);
        if (IpfcPID.controlOutput > (PFC_DUTYMAX << 2)) {
            IpfcPID.controlOutput = PFC_DUTYMAX << 2;
        }
        if (IpfcPID.controlOutput < 0) {
            IpfcPID.controlOutput = 0;
        }
        //very fast OVP protection
    tempint2 = IpfcPID.controlOutput >> 2; //divide by 8 instead of 4 ... period is halved
#ifndef DEBUGGING
    PG3DC = tempint2;
    PG2DC = tempint2;
#else
    PG3DC = 0;
    PG2DC = 0;
#endif
    }

    IFS4bits.PWM2IF = 0; 
}
