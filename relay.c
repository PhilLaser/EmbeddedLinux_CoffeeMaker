#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>


//Global variables
static int device_file = 0;
static int max_i2c_retries = 5;

//I2C Adress
uint8_t GROVE_ADDRESS = 0x04;

//Protocol Definitions
#define WBUFFER_SIZE 4
static const uint8_t DIGITAL_READ = 1;
static const uint8_t DIGITAL_WRITE = 2;
static const uint8_t ANALOG_READ = 3;
static const uint8_t ANALOG_WRITE = 4;
static const uint8_t PIN_MODE = 5;
static const uint8_t USONIC_READ = 7;

static const uint8_t INPUT = 0;
static const uint8_t OUTPUT = 1;

//Hardware
static const int LED_pin = 4; // Grove LED is connected to digital port D4 on the GrovePi

/**
 * Open the device and set device file
 */
void initDevice()
{
        char filename[11]="/dev/i2c-1";           // enough to hold "/dev/i2c-x"
	int current_retry = 0;
        int i2c_device_file;
        while(current_retry < max_i2c_retries) {
                current_retry += 1; // increase the counter
		// open port for read/write operation
                if((i2c_device_file = open(filename, O_RDWR)) < 0) {
			printf("[failed to open i2c port]\n");
			continue;
		}
		// setting up port options and address of the device
                if(ioctl(i2c_device_file, I2C_SLAVE, GROVE_ADDRESS) < 0) {
			printf("[unable to get bus access to talk to slave]\n");
			continue;
		}
                break; // if it got connected, then exit
	}
        device_file = i2c_device_file;
}

/**
 * writes a block of [WBUFFER_SIZE] bytes to the slave i2c device
 * @param  command    command to send to GrovePi
 * @param  pin_number number
 * @param  opt1       optional argument depending on sensor/actuator/etc
 * @param  opt2       optional argument depending on sensor/actuator/etc
 */
void writeBlock(uint8_t command, uint8_t pin_number, uint8_t opt1, uint8_t opt2)
{
	int output_code = -1;
	int current_retry = 0;
        uint8_t data_block[WBUFFER_SIZE] = {command, pin_number, opt1, opt1};
        // repeat until it writes the data or until it fails sending it
        while(output_code == -1 && current_retry < max_i2c_retries) {
                output_code = i2c_smbus_write_i2c_block_data(device_file, 1, WBUFFER_SIZE, &data_block[0]);
		current_retry += 1;
	}
}

int main(int argc, char* argv[])
{
       	if(argc != 2){
		printf("not enough arguments supplied\n");
		return(1);
	} 
       	
       	initDevice(); // initialize communication w/ GrovePi
        writeBlock(PIN_MODE, LED_pin, OUTPUT,0); // set the LED pin as OUTPUT on the GrovePi
        usleep(1000 * 1000); // wait 1 second

	if(strcmp(argv[1], "on") == 0) {
		printf("[pin %d][Relay ON]\n", LED_pin);
		usleep(1000*1000);
		writeBlock(DIGITAL_WRITE, LED_pin, (uint8_t) 1,0);
		return(0);
	}
	if(strcmp(argv[1], "off") == 0){
		printf("[pin %d][Relay OFF]\n", LED_pin);
		usleep(1000*1000);
		writeBlock(DIGITAL_WRITE, LED_pin, (uint8_t) 0,0);
		return(0);
	}
		
        return 0;
}