#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/random.h>

#include "char_dev_adc.h"


#define SUCCESS 0


static dev_t number;/*Global variable storing the major and minor number*/
static struct cdev cdev_adc;//character device structure
static struct class *cls;//variable for device class

/*-----------------------------------------------------------------------*/
//definition of system calls

int L,O;//used further for givig data output
uint16_t m;


static int adc_open(struct inode *i, struct file *f)
{
	printk(KERN_ALERT"Opening the file\n");
	return 0;
}
static int adc_close(struct inode *i, struct file *f)
{
	printk(KERN_ALERT"closing the file\n");
	return 0;
}
static ssize_t adc_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_ALERT"ADC data read\n");
	get_random_bytes(&m,2);
	copy_to_user((int16_t*)buf, &m, 2);
	
	
	return 0;
}






long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int adc_channel;
	int adc_alignment;
	int adc_mode;
	
	switch(ioctl_num){
	/*IOCTL_SET_CHANNEL system call will allow selecting one of the channels from 0 to 8
	
	IOCTL_SET_ALIGNMENT systemcall will allow to select if the 12-bits must be left aligned or right aligned
	
	IOCTL_SET_MODE system call allows to select the mode of conversion required by the user. The function can be used to read the converted number. The output of this function will be a 16-bit number
	
	*/
	case IOCTL_SET_CHANNEL:
		adc_channel=(int)ioctl_param;
		printk(KERN_ALERT"\nSelected Channel=%d",adc_channel);
		break;
	case IOCTL_SET_ALIGNMENT:
		adc_alignment=(int)ioctl_param;
	/*******L=1 : Left alignment is selected by the user
	        L=0 : Right aligment is selected by the user*********/
		if(adc_alignment==0)
		{
			printk(KERN_ALERT"\nSelected alignment= LEFT");
			L=1;
		}
		else if(adc_alignment==1)
		{
			printk(KERN_ALERT"\nSelected alignment= RIGHT");
			
			L=0;
		}
		else
		{
			printk(KERN_ALERT"\n ERROR: Please enter a valid number");
		}
			
		break;
	case IOCTL_SET_MODE:
	/*note that the data can be read only if the selected mode of conversion is ONE SHOT CONVERSION*/
		adc_mode=(int)ioctl_param;
		if(adc_mode==0)
		{
			printk(KERN_ALERT"\nSelected mode : ONE SHOT CONVERSION");
			
			O=1;
			
		}
		else if(adc_mode==1)
		{
			printk(KERN_ALERT"\nSelected mode= CONTINUOUS CONVERSION");
			O=0;
		}
		else
		{
			printk(KERN_ALERT"\n Error : Please enter a valid number");
		}
		
		
		break;
		
	case IOCTL_READ:/*note that the data can be read only if the selected mode of conversion is ONE SHOT CONVERSION*/
		m=(int)ioctl_param;
		
		if(O==1)
	        {
			if(L==1)
			{
				
				
				adc_read(file, m,2,0);
				m=(m & 1111111111110000);
				printk(KERN_ALERT"\nm=%x",m);
				
				
			}
			else
			{
				
				
				adc_read(file, m,2,0);
				m=(m & 0000111111111111);
				printk(KERN_ALERT"\nm=%x",m);
				
				
			
			}
		}
			
	}
	return SUCCESS;
}


 
/*---------------------------------------------------------------------*/
//file operation structure
static struct file_operations fops =
{
	.owner= THIS_MODULE,
	.open= adc_open,
	.release= adc_close,
	.unlocked_ioctl= device_ioctl,
	.read= adc_read
	
};
/*------------------------------------------------------------*/

static int mychar_init(void)
{
	
	printk(KERN_INFO"adc-dev registered");
	if (alloc_chrdev_region(&number,1,1,"ADC-DEV")<0)
	{
		return -1;
	}
	printk(KERN_ALERT"<major, minor> : <%d, %d>\n",MAJOR(number), MINOR(number));
	
	
	if((cls = class_create(THIS_MODULE,"chardev")) == NULL)
	{
		unregister_chrdev_region(number,1);
		return -1;
	}
	if(device_create(cls, NULL, number, NULL, "adc-dev") == NULL)
	{
		printk(KERN_ALERT"Device not created!!!!!");
		class_destroy(cls);
		unregister_chrdev_region(number,1);
		return 0;
	}
	
	cdev_init(&cdev_adc, &fops);
	if(cdev_add(&cdev_adc, number, 1) == -1)
	{
		device_destroy(cls, number);
		class_destroy(cls);
		unregister_chrdev_region(number,1);
		return -1;
	}
	return 0;
}
		
static void mychar_exit(void)
{
	cdev_del(&cdev_adc);
	device_destroy(cls, number);
	class_destroy(cls);
	unregister_chrdev_region(number, 1);
	printk(KERN_INFO"adc-dev unregistered\n\n");
}

module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Assignment-1 , Configuration of a virtual ADC");
MODULE_AUTHOR("Urvi Barapatre - 2021H1400161P");

