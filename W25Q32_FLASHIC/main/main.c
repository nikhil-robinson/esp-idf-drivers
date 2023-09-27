#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "w25q32.h"

#define TAG "W25Q32"

//
// Data dump list
// dt(in):Data to dump
// n(in) :Number of bytes of data
//
void dump(uint8_t *dt, int n)
{
	uint16_t clm = 0;
	uint8_t data;
	uint8_t sum;
	uint8_t vsum[16];
	uint8_t total =0;
	uint32_t saddr =0;
	uint32_t eaddr =n-1;

	printf("----------------------------------------------------------\n");
	uint16_t i;
	for (i=0;i<16;i++) vsum[i]=0;  
	uint32_t addr;
	for (addr = saddr; addr <= eaddr; addr++) {
		data = dt[addr];
		if (clm == 0) {
			sum =0;
			printf("%05"PRIx32": ",addr);
		}

		sum+=data;
		vsum[addr % 16]+=data;

		printf("%02x ",data);
		clm++;
		if (clm == 16) {
			printf("|%02x \n",sum);
			clm = 0;
		}
	}
	printf("----------------------------------------------------------\n");
	printf("       ");
	for (i=0; i<16;i++) {
		total+=vsum[i];
		printf("%02x ",vsum[i]);
	}
	printf("|%02x \n\n",total);
}

void app_main()
{
	W25Q32_t dev;
	W25Q32_init(&dev);

	// Get Status Register1
	uint8_t reg1;
	esp_err_t ret;
	ret = W25Q32_readStatusReg1(&dev, &reg1);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "readStatusReg1 fail %d",ret);
		while(1) { vTaskDelay(1); }
	} 
	ESP_LOGI(TAG, "readStatusReg1 : %x", reg1);
	
	// Get Status Register2
	uint8_t reg2;
	ret = W25Q32_readStatusReg2(&dev, &reg2);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "readStatusReg2 fail %d",ret);
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "readStatusReg2 : %x", reg2);
	// Get Unique ID
	uint8_t uid[8];
	ret = W25Q32_readUniqueID(&dev, uid);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "readUniqueID fail %d",ret);
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "readUniqueID : %x-%x-%x-%x-%x-%x-%x-%x",
		 uid[0], uid[1], uid[2], uid[3], uid[4], uid[5], uid[6], uid[7]);

	// Get JEDEC ID
	uint8_t jid[3];
	ret = W25Q32_readManufacturer(&dev, jid);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "readManufacturer fail %d",ret);
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "readManufacturer : %x-%x-%x",
		 jid[0], jid[1], jid[2]);

	// Read 256 byte data from Address=0
	uint8_t rbuf[256];    
	int len;
	memset(rbuf, 0, 256);
	len =  W25Q32_fastread(&dev, 0, rbuf, 256);
	if (len != 256) {
		ESP_LOGE(TAG, "fastread fail");
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "Fast Read Data: len=%d", len);
	dump(rbuf, 256);

	// Erase data by Sector
	bool flag = W25Q32_eraseSector(&dev, 0, true);
	if (flag == false) {
		ESP_LOGE(TAG, "eraseSector fail %d",ret);
		while(1) { vTaskDelay(1); }
	}
	memset(rbuf, 0, 256);
	len =  W25Q32_read(&dev, 0, rbuf, 256);
	if (len != 256) {
		ESP_LOGE(TAG, "read fail");
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "Read Data: len=%d", len);
	dump(rbuf, 256);

	// Write data to Sector=0 Address=10
	uint8_t wdata[26];    
	for (int i=0; i<26; i++) {
		wdata[i]='A'+i; // A-Z     
	}  
	len =  W25Q32_pageWrite(&dev, 0, 10, wdata, 26);
	if (len != 26) {
		ESP_LOGE(TAG, "pageWrite fail");
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "Page Write(Sector=0 Address=10) len=%d", len);

	// Fast read 256 byte data from Address=0
	memset(rbuf, 0, 256);
	len =  W25Q32_fastread(&dev, 0, rbuf, 256);
	if (len != 256) {
		ESP_LOGE(TAG, "fastread fail");
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "Fast Read Data: len=%d", len);
	dump(rbuf, 256);

	// Write data to Sector=0 Address=0
	for (int i=0; i < 10;i++) {
		wdata[i]='0'+i; // 0-9     
	}  
	len =  W25Q32_pageWrite(&dev, 0, 0, wdata, 10);
	if (len != 10) {
		ESP_LOGE(TAG, "pageWrite fail");
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "Page Write(Sector=0 Address=0) len=%d", len);

	// Fast read 256 byte data from Address=0
	memset(rbuf, 0, 256);
	len =  W25Q32_fastread(&dev, 0, rbuf, 256);
	if (len != 256) {
		ESP_LOGE(TAG, "fastread fail");
		while(1) { vTaskDelay(1); }
	}
	ESP_LOGI(TAG, "Fast Read Data: len=%d", len);
	dump(rbuf, 256);

	ESP_LOGI(TAG, "Success All Test");
}