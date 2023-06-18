#ifndef __DEVIDECONFIG_H
#define __DEVIDECONFIG_H

/* Register DEVCFG3 */
#pragma config PGL1WAY = OFF                // Permission Group Lock One Way Configuration
#pragma config PMDL1WAY = OFF               // Peripheral Module Disable Configuration
#pragma config IOL1WAY = OFF                // Peripheral Pin Select Configuration

/* Register DEVCFG2 */
#pragma config FPLLIDIV = DIV_1             // System PLL Input Clock Divider
#pragma config FPLLRNG =  RANGE_8_16_MHZ    // System PLL Divided Input Clock Frequency Range
#pragma config FPLLICLK = PLL_FRC           // System PLL Input Clock Select
#pragma config FPLLMULT = MUL_60            // System PLL Feedback Divider
#pragma config FPLLODIV = DIV_4             // Default System PLL Output Divisor
#pragma config BORSEL = HIGH                // Brown-out trip voltage
#pragma config UPLLEN = OFF                 // USB PLL Enable

/* Register DEVCFG1 */
#pragma config FNOSC = SPLL                 // Oscillator Selection
#pragma config DMTINTV = WIN_127_128        // DMT Count Window Interval
#pragma config FSOSCEN = OFF                // Secondary Oscillator Enable
#pragma config IESO = OFF                   // Internal External Switchover
#pragma config POSCMOD = EC                 // Primary Oscillator Configuration
#pragma config OSCIOFNC = ON                // CLKO Enable Configuration
#pragma config FCKSM = CSECME               // Clock Switching and Monitoring Selection Configuration
#pragma config WDTPS = PS1048576            // Watchdog Timer Postscale Select
#pragma config WDTSPGM = STOP               // Watchdog Timer Stop During Flash Programming
#pragma config WINDIS = NORMAL              // Watchdog Timer Window Mode
#pragma config FWDTEN = OFF                 // Watchdog Timer Enable
#pragma config FWDTWINSZ = WINSZ_25         // Watchdog Timer Window Size
#pragma config DMTCNT = DMT31               // Deadman Timer Count Select
#pragma config FDMTEN = OFF                 // Deadman Timer enable

/* Register DEVCFG0 */
#pragma config DEBUG = OFF                  // Background Debugger Enable
#pragma config JTAGEN = OFF                 // JTAG Enable
#pragma config ICESEL = ICS_PGx1            // ICE/ICD Comm Channel Select
#pragma config TRCEN = OFF                  // Trace Enable
#pragma config BOOTISA = MIPS32             // Boot ISA Selection
#pragma config FECCCON = ECC_DECC_DISABLE_ECCON_WRITABLE   // Dynamic Flash ECC Configuration
#pragma config FSLEEP = OFF                 // Flash Sleep Mode
#pragma config DBGPER = PG_ALL              // Debug Mode CPU Access Permission
#pragma config SMCLR = MCLR_NORM            // Soft Master Clear Enable bit
#pragma config SOSCGAIN = G2                // Secondary Oscillator Gain Control bits
#pragma config SOSCBOOST = ON               // Secondary Oscillator Boost Kick Start Enable bit
#pragma config POSCGAIN = G2                // Primary Oscillator Gain Control bits
#pragma config POSCBOOST = ON               // Primary Oscillator Boost Kick Start Enable bit
#pragma config POSCFGAIN = G3               // Primary Oscillator Fine Gain Control bits
#pragma config POSCAGCDLY = AGCRNG_x_25ms   // AGC Gain Search Step Settling Time Control
#pragma config POSCAGC = Automatic          // Primary Oscillator Gain Control bit
#pragma config EJTAGBEN = NORMAL            // EJTAG Boot

/* Register DEVCP0 */
#pragma config CP = OFF                     // Code Protect

void Set_MaxSpeed_Mode(void){   
	
    // Unlock Sequence
    asm volatile("di");                     // Disable all interrupts
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;  

    // PB1DIV
    PB1DIVbits.PBDIV = 0;

    // PB2DIV
    PB2DIVbits.ON = 1;
    PB2DIVbits.PBDIV = 0;

    // PB3DIV
    PB3DIVbits.ON = 1;
    PB3DIVbits.PBDIV = 0;

    // PB4DIV
    PB4DIVbits.ON = 1;
    while (!PB4DIVbits.PBDIVRDY);
    PB4DIVbits.PBDIV = 0;

    // PB6DIV
    PB6DIVbits.ON = 1;
    PB6DIVbits.PBDIV = 0;

    // Lock Sequence
    SYSKEY = 0x00000000;
    asm volatile("ei");                     // Enable all interrupts
}

#endif /* __DEVIDECONFIG_H */