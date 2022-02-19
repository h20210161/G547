#include<linux/ioctl.h>
#define CHAR_DEV_ADC_H
#define MAJOR_NUM 236//major number of the device to maintain the uniqueness
#define IOCTL_SET_CHANNEL _IOW(MAJOR_NUM, 0, int)
#define IOCTL_SET_ALIGNMENT _IOW(MAJOR_NUM, 1, int)
#define IOCTL_SET_MODE _IOW(MAJOR_NUM, 2, int)
#define IOCTL_READ _IOWR(MAJOR_NUM, 3, int)
#define DEVICE_FILE_NAME "/dev/adc-dev"

