#include "project.h"
#include "stdlib.h"

#define LED_ON 1u
#define LED_OFF 0u

#define INITIAL_LEVEL 1

// Function to check if the player's input matches the pattern
int checkInput(int arr[], int level) {
    int inputIndex = 0;
   
    while (inputIndex < level) {
        // Check whether the scanning of all enabled widgets is completed.
        if (0u == CapSense_IsBusy()) {
            // Update all baselines
            CapSense_UpdateEnabledBaselines();
            // Start scanning all enabled sensors
            CapSense_ScanEnabledWidgets();
        }
 uint8 rb;
    uint8 lb;
    rb = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
    lb = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
            if (rb) {
                // Button 0
                if (arr[inputIndex] != 0) {
                    return 0; // Incorrect
                }
                LED1_Write(LED_ON);
                CyDelay(500);
                LED1_Write(LED_OFF);
                CyDelay(500);
                inputIndex++;
                CyDelay(100); // Delay to prevent multiple inputs from a single press
                CapSense_InitializeAllBaselines();
            } else if (lb) {
                // Button 1
                if (arr[inputIndex] != 1) {
                    return 0; // Incorrect
                }
                LED2_Write(LED_ON);
                CyDelay(500);
                LED2_Write(LED_OFF);
                CyDelay(500);
                inputIndex++;
                CyDelay(100); // Delay to prevent multiple inputs from a single press
                CapSense_InitializeAllBaselines();
            }
        }
    return 1; // Correct input
}

int main(void) {
    CyGlobalIntEnable;
    int levelCount = INITIAL_LEVEL;
    int score = 0;
    int score1 = 0;
    int score2 = 0;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    CapSense_Start();
    
    
    for (;;) {   
        
        CapSense_InitializeAllBaselines();
        int level = levelCount;
        int arr[100]; // Fix the array size to prevent stack overflow
        /* Generate random pattern */
        for (int i = 0; i < level; i++) {
            int randomNum = rand() % 2;
            arr[i] = randomNum;
            if (randomNum == 0) {
                LED1_Write(LED_ON);
                CyDelay(500);
                LED1_Write(LED_OFF);
                CyDelay(500);
            } else {
                LED2_Write(LED_ON);
                CyDelay(500);
                LED2_Write(LED_OFF);
                CyDelay(500);
            }
        }
        /* Check player input */
        //
        if(checkInput(arr, level)) {
            score++;
            LCD_Position(0, 0);
            LCD_PrintString("Score:");
            LCD_PrintNumber(score);
            CyDelay(1000);
            levelCount++;
        }else{
            // Game over, reset level count and score
            LCD_Position(0, 0);
            LCD_PrintString("Game Over!");
            LCD_Position(1, 0);
            LCD_PrintString("Score:");
            LCD_PrintNumber(score);
            levelCount = INITIAL_LEVEL;
            score = 0;
            CyDelay(5000); // Delay to display "Game Over!" message for 5 seconds
            LCD_ClearDisplay(); // Clear LCD after delay
        }
    }
    }


/* [] END OF FILE */
