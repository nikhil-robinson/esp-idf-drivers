#include <stdio.h>
#include <i2cdev.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>

#include <esp_log.h>
#include <esp_err.h>

#include <ds1307.h>
#include <at24c32.h>



void ds1307_test(void *pvParameters)
{

    EEPROM_t eeprom;
    memset(&eeprom, 0, sizeof(EEPROM_t));

    esp_err_t eeprom_init_result = InitRom(&eeprom, 0); // Initialize EEPROM
    if (eeprom_init_result != ESP_OK)
    {
        printf("Failed to initialize EEPROM\n");
    }
    else 
    {
        printf("successfullly initialized eeprom\n");
    }

    // uint16_t readYear;
    //     uint8_t readMon;
    //     uint8_t readDay;
    //     uint8_t readHour;
    //     uint8_t readMin;
    //     uint8_t readSec;
           
    //     ReadRom(&eeprom , 0x00 , &readYear);
    //     ReadRom(&eeprom , 0x02 , &readMon);
    //     ReadRom(&eeprom , 0x03 , &readDay);
    //     ReadRom(&eeprom , 0x04 , &readHour);
    //     ReadRom(&eeprom , 0x05 , &readMin);
    //     ReadRom(&eeprom , 0x06 , &readSec);
           
   
    //     printf("Read time from EEPROM: %04d-%02d-%02d %02d:%02d:%02d\n", readYear+ 1900, readMon + 1,
    //     readDay, readHour, readMin, readSec);

        i2c_driver_delete(I2C_NUM_0);

    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));

    esp_err_t ds1307Result = ds1307_init_desc(&dev, 0, 8, 9);
    if(ds1307Result != ESP_OK)
    {
         printf("Failed to initialize ds1307\n");
    }
    else
    {
        printf("successfullly initialzed ds1307\n");
    }

    //     struct tm time = {
    //     .tm_year = readYear,
    //     .tm_mon = readMon,
    //     .tm_mday = readDay,
    //     .tm_hour = readHour,
    //     .tm_min = readMin,
    //     .tm_sec = readSec,
    // };

    
    //     struct tm time = {
    //     .tm_year = 123,
    //     .tm_mon = 8,
    //     .tm_mday = 19,
    //     .tm_hour = 11,
    //     .tm_min = 20,
    //     .tm_sec = 30,
    // };
    // ESP_ERROR_CHECK(ds1307_set_time(&dev, &time));

    while (1)
    {
   
        struct tm time;
        ds1307_get_time(&dev, &time);

        printf("%04d-%02d-%02d %02d:%02d:%02d\n", time.tm_year + 1900, time.tm_mon ,
            time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);

    i2c_driver_delete(I2C_NUM_0);

    EEPROM_t eeprom;
    memset(&eeprom, 0, sizeof(EEPROM_t));

    esp_err_t eeprom_init_result = InitRom(&eeprom, 0); // Initialize EEPROM
    if (eeprom_init_result != ESP_OK)
    {
        printf("Failed to initialize EEPROM\n");
    }
    else 
    {
        printf("successfullly initialized eeprom\n");
    }


        uint8_t writeYear = time.tm_year;
        uint8_t writemon = time.tm_mon;
        uint8_t writeday = time.tm_mday;
        uint8_t writeHour = time.tm_hour;
        uint8_t writeMin = time.tm_min;
        uint8_t writeSec = time.tm_sec;

        WriteRom(&eeprom,0x00 , writeYear);
        WriteRom(&eeprom,0x02 , writemon);
        WriteRom(&eeprom,0x03 , writeday);
        WriteRom(&eeprom,0x04 , writeHour);
        WriteRom(&eeprom,0x05 , writeMin);
        WriteRom(&eeprom,0x06 , writeSec);

        printf("write time to EEPROM: %04d-%02d-%02d %02d:%02d:%02d\n", writeYear+ 1900, writemon + 1,
        writeday, writeHour, writeMin, writeSec);

      


        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main()
{
    ESP_ERROR_CHECK(i2cdev_init());

    xTaskCreate(ds1307_test, "ds1307_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);
}

