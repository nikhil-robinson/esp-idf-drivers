#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/spi_master.h>
#include <driver/gpio.h>
#include <esp_log.h>

#include "w25q32.h"

#define TAG "w25q32"

#define _DEBUG_	0

// SPI Stuff
#if CONFIG_SPI2_HOST
#define HOST_ID SPI2_HOST
#elif CONFIG_SPI3_HOST
#define HOST_ID SPI3_HOST
#endif

//static const int SPI_Command_Mode = 0;
//static const int SPI_Data_Mode = 1;
static const int SPI_Frequency = 1000000;

void W25Q32_dump(char *id, int ret, uint8_t *data, int len)
{
	int i;
	printf("[%s] = %d\n",id, ret);
	for(i=0;i<len;i++) {
		printf("%0x ",data[i]);
		if ( (i % 10) == 9) printf("\n");
	}
	printf("\n");
}



void W25Q32_init(W25Q32_t * dev)
{
  ESP_LOGI(TAG, "MISO_GPIO=%d", MISO_GPIO);
  ESP_LOGI(TAG, "MOSI_GPIO=%d", MOSI_GPIO);
  ESP_LOGI(TAG, "SCLK_GPIO=%d", SCLK_GPIO);
  ESP_LOGI(TAG, "CS_GPIO=%d", CS_GPIO);

	esp_err_t ret;

	//gpio_pad_select_gpio( CONFIG_CS_GPIO );
	gpio_reset_pin( CS_GPIO);
	gpio_set_direction( CS_GPIO, GPIO_MODE_OUTPUT );
	gpio_set_level( CS_GPIO, 0 );

	spi_bus_config_t spi_bus_config = {
		.sclk_io_num = SCLK_GPIO,
		.mosi_io_num = MOSI_GPIO,
		.miso_io_num = MISO_GPIO,
		.quadwp_io_num = WP_GPIO,
		.quadhd_io_num = HOLD_GPIO,
	};

	ret = spi_bus_initialize( HOST_ID, &spi_bus_config, SPI_DMA_CH_AUTO );
	if(_DEBUG_)ESP_LOGI(TAG, "spi_bus_initialize=%d",ret);
	assert(ret==ESP_OK);

	spi_device_interface_config_t devcfg;
	memset( &devcfg, 0, sizeof( spi_device_interface_config_t ) );
	devcfg.clock_speed_hz = SPI_Frequency;
	devcfg.spics_io_num = CS_GPIO;
	devcfg.queue_size = 7;
	devcfg.mode = 0;

	spi_device_handle_t handle;
	ret = spi_bus_add_device( HOST_ID, &devcfg, &handle);
	if(_DEBUG_)ESP_LOGI(TAG, "spi_bus_add_device=%d",ret);
	assert(ret==ESP_OK);
	dev->_SPIHandle = handle;
	dev->_4bmode = false;
#if CONFIG_4B_MODE
	ESP_LOGW(TAG, "4-Byte Address Mode");
	dev->_4bmode = true;
#endif
}

// Get status register 1
// reg1(out):Value of status register 1
//
esp_err_t W25Q32_readStatusReg1(W25Q32_t * dev, uint8_t * reg1)
{
	spi_transaction_t SPITransaction;
	uint8_t data[2];
	data[0] = CMD_READ_STATUS_R1;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 2 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if(_DEBUG_)ESP_LOGI(TAG, "W25Q32_readStatusReg1=%x",data[1]);
	*reg1 = data[1];
	return ret;
}

//
// Get status register 2
// reg2(out):Value of status register 2
//
esp_err_t W25Q32_readStatusReg2(W25Q32_t * dev, uint8_t * reg2)
{
	spi_transaction_t SPITransaction;
	uint8_t data[2];
	data[0] = CMD_READ_STATUS_R2;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 2 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if(_DEBUG_)ESP_LOGI(TAG, "W25Q32_readStatusReg2=%x",data[1]);
	*reg2 = data[1];
	return ret;
}

//
// Get Unique ID
// id(out):Unique ID 8 bytes	
//
esp_err_t W25Q32_readUniqueID(W25Q32_t * dev, uint8_t * id)
{
	spi_transaction_t SPITransaction;
	uint8_t data[13];
	data[0] = CMD_READ_UNIQUE_ID;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 13 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if(_DEBUG_)W25Q32_dump("readUniqieID", ret, data, 13);
	memcpy(id, &data[5], 8);
	return ret ;
}

//
// Get JEDEC ID(Manufacture, Memory Type,Capacity)
// d(out):Stores 3 bytes of Manufacture, Memory Type, Capacity
//
esp_err_t W25Q32_readManufacturer(W25Q32_t * dev, uint8_t * id)
{
	spi_transaction_t SPITransaction;
	uint8_t data[4];
	data[0] = CMD_JEDEC_ID;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 4 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if(_DEBUG_)W25Q32_dump("readManufacturer", ret, data, 4);
	memcpy(id, &data[1], 3);
	return ret ;
}

//
// Check during processing such as writing
// Return value: true:processing false:idle
//
bool W25Q32_IsBusy(W25Q32_t * dev)
{
	spi_transaction_t SPITransaction;
	uint8_t data[2];
	data[0] = CMD_READ_STATUS_R1;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 2 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if (ret != ESP_OK) return false;
	if( (data[1] & SR1_BUSY_MASK) != 0) return true;
	return false;
}




//
// Power down 
//
esp_err_t W25Q32_powerDown(W25Q32_t * dev)
{
	spi_transaction_t SPITransaction;
	uint8_t data[1];
	data[0] = CMD_POWER_DOWN;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 1 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	return ret;
}


//
// Write permission setting
//
esp_err_t W25Q32_WriteEnable(W25Q32_t * dev)
{
	spi_transaction_t SPITransaction;
	uint8_t data[1];
	data[0] = CMD_WRITE_ENABLE;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 1 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	return ret;
}



//
// Write-protected setting
//
esp_err_t W25Q32_WriteDisable(W25Q32_t * dev)
{
	spi_transaction_t SPITransaction;
	uint8_t data[1];
	data[0] = CMD_WRITE_DISABLE;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 1 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	return ret;
}

//set QE = 1

esp_err_t W25Q32_quadEnable(W25Q32_t * dev,uint8_t reg1 , uint8_t reg2)
{
	spi_transaction_t SPITransaction;
	uint8_t data[3];

	// Write permission setting
	esp_err_t ret;
	ret = W25Q32_WriteEnable(dev);
	if (ret != ESP_OK) return false;

	data[0] = CMD_WRITE_STATUS_R;
	data[1] = reg1;
	data[2] = reg2 | (1 << 1);  //QE = 1 ; set the 9th bit to 1(2nd bit statusregister 2)

	memset(&SPITransaction , 0, sizeof(spi_transaction_t));
	SPITransaction.length = 3 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = NULL; //this is the write only operation
	ret = spi_device_transmit(dev-> _SPIHandle, &SPITransaction);
	assert(ret== ESP_OK);
	return ret;
}
//
// Read data
// addr(in):Read start address
//          3 Bytes Address Mode : 24 Bits 0x000000 - 0xFFFFFF
//          4 Bytes Address Mode : 32 Bits 0x00000000 - 0xFFFFFFFF
// n(in):Number of read data
//
uint16_t W25Q32_read(W25Q32_t * dev, uint32_t addr, uint8_t *buf, uint16_t n)
{ 
	spi_transaction_t SPITransaction;
	uint8_t *data;
	data = (uint8_t *)malloc(n+5);
	size_t offset;
	if (dev->_4bmode) {
		data[0] = CMD_READ_DATA4B;
		data[1] = (addr>>24) & 0xFF; // A31-A24
		data[2] = (addr>>16) & 0xFF; // A23-A16
		data[3] = (addr>>8) & 0xFF; // A15-A08
		data[4] = addr & 0xFF; // A07-A00
		offset = 5;
	} else {
		data[0] = CMD_READ_DATA;
		data[1] = (addr>>16) & 0xFF; // A23-A16
		data[2] = (addr>>8) & 0xFF; // A15-A08
		data[3] = addr & 0xFF; // A07-A00
		offset = 4;
	}
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = (n+offset) * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	memcpy(buf, &data[offset], n);
	free(data);
	if (ret != ESP_OK) return 0;
	return n;
}

//
// Fast read data
// addr(in):Read start address
//          3 Bytes Address Mode : 24 Bits 0x000000 - 0xFFFFFF
//          4 Bytes Address Mode : 32 Bits 0x00000000 - 0xFFFFFFFF
// n(in):Number of read data
//
uint16_t W25Q32_fastread(W25Q32_t * dev, uint32_t addr, uint8_t *buf, uint16_t n)
{
	spi_transaction_t SPITransaction;
	uint8_t *data;
	data = (uint8_t *)malloc(n+6);
	size_t offset;
	if (dev->_4bmode) {
		data[0] = CMD_FAST_READ4B;
		data[1] = (addr>>24) & 0xFF; // A31-A24
		data[2] = (addr>>16) & 0xFF; // A23-A16
		data[3] = (addr>>8) & 0xFF; // A15-A08
		data[4] = addr & 0xFF; // A07-A00
		data[5] = 0; // Dummy
		offset = 6;
	} else {
		data[0] = CMD_FAST_READ;
		data[1] = (addr>>16) & 0xFF; // A23-A16
		data[2] = (addr>>8) & 0xFF; // A15-A08
		data[3] = addr & 0xFF; // A07-A00
		data[4] = 0; // Dummy
		offset = 5;
	}
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = (n+offset) * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	esp_err_t ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	memcpy(buf, &data[offset], n);
	free(data);
	if (ret != ESP_OK) return 0;
	return n;
}

//fastread quad output data

uint16_t W25Q32_fastReadQuadOutput(W25Q32_t * dev, uint32_t addr, uint8_t *buf, uint16_t n)
{
	spi_transaction_t SPITransaction;
	uint8_t *data;
	data = (uint8_t *)malloc(n+6);
	size_t offset;

	// Write quadenable permission setting ie; QE=1
	esp_err_t ret;
	ret = W25Q32_quadEnable(dev , 0, 0x02);
	if (ret != ESP_OK) return false;
	
	data[0] = CMD_READ_QUAD_OUTPUT;
	data[1] = (addr>>16) & 0xFF; // A23-A16
	data[2] = (addr>>8) & 0xFF; // A15-A08
	data[3] = addr & 0xFF; // A07-A00
	data[4] = 0; // Dummy
	offset = 5;

	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = (n+offset) * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	memcpy(buf, &data[offset], n);
	free(data);
	if (ret != ESP_OK) return 0;
	return n;

}

//
// Erasing data in 4kb space units
// sect_no(in):Sector number(0 - 1023)
// flgwait(in):true:Wait for complete / false:No wait for complete
// Return value: true:success false:fail
//
// Note:
// The data sheet states that erasing usually takes 30ms and up to 400ms.
// The upper 11 bits of the 23 bits of the address correspond to the sector number.
// The lower 12 bits are the intra-sectoral address.

bool W25Q32_eraseSector(W25Q32_t * dev, uint16_t sect_no, bool flgwait)
{
	spi_transaction_t SPITransaction;
	uint8_t data[4];
	uint32_t addr = sect_no;
	addr<<=12;

	// Write permission setting
	esp_err_t ret;
	ret = W25Q32_WriteEnable(dev);
	if (ret != ESP_OK) return false;

	data[0] = CMD_SECTOR_ERASE;
	data[1] = (addr>>16) & 0xff;
	data[2] = (addr>>8) & 0xff;
	data[3] = addr & 0xff;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 4 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if (ret != ESP_OK) return false;

	// Busy check
	while( W25Q32_IsBusy(dev) & flgwait) {
		vTaskDelay(1);
	}
	return true;
}

//
// Erasing data in 64kb space units
// blk_no(in):Block number(0 - 63)
// flgwait(in):true:Wait for complete / false:No wait for complete
// Return value: true:success false:fail
//
// Note:
// The data sheet states that erasing usually takes 150ms and up to 1000ms.
// The upper 7 bits of the 23 bits of the address correspond to the block.
// The lower 16 bits are the address in the block.

bool W25Q32_erase64Block(W25Q32_t * dev, uint16_t blk_no, bool flgwait)
{
	spi_transaction_t SPITransaction;
	uint8_t data[4];
	uint32_t addr = blk_no;
	addr<<=16;

	// Write permission setting
	esp_err_t ret;
	ret = W25Q32_WriteEnable(dev);
	if (ret != ESP_OK) return false;

	data[0] = CMD_BLOCK_ERASE64KB;
	data[1] = (addr>>16) & 0xff;
	data[2] = (addr>>8) & 0xff;
	data[3] = addr & 0xff;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 4 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if (ret != ESP_OK) return false;

	// Busy check
	while( W25Q32_IsBusy(dev) & flgwait) {
		vTaskDelay(1);
	}
	return true;
}

//
// Erasing data in 32kb space units
// blk_no(in):Block number(0 - 127)
// flgwait(in):true:Wait for complete / false:No wait for complete
// Return value: true:success false:fail
//
// Note:
// The data sheet states that erasing usually takes 120ms and up to 800ms.
// The upper 8 bits of the 23 bits of the address correspond to the block.
// The lower 15 bits are the in-block address.

bool W25Q32_erase32Block(W25Q32_t * dev, uint16_t blk_no, bool flgwait)
{
	spi_transaction_t SPITransaction;
	uint8_t data[4];
	uint32_t addr = blk_no;
	addr<<=15;

	// Write permission setting
	esp_err_t ret;
	ret = W25Q32_WriteEnable(dev);
	if (ret != ESP_OK) return false;

	data[0] = CMD_BLOCK_ERASE32KB;
	data[1] = (addr>>16) & 0xff;
	data[2] = (addr>>8) & 0xff;
	data[3] = addr & 0xff;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 4 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if (ret != ESP_OK) return false;

	// Busy check
	while( W25Q32_IsBusy(dev) & flgwait) {
		vTaskDelay(1);
	}
	return true;
}


//
// Erase all data
// flgwait(in):true:Wait for complete / false:No wait for complete
// Return value: true:success false:fail
//
// Note:
// The data sheet states that erasing usually takes 15s and up to 30s.

bool W25Q32_eraseAll(W25Q32_t * dev, bool flgwait)
{
	spi_transaction_t SPITransaction;
	uint8_t data[1];

	// Write permission setting
	esp_err_t ret;
	ret = W25Q32_WriteEnable(dev);
	if (ret != ESP_OK) return false;

	data[0] = CMD_CHIP_ERASE;
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = 1 * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	assert(ret==ESP_OK);
	if (ret != ESP_OK) return false;

	// Busy check
	while( W25Q32_IsBusy(dev) & flgwait) {
		vTaskDelay(1);
	}
	return true;
}

//
// Page write
// sect_no(in):Sector number(0x00 - 0x3FF) 
// inaddr(in):In-sector address(0x00-0x3FFFFF)
// data(in):Write data
// n(in):Number of bytes to write(0～256)
//
int16_t W25Q32_pageWrite(W25Q32_t * dev, uint16_t sect_no, uint16_t inaddr, uint8_t* buf, int16_t n)
{
	if (n > 256) return 0;
	spi_transaction_t SPITransaction;
	uint8_t *data;

	uint32_t addr = sect_no;
	addr<<=12;
	addr += inaddr;

	// Write permission setting
	esp_err_t ret;
	ret = W25Q32_WriteEnable(dev);
	if (ret != ESP_OK) return 0;

	// Busy check
	if (W25Q32_IsBusy(dev)) return 0;  

	data = (unsigned char*)malloc(n+4);
	data[0] = CMD_PAGE_PROGRAM;
	data[1] = (addr>>16) & 0xff;
	data[2] = (addr>>8) & 0xff;
	data[3] = addr & 0xFF;
	memcpy( &data[4], buf, n );
	memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
	SPITransaction.length = (n+4) * 8;
	SPITransaction.tx_buffer = data;
	SPITransaction.rx_buffer = data;
	ret = spi_device_transmit( dev->_SPIHandle, &SPITransaction );
	free(data);
	assert(ret==ESP_OK);
	if (ret != ESP_OK) return 0;

	// Busy check
	while( W25Q32_IsBusy(dev) ) {
		vTaskDelay(1);
	}
	return n;
}
