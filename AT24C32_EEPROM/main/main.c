#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <driver/i2c.h>

#include <esp_log.h>
#include <esp_err.h>

#include <at24c32.h>



void at24c32Test(void *pvParameters)
{
    
    EEPROM_t eeprom;
    memset(&eeprom, 0, sizeof(EEPROM_t));


    esp_err_t eeprom_init_result = InitRom(&eeprom, I2C_NUM_0); // Initialize EEPROM
    if (eeprom_init_result != ESP_OK)
    {
        printf("Failed to initialize EEPROM\n");
    }
    else 
    {
        printf("successfullly initilized eeprom\n");
    }


    //  struct tm currentTime = {
    //             .tm_year = 123,
    //             .tm_mon = 8,
    //             .tm_mday = 19,
    //             .tm_hour = 3,
    //             .tm_min = 3,
    //             .tm_sec = 30,
    //         };

    //     uint8_t writeYear = currentTime.tm_year;
    //     uint8_t writemon = currentTime.tm_mon;
    //     uint8_t writeday = currentTime.tm_mday;
    //     uint8_t writeHour = currentTime.tm_hour;
    //     uint8_t writeMin = currentTime.tm_min;
    //     uint8_t writeSec = currentTime.tm_sec;

    //     WriteRom(&eeprom,0x00 , writeYear);
    //     WriteRom(&eeprom,0x02 , writemon);
    //     WriteRom(&eeprom,0x03 , writeday);
    //     WriteRom(&eeprom,0x04 , writeHour);
    //     WriteRom(&eeprom,0x05 , writeMin);
    //     WriteRom(&eeprom,0x06 , writeSec);


    while (1)
    {
   

           uint16_t readYear;
           uint8_t readMon;
           uint8_t readDay;
           uint8_t readHour;
           uint8_t readMin;
           uint8_t readSec;
           
            ReadRom(&eeprom , 0x00 , &readYear);
            ReadRom(&eeprom , 0x02 , &readMon);
            ReadRom(&eeprom , 0x03 , &readDay);
            ReadRom(&eeprom , 0x04 , &readHour);
            ReadRom(&eeprom , 0x05 , &readMin);
            ReadRom(&eeprom , 0x06 , &readSec);
           
   
            printf("Read time from EEPROM: %04d-%02d-%02d %02d:%02d:%02d\n", readYear+ 1900, readMon + 1,
            readDay, readHour, readMin, readSec);
            

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main()
{
    
    xTaskCreate(at24c32Test, "at24c32_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);
}

