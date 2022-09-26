#define EXTERN //global variables defined here
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/delay.h"
// <editor-fold defaultstate="collapsed" desc="tables">


const int therm[40] = {1082, 1052, 1023, 994, 966, 938, 912, 886,
    860, 836, 812, 789, 766, 744, 722, 701, 681,
    661, 642, 624, 606, 588, 571, 555, 539, 523,
    508, 494, 480, 466, 453};


const unsigned int CRC16Table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

// </editor-fold>
#include "main.h"

void init_PIDs(void);
void TransmitData(void);
size_t cobsEncode(volatile uint8_t *, size_t, volatile uint8_t *);

int main(void) {
    volatile uint16_t temprms, tempvac;
    volatile uint16_t tempuint;
    volatile int16_t tempint;
    volatile int16_t ssdelay;
    volatile int16_t vpidgained;

    // <editor-fold defaultstate="collapsed" desc="Initialize ">

    SYSTEM_Initialize();
    //    DIS_LLCPWM
    DIS_PFCPWM
    PFC_ENA_SetHigh(); // we use I/O control from here on out
    //temp keep llc off
    DISABLE_LLC_SetHigh(); //ditto
    init_PIDs();

    systemstate_pfc = STANDBYPFC;
    oldstate_pfc = NOTASTATEPFC;

    //    systemstate_llc = STANDBYLLC;
    //    oldstate_llc = NOTASTATELLC;

    pfc_voltage_skip = 20;
    pfc_voltage_counter = 0;
    currentcomparatortripped = false;
    one_over_voltage = 0;
    vbus_setpoint = VBUSSETPOINT;
    // </editor-fold>
    vmeasindex = 0;
    //delay to turn on inrush
    DELAY_milliseconds(300);
    INRUSH_ENA_SetHigh();
    DELAY_milliseconds(20);
    ocp_counter = 0;

    /*  this checks for open circuits on the temperature sensors  */
    if ((temperature1_adc < 200) || (temperature1_adc > 3800)
            || (temperature2_adc < 200) || (temperature2_adc > 3800)) {
        systemstate_pfc = FAULTPFC;
    }

    while (1) {

        if (newadcdata == true) {
            newadcdata = false;
            temprms = vacrms >> 7; //need to reduce value to prevent overflow
            //calculate feed forward term, limit current/power knee at 100vac so current doesn't keep increasing.
            if (temprms < 64) { //this is at 100V, 5.5A for 550W
                temprms = 64;
            }
            if (temprms > 255) {
                temprms = 255;
            }
            //feedforward = K/V^2; times V becomes 1/V 
            tempuint = (uint16_t) (__builtin_muluu(temprms, temprms));
            feedforward = (uint16_t) (__builtin_divud(PFC_K, tempuint));

            /**************  pfc state machine  *****************/

            if (systemstate_pfc != oldstate_pfc) {
                oldstate_pfc = systemstate_pfc;
                statechanged_pfc = true;
            }

            switch (systemstate_pfc) {
                case STANDBYPFC:
                    if (statechanged_pfc == true) {
                        statechanged_pfc = false;
                        VpfcPID.controlReference = 0;
                        VpfcPID.controlOutput = 0;
                        IpfcPID.controlOutput = 0;
                        DIS_PFCPWM;
#ifndef LLCONLY
                        DISABLE_LLC_SetHigh(); //ditto; this disables the driver, the control pin is 'disable'
#else
                        DISABLE_LLC_SetLow();
#endif
                        PG2DC = 0;
                        PG3DC = 0;
                        DELAY_milliseconds(200);
                    }
#ifdef DEBUGGING
                    systemstate_pfc = SOFTSTARTPFC;
#else
                    if (vacrms > (VACADC(VTURNON) << 3)) {
                        systemstate_pfc = SOFTSTARTPFC;
                    }
#endif
                    break;

                case SOFTSTARTPFC: //during this phase keep LLC off
                    if (statechanged_pfc == true) {
                        statechanged_pfc = false;
                        VpfcPID.controlReference = hvbus_adc - (hvbus_adc >> 2); //start at 75% of Vbus
                        ENA_PFCPWM;
                    }
                    if (++ssdelay > 5) { //inner counter to further slow down initial rise time
                        ssdelay = 0;
                        if (++VpfcPID.controlReference > vbus_setpoint) {
                            VpfcPID.controlReference = vbus_setpoint;
                            systemstate_pfc = RUNNINGPFC;
                        }
                    }
                    /* we don't need break, software is the precursor to running*/
                case RUNNINGPFC:
                    if (statechanged_pfc == true) {
                        statechanged_pfc = false;
                        //may want to verify the secondary is responding to commands
                        //we need to verify the secondary is controlling the pins
#ifndef LLCONLY
                        if ((_RB14 == 0)&&(_RB15 == 0)) {
#ifndef DISABLELLCONLY
                            DISABLE_LLC_SetLow(); //ditto
#endif
                        } else {
                            statechanged_pfc = FAULTPFC;
                        }
#endif
                    }
#ifndef DEBUGGING
                    if (vacrms < (VACADC(VTURNOFF) << 3)) {
                        lowvinstatus = true;
                    } else {
                        lowvinstatus = false;
                        lowvin_ms_counter = 0;
                    }
                    if (lowvin_ms_counter > 30) {
                        systemstate_pfc = STANDBYPFC;
                    }
#endif
                    //run current PID each time
                    //calculate the math so that the output of the voltage PID = watts x 50
                    //27500 = 550W
                    tempvac = vac_adc >> 4;
                    one_over_voltage = (int16_t) (__builtin_mulss(feedforward, tempvac) >> 10);
                    tempvac = (int16_t) (__builtin_mulss(one_over_voltage, vpidgained) >> 14);
                    tempvac = tempvac >>1;
                    if (tempvac > IMAX) {
                        tempvac = IMAX;
                    }
                    IpfcPID.controlReference = tempvac;

                    //the voltage integration is done less frequently
                    //we set the values for proportional only or with integration
                    VpfcPID.measuredOutput = hvbus_adc;
                    if (++pfc_voltage_counter > pfc_voltage_skip) {
                        pfc_voltage_counter = 0;
                        VpfcPID.abcCoefficients[0] = PID_VPFC_A;
                    } else {
                        VpfcPID.abcCoefficients[0] = PID_VPFC_A_P;
                    }
                    PID(&VpfcPID);
#ifndef LLCONLY
                    if (VpfcPID.controlOutput > MAXPOWER) {
                        VpfcPID.controlOutput = MAXPOWER;
//                        ++ocp_counter;
//                        if (ocp_counter > 50) {
//                            systemstate_pfc = FAULTPFC;
//                            ocp_counter = 50;
//                        }
//                    } else {
//                        ocp_counter = 0;
                    }
#endif
                    if (VpfcPID.controlOutput < 0) {
                        VpfcPID.controlOutput = 0;
                    }
                    vpidgained = VpfcPID.controlOutput << 1;
                    DAC2DATH = vpidgained >> 3;
                    if (VpfcPID.measuredOutput > VBUSOVP) {
                        VpfcPID.controlOutput = 0;
                    }
                    tempint = VpfcPID.measuredOutput - VpfcPID.controlReference;
                    if (tempint < (VBUS_DIVIDER(-20) << 2)) {
                        pfc_voltage_skip = 5;
                    } else if (tempint < (VBUS_DIVIDER(20.0) << 2)) {
                        pfc_voltage_skip = 10;
                    } else if (tempint < (VBUS_DIVIDER(30.0) << 2)) {
                        pfc_voltage_skip = 5;
                    } else {
                        pfc_voltage_skip = 1;
                    }


                    break;

                case FAULTPFC:
                    if (statechanged_pfc == true) {
                        statechanged_pfc = false;
                        VpfcPID.controlReference = 0;
                        VpfcPID.controlOutput = 0;
                        IpfcPID.controlOutput = 0;
                        DIS_PFCPWM
                        DISABLE_LLC_SetHigh(); //ditto
                        PG2DC = 0;
                        PG3DC = 0;
                        DELAY_milliseconds(200);
                    }
                    if (vacrms < (VACADC(VTURNOFF) << 3)) {
                        systemstate_pfc = STANDBYPFC;
                    }
                    break;

                case OVPPFC:
                    if (statechanged_pfc == true) {
                        statechanged_pfc = false;
                        //                        systemstate_llc = STANDBYLLC;
                        DELAY_milliseconds(500);
                    }
                    DIS_PFCPWM;
                    DISABLE_LLC_SetHigh(); //ditto
                    break;

                case OTPPFC:
                    if (statechanged_pfc == true) {
                        statechanged_pfc = false;
                        //                        systemstate_llc = STANDBYLLC;
                        DELAY_milliseconds(500);
                    }
                    DISABLE_LLC_SetHigh(); //ditto
                    DIS_PFCPWM;
                    if ((temperature1_adc > OTP_80DEGC_ON) && (temperature1_adc > OTP_80DEGC_ON)) {
                        systemstate_pfc = STANDBYPFC;
                    }
                    break;

                default:
                    systemstate_pfc = STANDBYPFC;
                    statechanged_pfc = false;
                    DIS_PFCPWM;
                    break;
            }
            TransmitData(); //send the values to the LLC converter
        }
    }
    return 1;
}

// <editor-fold defaultstate="collapsed" desc="PID Inits">

void init_PIDs(void) {

    //pfc current
    IpfcPID.abcCoefficients = IpfcPIDABC;
    IpfcPID.controlHistory = IpfcPIDHistory;

    PIDInit(&IpfcPID);

    IpfcPID.abcCoefficients[0] = PID_IPFC_A;
    IpfcPID.abcCoefficients[1] = PID_IPFC_B;
    IpfcPID.abcCoefficients[2] = PID_IPFC_C;
    IpfcPID.measuredOutput = 0;
    IpfcPID.controlOutput = 0;

    //pfc voltage
    VpfcPID.abcCoefficients = VpfcPIDABC;
    VpfcPID.controlHistory = VpfcPIDHistory;

    PIDInit(&VpfcPID);

    VpfcPID.abcCoefficients[0] = PID_VPFC_A;
    VpfcPID.abcCoefficients[1] = PID_VPFC_B;
    VpfcPID.abcCoefficients[2] = PID_VPFC_C;
    VpfcPID.measuredOutput = 0;
    VpfcPID.controlOutput = 0;
}
// </editor-fold>

/**
 End of File
 */

// <editor-fold defaultstate="collapsed" desc="TX Code">

void TransmitData(void) {
    static int txindex = 0;
    static uint8_t counter = 0;
    static unsigned int temp_tx;
    static unsigned int crctx;
    static int size;
    /* 1 = preparing buffer, 2 = COBS, 3 = transmit */
    static int transmitstate = 1;

    switch (transmitstate) {
        case 1:
            switch (txindex) {
                case 0:
                    temp_tx = systemstate_pfc;
                    bufferin[txindex] = temp_tx >> 8;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 1:
                    bufferin[txindex] = temp_tx & 0xFF;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 2:
                    temp_tx = 0x3344; //temperature2_adc;
                    bufferin[txindex] = temp_tx >> 8;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 3:
                    bufferin[txindex] = temp_tx & 0xFF;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 4:
                    temp_tx = vacrms;
                    bufferin[txindex] = temp_tx >> 8;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 5:
                    bufferin[txindex] = temp_tx & 0xFF;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 6:
                    temp_tx = 0x1122; //temperature1_adc;
                    bufferin[txindex] = temp_tx >> 8;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 7:
                    bufferin[txindex] = temp_tx & 0xFF;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 8:
                    temp_tx = VpfcPID.controlOutput;
                    bufferin[txindex] = temp_tx >> 8;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 9:
                    bufferin[txindex] = temp_tx & 0xFF;
                    crctx = (crctx << 8) ^ CRC16Table[((crctx >> 8)^(bufferin[txindex]))];
                    break;
                case 10:
                    bufferin[txindex] = crctx >> 8;
                    break;
                case 11:
                    bufferin[txindex] = crctx & 0xFF;
                    bufferin[txindex + 1] = counter++;
                    bufferin[txindex + 2] = 0;
                    break;
            }
            ++txindex;
            if (txindex == 12) {
                transmitstate = 2;
                txindex = 0;
                crctx = 0;
            }
            break;
        case 2:
            size = cobsEncode(bufferin, 14, bufferout);
            bufferout[size] = 0;
            txindex = 0;
            ++size;
            transmitstate = 3;
            break;
        case 3:
            if ((U1STAHbits.UTXBF == 0)&&(txtrigger == true)) { //check buffer is not full
                U1TXREG = bufferout[txindex];
                ++txindex;
                if (txindex == size) {
                    transmitstate = 1;
                    txindex = 0;
                }
            }
            break;
        default:
            transmitstate = 1;
            break;
    }
}
// </editor-fold>

/** COBS encode data to buffer
    @param data Pointer to input data to encode
    @param length Number of bytes to encode
    @param buffer Pointer to encoded output buffer
    @return Encoded buffer length in bytes
    @note Does not output delimiter byte
 */

size_t cobsEncode(volatile uint8_t *data, size_t length, volatile uint8_t *buffer) {

    volatile uint8_t *encode = buffer; // Encoded byte pointer
    volatile uint8_t *codep = encode++; // Output code pointer
    volatile uint8_t code = 1; // Code value
    volatile uint8_t *byte;


    for (byte = data; length--; ++byte) {
        if (*byte) // Byte not zero, write it
            *encode++ = *byte, ++code;

        if (!*byte) // Input is zero ** don't need to test for completed block never big, or block completed, restart
        {
            *codep = code, code = 1, codep = encode;
            if (!*byte || length)
                ++encode;
        }
    }
    *codep = code; // Write final code value

    return (size_t) (encode - buffer);
}

/** COBS decode data from buffer
    @param buffer Pointer to encoded input bytes
    @param length Number of bytes to decode
    @param data Pointer to decoded output data
    @return Number of bytes successfully decoded
    @note Stops decoding if delimiter byte is found
 */
size_t cobsDecode(const uint8_t *buffer, size_t length, void *data) {

    const uint8_t *byte = buffer; // Encoded input byte pointer
    volatile uint8_t *decode = (uint8_t *) data; // Decoded output byte pointer
    volatile uint8_t code;
    volatile int8_t block;

    for (code = 0xff, block = 0; byte < buffer + length; --block) {
        if (block) // Decode block byte
            *decode++ = *byte++;
        else {
            if (code != 0xff) // Encoded zero, write it
                *decode++ = 0;
            block = code = *byte++; // Next block length
            if (!code) // Delimiter code found
                break;
        }
    }

    return (size_t) (decode - (uint8_t *) data);
}
