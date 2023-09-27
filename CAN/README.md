# CAN Network Example 

This example demonstrates how to use the CAN(TWAI) driver to program a target (ESP32, ESP32-S2, ESP32-S3 or ESP32-C3) as a TWAI node, and have the two nodes (Network Master and Network Slave) communicate on a TWAI network. 

Note that concept of master/slave in this example refers to which node initiates and stops the transfer of a stream of data messages.

## How to use example

### Hardware Required

This example requires at least two targets (e.g., an ESP32 or ESP32-S3) to act as the Network Master and Network Slave.Each target must be connected to an external transceiver (e.g., a TJA1050 CAN transceiver). The transceivers must then be interconnected to form a TWAI(CAN) network.

The following diagram illustrates an example network:
```
    ----------       ----------    
   |  Master  |     |  Slave   | 
   |          |     |          |
   |  ESP32   |     |  ESP32   |
   |          |     |          |
   | TX    RX |     | TX    RX | 
    ----------       ----------   
     |      |         |      |     
     |      |         |      |           
    ----------       ----------   
   | TX    RX |     | TX    RX | 
   |          |     |          | 
   |  TJA1050 |     |  TJA1050 | 
   |          |     |          |          
   | H      L |     | H      L | 
    ----------       ----------   
     |      |         |      |          
     |      |         |      |         
  |--x------|---------x------|------| H
            |                |            
  |---------x----------------x------| L

```

### Configure the project

For each node in the TWAI network (i.e., Master, Slave)...

- Set the target of the build (where {IDF_TARGET} stands for the target chip such as esp32 or esp32s2).
- Then run menuconfig to configure the example.

```idf.py set-target {IDF_TARGET} ```  

```idf.py menuconfig```

Under Example Configuration, configure the pin assignments using the options TX GPIO Number and RX GPIO Number according to how the target was connected to the transceiver. By default, TX GPIO Number and RX GPIO Number are set to the following values:
On the ESP32, TX GPIO Number and RX GPIO Number default to 21 and 22 respectively
On the ESP32-S3, TX GPIO Number and RX GPIO Number default to 43 and 44 respectively
On other chips, TX GPIO Number and RX GPIO Number default to 0 and 2 respectively

### Build and Flash

For each node, build the project and flash it to the board, then run monitor tool to view serial output:

idf.py -p PORT flash monitor
(Replace PORT with the name of the serial port to use.)

(To exit the serial monitor, type Ctrl-].)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

### Example Output:

#### CAN_Master 

```
I (345) TWAI Master: Driver installed
I (345) TWAI Master: Driver started
I (345) TWAI Master: Transmitting ping
I (3105) TWAI Master: Transmitted start command
I (3105) TWAI Master: Received data value 339
...
I (5545) TWAI Master: Received data value 584
I (5545) TWAI Master: Transmitted stop command
I (5595) TWAI Master: Driver stopped
I (6595) TWAI Master: Driver started
I (6595) TWAI Master: Transmitting ping
I (7095) TWAI Master: Transmitted start command
I (7095) TWAI Master: Received data value 738
...
I (9535) TWAI Master: Received data value 983
I (9535) TWAI Master: Transmitted stop command
I (9585) TWAI Master: Driver stopped
I (10585) TWAI Master: Driver started
I (10585) TWAI Master: Transmitting ping
I (11085) TWAI Master: Transmitted start command
I (11085) TWAI Master: Received data value 1137
...
I (13525) TWAI Master: Received data value 1382
I (13525) TWAI Master: Transmitted stop command
I (13575) TWAI Master: Driver stopped
I (14575) TWAI Master: Driver uninstalled

```
#### CAN_Slave

```
Slave starting in 3
Slave starting in 2
Slave starting in 1
I (6322) TWAI Slave: Driver installed
I (6322) TWAI Slave: Driver started
I (6462) TWAI Slave: Transmitted ping response
I (6712) TWAI Slave: Start transmitting data
I (6712) TWAI Slave: Transmitted data value 339
...
I (9162) TWAI Slave: Transmitted data value 584
I (9212) TWAI Slave: Transmitted stop response
I (9312) TWAI Slave: Driver stopped
I (10312) TWAI Slave: Driver started
I (10452) TWAI Slave: Transmitted ping response
I (10702) TWAI Slave: Start transmitting data
I (10702) TWAI Slave: Transmitted data value 738
...
I (13152) TWAI Slave: Transmitted data value 983
I (13202) TWAI Slave: Transmitted stop response
I (13302) TWAI Slave: Driver stopped
I (14302) TWAI Slave: Driver started
I (14442) TWAI Slave: Transmitted ping response
I (14692) TWAI Slave: Start transmitting data
I (14692) TWAI Slave: Transmitted data value 1137
...
I (17142) TWAI Slave: Transmitted data value 1382
I (17192) TWAI Slave: Transmitted stop response
I (17292) TWAI Slave: Driver stopped
I (18292) TWAI Slave: Driver uninstalled

```