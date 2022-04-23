
To test the working of the Disk On File(DOF) Block Device Driver. Follow the steps given below:

1) $make 
(creates the object file main.ko)

2) $sudo insmod main.ko 
(inserts the kernel object file created in step 1) 

3) $ls /dev
This command will list all the device files in the dev directory. Check if the disk file-dof and partitions dof1 and dof2 are created succesfully or not

4) $lsmod
Check if the block_driver module is present in the kernel


5) $sudo chmod 777 /dev/dof  
   $sudo chmod 777 /dev/dof1  
   $sudo chmod 777 /dev/dof2
Change the permission of the disk file and its partitions so that we can access thes files and perform operaions on these files.

6) $lsblk 
Displays the disk file and its partitions, their size and type. Here the size of the dof file can be checked whether it is 512KB or not 

7) $dmesg
view the kernel log and see the comments 

8) $ fdisk -l /dev/dof
Additionally this cmmand can be used to see the partitions and ther starting and ending sectors, number of blocks and ID. 

9) sudo cat > /dev/dof1 
After this command type whatever you want and then press ctrl+C. This will write this sentence on dof1
example : "Hello USER . First partition "

10) sudo cat > /dev/dof2 
After this command type whatever you want and then press ctrl+C. This will write this sentence on dof1
example : "Hello USER . Second partition "

11)sudo dd if=/dev/dof1 of=part_1.txt and sudo dd if=/dev/dof2 of=part_2.txt
can be used to print the data on dof1 and dof2 respectively. This data includes the above written statments in the file.

The successful outputs from steps 1 to 11 will show the execution block device driver.
