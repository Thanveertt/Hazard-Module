#include <pic18.h>
#include <xc.h>

void delay();
void blink_pattern_0();
void blink_pattern_1();
void blink_pattern_2();
void blink_pattern_3();
void blink_pattern_4();
void blink_pattern_5();
void blink_pattern_6();
void blink_pattern_7();
void blink_pattern_8();
void blink_pattern_9();
void blink_pattern_10();
void blink_pattern_11();
void blink_pattern_12();
void blink_pattern_13();
void blink_pattern_14();
void blink_pattern_15();
void blink_pattern_16();
void blink_pattern_17();
void blink_pattern_18();
void blink_pattern_19();
void blink_pattern_20();
void blink_pattern_21();
void blink_pattern_22();
void blink_pattern_23();
void blink_pattern_24();
void blink_pattern_25();
void blink_pattern_26();
void blink_pattern_27();
void blink_pattern_28();
void blink_pattern_29();
void blink_pattern_30();
void blink_pattern_31();
void blink_pattern_32();
void blink_pattern_33();
void blink_pattern_34();
void blink_pattern_35();
void blink_pattern_36();
void blink_pattern_37();
void blink_pattern_38();
void blink_pattern_39();
void blink_pattern_40();
void blink_pattern_41();
void blink_pattern_42();
void blink_pattern_43();
void blink_pattern_44();
void blink_pattern_45();
void blink_pattern_46();
void blink_pattern_47();
void blink_pattern_48();
void blink_pattern_49();
void blink_pattern_50();
void blink_pattern_51();
void blink_pattern_52();
void blink_pattern_53();
void blink_pattern_54();
void blink_pattern_55();
void blink_pattern_56();
void blink_pattern_57();
void blink_pattern_58();
void blink_pattern_59();
void blink_pattern_60();
void blink_pattern_61();
void blink_pattern_62();
void blink_pattern_63();
void blink_pattern_64();
void blink_pattern_65();
void blink_pattern_66();
void blink_pattern_67();
void blink_pattern_68();
void blink_pattern_69();
void blink_pattern_70();
void blink_pattern_71();
void blink_pattern_72();
void blink_pattern_73();
void blink_pattern_74();
void blink_pattern_75();
void blink_pattern_76();
void blink_pattern_77();
void blink_pattern_78();
void blink_pattern_79();
void blink_pattern_80();
void blink_pattern_81();
void blink_pattern_82();
void blink_pattern_83();
void blink_pattern_84();
void blink_pattern_85();
void blink_pattern_86();
void blink_pattern_87();
void blink_pattern_88();
void blink_pattern_89();
void blink_pattern_90();
void blink_pattern_91();
void blink_pattern_92();
void blink_pattern_93();
void blink_pattern_94();
void blink_pattern_95();
void blink_pattern_96();
void blink_pattern_97();
void blink_pattern_98();
void blink_pattern_99();

// Array of function pointers
void (*patterns[100])() = {
    blink_pattern_0, blink_pattern_1, blink_pattern_2, blink_pattern_3, blink_pattern_4,
    blink_pattern_5, blink_pattern_6, blink_pattern_7, blink_pattern_8, blink_pattern_9,
    blink_pattern_10, blink_pattern_11, blink_pattern_12, blink_pattern_13, blink_pattern_14,
    blink_pattern_15, blink_pattern_16, blink_pattern_17, blink_pattern_18, blink_pattern_19,
    blink_pattern_20, blink_pattern_21, blink_pattern_22, blink_pattern_23, blink_pattern_24,
    blink_pattern_25, blink_pattern_26, blink_pattern_27, blink_pattern_28, blink_pattern_29,
    blink_pattern_30, blink_pattern_31, blink_pattern_32, blink_pattern_33, blink_pattern_34,
    blink_pattern_35, blink_pattern_36, blink_pattern_37, blink_pattern_38, blink_pattern_39,
    blink_pattern_40, blink_pattern_41, blink_pattern_42, blink_pattern_43, blink_pattern_44,
    blink_pattern_45, blink_pattern_46, blink_pattern_47, blink_pattern_48, blink_pattern_49,
    blink_pattern_50, blink_pattern_51, blink_pattern_52, blink_pattern_53, blink_pattern_54,
    blink_pattern_55, blink_pattern_56, blink_pattern_57, blink_pattern_58, blink_pattern_59,
    blink_pattern_60, blink_pattern_61, blink_pattern_62, blink_pattern_63, blink_pattern_64,
    blink_pattern_65, blink_pattern_66, blink_pattern_67, blink_pattern_68, blink_pattern_69,
    blink_pattern_70, blink_pattern_71, blink_pattern_72, blink_pattern_73, blink_pattern_74,
    blink_pattern_75, blink_pattern_76, blink_pattern_77, blink_pattern_78, blink_pattern_79,
    blink_pattern_80, blink_pattern_81, blink_pattern_82, blink_pattern_83, blink_pattern_84,
    blink_pattern_85, blink_pattern_86, blink_pattern_87, blink_pattern_88, blink_pattern_89,
    blink_pattern_90, blink_pattern_91, blink_pattern_92, blink_pattern_93, blink_pattern_94,
    blink_pattern_95, blink_pattern_96, blink_pattern_97, blink_pattern_98, blink_pattern_99
};

unsigned char pattern = 0;
unsigned char buttonPressed = 0;
unsigned int longPressCounter = 0;
const unsigned int LONG_PRESS_THRESHOLD = 500; // Adjust based on the delay needed for a long press


void savePatternToEEPROM(unsigned char pattern) {
    EEADR = 0x00;        // Set EEPROM address
    EEDATA = pattern;     // Load data to write
    EECON1bits.EEPGD = 0; // Access data memory
    EECON1bits.WREN = 1;  // Enable write

    // Required write sequence
    INTCONbits.GIE = 0;   // Disable interrupts
    EECON2 = 0x55;        // Write 0x55 to EECON2
    EECON2 = 0xAA;        // Write 0xAA to EECON2
    EECON1bits.WR = 1;    // Start write
    INTCONbits.GIE = 1;   // Re-enable interrupts

    while (EECON1bits.WR); // Wait for write to complete
    EECON1bits.WREN = 0;   // Disable write
}

unsigned char readPatternFromEEPROM() {
    EEADR = 0x00;          // Set EEPROM address
    EECON1bits.EEPGD = 0;  // Access data memory
    EECON1bits.RD = 1;     // Start read
    return EEDATA;         // Return the data read
}

void main() {
    TRISB = 0x00;         // Set PORTB as output
    TRISD = 0x00;         // Set PORTD as output
    TRISA = 0X00;         // Set PORTA as output
    TRISC = 0xFF;         // Set PORTC as input (for button)

    // Initialize pattern from EEPROM on startup
    pattern = readPatternFromEEPROM();

    while (1) {
        // Check if the button is pressed
        if (RC0 == 0) {
            if (!buttonPressed) {
                buttonPressed = 1;
                pattern = (pattern + 1) % 100; // Cycle through 100 patterns
                savePatternToEEPROM(pattern); // Save current pattern to EEPROM
                delay(); // Debounce delay
            }

            // Increment long press counter while button is held down
            longPressCounter++;

            // If button is held down for the long press threshold, reset pattern
            if (longPressCounter > LONG_PRESS_THRESHOLD) {
                pattern = 0; // Reset to the initial position
                savePatternToEEPROM(pattern); // Save reset pattern to EEPROM
                longPressCounter = 0; // Reset counter
            }
        } else {
            buttonPressed = 0;
            longPressCounter = 0; // Reset counter if button is released
        }

        // Execute the current pattern
        patterns[pattern]();
    }
}

// Blink Pattern Functions
void blink_pattern_0()
{
    PORTB = 0xF0;
    PORTD = 0xF0;
    delay();
    PORTB = 0x0F;
    PORTD = 0x0F;
    delay();
}

void blink_pattern_1()
{
    PORTB = 0xFF;
    PORTD = 0xFF;
    delay();
    PORTB = 0x00;
    PORTD = 0x00;
    delay();
}

void blink_pattern_2()
{
    PORTB = 0xAA;
    PORTD = 0xAA;
    delay();
    PORTB = 0x55;
    PORTD = 0x55;
    delay();
}

void blink_pattern_3()
{
    PORTB = 0xF0;
    PORTD = 0xF0;
    delay();
    PORTB = 0x00;
    PORTD = 0x00;
    delay();
    PORTB = 0x0F;
    PORTD = 0x0F;
    delay();
}

void blink_pattern_4()
{
    PORTB = 0xFF;
    PORTD = 0xFF;
    delay();
    PORTB = 0x00;
    PORTD = 0x00;
    delay();
}

void blink_pattern_5()
{
    PORTB = 0x55;
    PORTD = 0xAA;
    delay();
    PORTB = 0xAA;
    PORTD = 0x55;
    delay();
}

void blink_pattern_6()
{
    PORTB = 0xCC;
    PORTD = 0x33;
    delay();
    PORTB = 0x33;
    PORTD = 0xCC;
    delay();
}

void blink_pattern_7()
{
    PORTB = 0x00;
    PORTD = 0xFF;
    delay();
    PORTB = 0xFF;
    PORTD = 0x00;
    delay();
}

void blink_pattern_8()
{
    PORTB = 0xF0;
    PORTD = 0x0F;
    delay();
    PORTB = 0x0F;
    PORTD = 0xF0;
    delay();
}

void blink_pattern_9()
{
    PORTB = 0xAA;
    PORTD = 0x55;
    delay();
    PORTB = 0x55;
    PORTD = 0xAA;
    delay();
}

void blink_pattern_10()
{
    PORTB = 0xF8;
    PORTD = 0x07;
    delay();
    PORTB = 0x07;
    PORTD = 0xF8;
    delay();
}

// Patterns 11 to 99
void blink_pattern_11() { PORTB = 0x01; PORTD = 0x01; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_12() { PORTB = 0x02; PORTD = 0x02; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_13() { PORTB = 0x04; PORTD = 0x04; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_14() { PORTB = 0x08; PORTD = 0x08; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_15() { PORTB = 0x10; PORTD = 0x10; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_16() { PORTB = 0x20; PORTD = 0x20; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_17() { PORTB = 0x40; PORTD = 0x40; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_18() { PORTB = 0x80; PORTD = 0x80; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_19() { PORTB = 0xFF; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xFF; delay(); }

void blink_pattern_20() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_21() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_22() { PORTB = 0xCC; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xCC; delay(); }
void blink_pattern_23() { PORTB = 0x33; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x33; delay(); }
void blink_pattern_24() { PORTB = 0xF0; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xF0; delay(); }
void blink_pattern_25() { PORTB = 0x0F; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x0F; delay(); }
void blink_pattern_26() { PORTB = 0xFF; PORTD = 0xFF; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_27() { PORTB = 0x0A; PORTD = 0x0A; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_28() { PORTB = 0x0A; PORTD = 0xF0; delay(); PORTB = 0x0F; PORTD = 0x00; delay(); }
void blink_pattern_29() { PORTB = 0xF0; PORTD = 0x0A; delay(); PORTB = 0x0F; PORTD = 0x00; delay(); }

void blink_pattern_30() { PORTB = 0xAA; PORTD = 0xF0; delay(); PORTB = 0x00; PORTD = 0x0A; delay(); }
void blink_pattern_31() { PORTB = 0xF0; PORTD = 0x55; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_32() { PORTB = 0x55; PORTD = 0xAA; delay(); PORTB = 0x00; PORTD = 0xF0; delay(); }
void blink_pattern_33() { PORTB = 0xF0; PORTD = 0xCC; delay(); PORTB = 0x00; PORTD = 0x33; delay(); }
void blink_pattern_34() { PORTB = 0xCC; PORTD = 0x33; delay(); PORTB = 0x00; PORTD = 0xF0; delay(); }
void blink_pattern_35() { PORTB = 0x33; PORTD = 0xF0; delay(); PORTB = 0x00; PORTD = 0xCC; delay(); }
void blink_pattern_36() { PORTB = 0x0F; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_37() { PORTB = 0xF0; PORTD = 0x0F; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_38() { PORTB = 0xAA; PORTD = 0xAA; delay(); PORTB = 0x55; PORTD = 0x55; delay(); }
void blink_pattern_39() { PORTB = 0x55; PORTD = 0x55; delay(); PORTB = 0xAA; PORTD = 0xAA; delay(); }

void blink_pattern_40() { PORTB = 0xF0; PORTD = 0xF0; delay(); PORTB = 0x0F; PORTD = 0x0F; delay(); }
void blink_pattern_41() { PORTB = 0x0F; PORTD = 0x0F; delay(); PORTB = 0xF0; PORTD = 0xF0; delay(); }
void blink_pattern_42() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_43() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_44() { PORTB = 0xFF; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_45() { PORTB = 0x00; PORTD = 0xFF; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_46() { PORTB = 0x55; PORTD = 0xAA; delay(); PORTB = 0xAA; PORTD = 0x55; delay(); }
void blink_pattern_47() { PORTB = 0xAA; PORTD = 0x55; delay(); PORTB = 0x55; PORTD = 0xAA; delay(); }
void blink_pattern_48() { PORTB = 0xF0; PORTD = 0x0F; delay(); PORTB = 0x0F; PORTD = 0xF0; delay(); }
void blink_pattern_49() { PORTB = 0x0F; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }

void blink_pattern_50() { PORTB = 0x01; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_51() { PORTB = 0x02; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_52() { PORTB = 0x04; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_53() { PORTB = 0x08; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_54() { PORTB = 0x10; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_55() { PORTB = 0x20; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_56() { PORTB = 0x40; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_57() { PORTB = 0x80; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_58() { PORTB = 0xFF; PORTD = 0xFF; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_59() { PORTB = 0x00; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }

void blink_pattern_60() { PORTB = 0xFF; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xFF; delay(); }
void blink_pattern_61() { PORTB = 0x00; PORTD = 0xFF; delay(); PORTB = 0xFF; PORTD = 0x00; delay(); }
void blink_pattern_62() { PORTB = 0xF0; PORTD = 0x0F; delay(); PORTB = 0x0F; PORTD = 0xF0; delay(); }
void blink_pattern_63() { PORTB = 0x0F; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_64() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_65() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_66() { PORTB = 0xCC; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xCC; delay(); }
void blink_pattern_67() { PORTB = 0x33; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x33; delay(); }
void blink_pattern_68() { PORTB = 0xF0; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xF0; delay(); }
void blink_pattern_69() { PORTB = 0x0F; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x0F; delay(); }

void blink_pattern_70() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_71() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_72() { PORTB = 0xFF; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_73() { PORTB = 0x00; PORTD = 0xFF; delay(); PORTB = 0xFF; PORTD = 0x00; delay(); }
void blink_pattern_74() { PORTB = 0xF0; PORTD = 0x0F; delay(); PORTB = 0x0F; PORTD = 0xF0; delay(); }
void blink_pattern_75() { PORTB = 0x0F; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_76() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_77() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_78() { PORTB = 0xCC; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xCC; delay(); }
void blink_pattern_79() { PORTB = 0x33; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x33; delay(); }

void blink_pattern_80() { PORTB = 0xF0; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xF0; delay(); }
void blink_pattern_81() { PORTB = 0x0F; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x0F; delay(); }
void blink_pattern_82() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_83() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_84() { PORTB = 0xFF; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_85() { PORTB = 0x00; PORTD = 0xFF; delay(); PORTB = 0xFF; PORTD = 0x00; delay(); }
void blink_pattern_86() { PORTB = 0xF0; PORTD = 0x0F; delay(); PORTB = 0x0F; PORTD = 0xF0; delay(); }
void blink_pattern_87() { PORTB = 0x0F; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }
void blink_pattern_88() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_89() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }

void blink_pattern_90() { PORTB = 0xCC; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xCC; delay(); }
void blink_pattern_91() { PORTB = 0x33; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x33; delay(); }
void blink_pattern_92() { PORTB = 0xF0; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xF0; delay(); }
void blink_pattern_93() { PORTB = 0x0F; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x0F; delay(); }
void blink_pattern_94() { PORTB = 0x55; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0xAA; delay(); }
void blink_pattern_95() { PORTB = 0xAA; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x55; delay(); }
void blink_pattern_96() { PORTB = 0xFF; PORTD = 0x00; delay(); PORTB = 0x00; PORTD = 0x00; delay(); }
void blink_pattern_97() { PORTB = 0x00; PORTD = 0xFF; delay(); PORTB = 0xFF; PORTD = 0x00; delay(); }
void blink_pattern_98() { PORTB = 0xF0; PORTD = 0x0F; delay(); PORTB = 0x0F; PORTD = 0xF0; delay(); }
void blink_pattern_99() { PORTB = 0x0F; PORTD = 0xF0; delay(); PORTB = 0xF0; PORTD = 0x00; delay(); }

void delay()
{
    // Simple delay function (adjust as needed)
    for (volatile unsigned int i = 0; i < 1000; i++);
}
