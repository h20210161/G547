#include "char_dev_adc.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/ioctl.h>

/* ioctl_set_channel is the wrapper function that calls the IOCTL_SET_CHANNEL system call. It will set the channel.
   
   ioctl_set_alignment is the wrapper function that calls the IOCTL_SET_ALIGNMENT system call. It will set the alignment of the data.
   
   ioctl_set_mode is the wrapper function that calls the IOCTL_SET_MODE system call. It will set the mode of conversion i.e. either one shot conversion or continuous conversion mode.
   
   
   
   
   
   
 */

int ioctl_set_channel(int file_desc, int channel)
{
	int ret_val;
	ret_val=ioctl(file_desc, IOCTL_SET_CHANNEL, channel);
	if(ret_val <0)
	{
		printf("\nIOCTL setting channel failed: %d",ret_val);
		exit(-1);
	}
	return 0;
}

int ioctl_set_alignment(int file_desc, int alignment)
{
	int ret_val;
	ret_val=ioctl(file_desc, IOCTL_SET_ALIGNMENT, alignment);
	if(ret_val <0)
	{
		printf("\nIOCTL setting alignment failed: %d",ret_val);
		exit(-1);
	}
	return 0;
}

int ioctl_set_mode(int file_desc, int mode)
{
	int ret_val;
	ret_val=ioctl(file_desc, IOCTL_SET_MODE, mode);
	if(ret_val <0)
	{
		printf("\nIOCTL setting mode failed: %d",ret_val);
		exit(-1);
	}
	return 0;
}


int ioctl_read(int file_desc, uint16_t m)
{
	int ret_val;
	ret_val=ioctl(file_desc, IOCTL_READ, m);
	printf("Data output :  %x\n",m);
	if(ret_val <0)
	{
		printf("\nIOCTL setting mode failed: %d",ret_val);
		exit(-1);
	}
	return 0;
}

	


int main()
{
	int file_desc, ret_val;
	int channel, alignment ,mode;
	int m;
	 
	file_desc = open(DEVICE_FILE_NAME, 1);
	if(file_desc <0)
	{
		printf("\nCan't open the device file: %s",DEVICE_FILE_NAME);
		exit(-1);
	}
	printf("\nEnter the required channel from 0 to 8    ");
	scanf("%d",&channel);
	ioctl_set_channel(file_desc,channel);
	
	printf("\nEnter the required alignment");
	printf("\nEnter 0 for left alignment and 1 for right alignment   ");
	scanf("%d",&alignment);
	ioctl_set_alignment(file_desc,alignment);
	
	
	
	printf("\nEnter the required mode of conversion");
	printf("\nEnter 0 for one shot conversion and 1 for continuous conversion   ");
	scanf("%d",&mode);
	ioctl_set_mode(file_desc,mode);
	printf("\nThe data coverted by ADC will be seen in kernel log if the selected mode of conversion is ONE SHOT CONVERSION \n  ");
	
	ioctl_read(file_desc,m);
	
	close(file_desc);
	return 0;
}
	


	
