#include "adc1.h"
#include "../main.h"

// <editor-fold defaultstate="collapsed" desc="ADC Init">
void ADC1_Initialize(void) {
    // ADSIDL disabled; ADON enabled; 
    ADCON1L = (0x8000 & 0x7FFF); //Disabling ADON bit
    // FORM Integer; SHRRES 12-bit resolution; 
    ADCON1H = 0x60;
    // PTGEN disabled; SHRADCS 2; REFCIE disabled; SHREISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; REFERCIE disabled; EIEN disabled; 
    ADCON2L = 0x00;
    // SHRSAMC 0; 
    ADCON2H = 0x00;
    ADCON2Hbits.SHRSAMC = 15;
    // SWCTRG disabled; SHRSAMP disabled; SUSPEND disabled; SWLCTRG disabled; SUSPCIE disabled; CNVCHSEL AN0; REFSEL disabled; 
    ADCON3L = 0x00;
    // SHREN enabled; C1EN enabled; C0EN disabled; CLKDIV 1; CLKSEL FOSC/2; 
    ADCON3H = (0x82 & 0xFF00); //Disabling C0EN, C1EN, C2EN, C3EN and SHREN bits
    // SAMC0EN disabled; SAMC1EN disabled; 
    ADCON4L = 0x00;
    // C0CHS AN0; C1CHS AN1; 
    ADCON4H = 0x00;
    // SIGN0 disabled; SIGN4 disabled; SIGN3 disabled; SIGN2 disabled; SIGN1 disabled; SIGN7 disabled; SIGN6 disabled; DIFF0 disabled; SIGN5 disabled; DIFF1 disabled; DIFF2 disabled; DIFF3 disabled; DIFF4 disabled; DIFF5 disabled; DIFF6 disabled; DIFF7 disabled; 
    ADMOD0L = 0x00;
    // DIFF15 disabled; DIFF14 disabled; SIGN8 disabled; DIFF13 disabled; SIGN14 disabled; DIFF12 disabled; SIGN15 disabled; DIFF11 disabled; DIFF10 disabled; SIGN9 disabled; DIFF8 disabled; DIFF9 disabled; SIGN10 disabled; SIGN11 disabled; SIGN12 disabled; SIGN13 disabled; 
    ADMOD0H = 0x00;
    // DIFF25 disabled; SIGN25 disabled; 
    ADMOD1H = 0x00;
    // IE15 disabled; IE1 disabled; IE0 disabled; IE3 disabled; IE2 disabled; IE5 disabled; IE4 disabled; IE10 disabled; IE7 disabled; IE6 disabled; IE9 disabled; IE13 enabled; IE8 disabled; IE14 disabled; IE11 disabled; IE12 disabled; 
    ADIEL = 0x2000;
    // IE24 enabled; IE25 enabled; 
    ADIEH = 0x300;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP0ENL = 0x00;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP1ENL = 0x00;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP2ENL = 0x00;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP3ENL = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP0ENH = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP1ENH = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP2ENH = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP3ENH = 0x00;
    // CMPLO 0; 
    ADCMP0LO = 0x00;
    // CMPLO 0; 
    ADCMP1LO = 0x00;
    // CMPLO 0; 
    ADCMP2LO = 0x00;
    // CMPLO 0; 
    ADCMP3LO = 0x00;
    // CMPHI 0; 
    ADCMP0HI = 0x00;
    // CMPHI 0; 
    ADCMP1HI = 0x00;
    // CMPHI 0; 
    ADCMP2HI = 0x00;
    // CMPHI 0; 
    ADCMP3HI = 0x00;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL0CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL1CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL2CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL3CON = 0x400;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP0CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP1CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP2CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP3CON = 0x00;
    // LVLEN9 disabled; LVLEN8 disabled; LVLEN11 disabled; LVLEN7 disabled; LVLEN10 disabled; LVLEN6 disabled; LVLEN13 disabled; LVLEN5 disabled; LVLEN12 disabled; LVLEN4 disabled; LVLEN15 disabled; LVLEN3 disabled; LVLEN14 disabled; LVLEN2 disabled; LVLEN1 disabled; LVLEN0 disabled; 
    ADLVLTRGL = 0x00;
    // LVLEN24 disabled; LVLEN25 disabled; 
    ADLVLTRGH = 0x00;
    // SAMC 0; 
    ADCORE0L = 0x00;
    // SAMC 0; 
    ADCORE1L = 0x00;
    // RES 12-bit resolution; EISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; ADCS 2; 
    ADCORE0H = 0x300;
    // RES 12-bit resolution; EISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; ADCS 2; 
    ADCORE1H = 0x300;
    // EIEN9 disabled; EIEN7 disabled; EIEN8 disabled; EIEN5 disabled; EIEN6 disabled; EIEN3 disabled; EIEN4 disabled; EIEN1 disabled; EIEN2 disabled; EIEN13 disabled; EIEN0 disabled; EIEN12 disabled; EIEN11 disabled; EIEN10 disabled; EIEN15 disabled; EIEN14 disabled; 
    ADEIEL = 0x00;
    // EIEN25 disabled; EIEN24 disabled; 
    ADEIEH = 0x00;
    // C0CIE disabled; C1CIE disabled; SHRCIE disabled; WARMTIME 32768 Source Clock Periods; 
    ADCON5H = (0xF00 & 0xF0FF); //Disabling WARMTIME bit

    // Clearing TEMPERATURE2_ADC interrupt flag.
    IFS6bits.ADCAN13IF = 0;
    // Enabling TEMPERATURE2_ADC interrupt.
    IEC6bits.ADCAN13IE = 1;
    // Clearing channel_AN24 interrupt flag.
    IFS12bits.ADCAN24IF = 0;
    // NOT Enabling channel_AN24 interrupt.
    IEC12bits.ADCAN24IE = 0;
    // Clearing channel_AN25 interrupt flag.
    IFS12bits.ADCAN25IF = 0;
    // NOT Enabling channel_AN25 interrupt.
    IEC12bits.ADCAN25IE = 0;

    // Setting WARMTIME bit
    ADCON5Hbits.WARMTIME = 0xF;
    // Enabling ADC Module
    ADCON1Lbits.ADON = 0x1;
    // Enabling Power for the Shared Core
    ADC1_SharedCorePowerEnable();
    // Enabling Power for Core1
    ADC1_Core1PowerEnable();

    //TRGSRC0 None; TRGSRC1 SCCP1; 
    ADTRIG0L = 0x1400;
    //TRGSRC3 None; TRGSRC2 PWM2 Trigger2; 
    ADTRIG0H = 0x07;
    //TRGSRC4 PWM2 Trigger2; TRGSRC5 None; 
    ADTRIG1L = 0x07;
    //TRGSRC6 None; TRGSRC7 None; 
    ADTRIG1H = 0x00;
    //TRGSRC8 None; TRGSRC9 None; 
    ADTRIG2L = 0x00;
    //TRGSRC11 PWM2 Trigger2; TRGSRC10 PWM2 Trigger2; 
    ADTRIG2H = 0x0707;
    //TRGSRC13 PWM2 Trigger2; TRGSRC12 None; 
    ADTRIG3L = 0x700;
    //TRGSRC15 None; TRGSRC14 None; 
    ADTRIG3H = 0x00;
    //TRGSRC24 Common Software Trigger; TRGSRC25 Common Software Trigger; 
    ADTRIG6L = 0x101;
}

void ADC1_Core0PowerEnable() {
    ADCON5Lbits.C0PWR = 1;
    while (ADCON5Lbits.C0RDY == 0);
    ADCON3Hbits.C0EN = 1;
}

void ADC1_Core1PowerEnable() {
    ADCON5Lbits.C1PWR = 1;
    while (ADCON5Lbits.C1RDY == 0);
    ADCON3Hbits.C1EN = 1;
}

void ADC1_SharedCorePowerEnable() {
    ADCON5Lbits.SHRPWR = 1;
    while (ADCON5Lbits.SHRRDY == 0);
    ADCON3Hbits.SHREN = 1;
}

// </editor-fold>

void __attribute__((__interrupt__, auto_psv, weak)) _ADCAN13Interrupt(void) {
    //AN1 = I_PFC_ADC, OVERSAMPLED
    //AN2 = HVBUS_ADC
    //AN4 = TEMPERATURE1_ADC
    //AN10 = VAC1_ADC
    //AN11 = VAC2_ADC
    //AN13 = TEMPERATURE2_ADC

    static int32_t vac_filter;
    volatile int16_t tempint2;

    hvbus_adc = ADCBUF2 << 2;
    tempint2 = abs(ADCBUF10 - ADCBUF11);
    
    vac_filter = vac_filter - (vac_filter >> 3) + (tempint2 << 3);
    vac_adc = vac_filter >> 3;
    temperature1_adc = ADCBUF4;
    temperature2_adc = ADCBUF13;
   
    newadcdata = true;

    //clear the TEMPERATURE2_ADC interrupt flag
    IFS6bits.ADCAN13IF = 0;
}

//these are not intended to be used, they are 'just in case' the configurator turns them on
void __attribute__((__interrupt__, auto_psv, weak)) _ADCAN24Interrupt(void) {

    IFS12bits.ADCAN24IF = 0;
}

void __attribute__((__interrupt__, auto_psv, weak)) _ADCAN25Interrupt(void) {

    IFS12bits.ADCAN25IF = 0;
}




/**
  End of File
 */
