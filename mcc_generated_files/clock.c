#include <stdint.h>
#include "xc.h"
#include "clock.h"

void CLOCK_Initialize(void)
{
    // FRCDIV FRC/1; PLLPRE 1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3001;
    // PLLFBDIV 120; 
    PLLFBD = 0x78;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // POST1DIV 1:3; VCODIV FVCO/4; POST2DIV 1:1; 
    PLLDIV = 0x31;
    // APLLEN enabled; FRCSEL Primary Oscillator; APLLPRE 1:1; 
    ACLKCON1 = 0x8001;
    // APLLFBDIV 100; 
    APLLFBD1 = 0x64;
    // APOST1DIV 1:2; APOST2DIV 1:1; AVCODIV FVCO/2; 
    APLLDIV1 = 0x221;
    // ROEN enabled; ROSWEN disabled; ROSLP disabled; ROSEL FOSC/2; ROOUT enabled; ROSIDL disabled; 
    REFOCONL = 0x9001;
    // RODIV 0; 
    REFOCONH = 0x00;
    // ROTRIM 0; 
    REFOTRIMH = 0x00;
    // IOLOCK disabled; 
    RPCON = 0x00;
    // PMDLOCK disabled; 
    PMDCON = 0x00;
    // ADC1MD enabled; T1MD enabled; U2MD enabled; U1MD enabled; SPI2MD enabled; SPI1MD enabled; QEI1MD enabled; PWMMD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    // CCP2MD enabled; CCP1MD enabled; CCP4MD enabled; CCP3MD enabled; CCP7MD enabled; CCP8MD enabled; CCP5MD enabled; CCP6MD enabled; CCP9MD enabled; 
    PMD2 = 0x00;
    // I2C3MD enabled; U3MD enabled; QEI2MD enabled; CRCMD enabled; I2C2MD enabled; 
    PMD3 = 0x00;
    // REFOMD enabled; 
    PMD4 = 0x00;
    // DMA1MD enabled; SPI3MD enabled; DMA2MD enabled; DMA3MD enabled; DMA0MD enabled; 
    PMD6 = 0x00;
    // CMP3MD enabled; PTGMD enabled; CMP1MD enabled; CMP2MD enabled; 
    PMD7 = 0x00;
    // DMTMD enabled; CLC3MD enabled; OPAMPMD enabled; BIASMD enabled; CLC4MD enabled; SENT2MD enabled; SENT1MD enabled; CLC1MD enabled; CLC2MD enabled; 
    PMD8 = 0x00;
    // CF no clock failure; NOSC PRIPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x03));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);
}

bool CLOCK_AuxPllLockStatusGet()
{
    return ACLKCON1bits.APLLCK;
}
