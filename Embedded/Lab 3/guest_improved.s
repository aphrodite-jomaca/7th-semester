.text

.global main
.extern tcsetattr
.extern tcflush

main:	
	ldr r0, =serial_port	
	ldr r1, =mode
	ldr r1, [r1]		    
	mov r7, #5		        //Open ttyAMA0 in mode O_RDWR | O_NOCTTY | O_NDELAY
	swi	0

	cmp r0, #0
	blt error_open

	mov r5, r0		        //Open returns file desc in r0
							//and we store it at r5

dev_config:
	mov r1, #0
	ldr r2, =options	    
	bl  tcsetattr

	cmp r0, #0
	blt error_config

flush:
	mov r0, r5
	mov r1, #2
	bl  tcflush

	cmp r0, #0
	blt error_flush
		
	ldr r6,=chars     		//r6 holds the mem pos for the chars table
	mov r8, #0				//r8 for iterator				
	mov r7, #0				//r7 to fill with 0

char_init:					//initialize counter of each char to zero
	strb r7, [r6], #1
	add r8, r8, #1
	cmp r8, #256
	blt char_init

read:
	mov r0, r5
	ldr r1, =in_str
	mov r2, #1
	mov r7, #3
	swi 0					//Read input string from Serial Port	

	cmp r0, #1
	blt read
	mov r4, r0				//Bytes read in r4

//processing
	ldr  r1, =in_str	
	ldrb r3, [r1]

	cmp  r3, #1
	blt  read				//If not a character read again 
	cmp  r3, #32
	beq  read				//Ignore spaces
	cmp  r3, #10
	beq  cont				//If we've reached \n stop reading
	
	ldr  r6, =chars			//Else...
	ldrb r2, [r6, r3]!		//Go to index that corresponds to the ascii value of the input char
	add  r2, r2, #1			
	strb r2, [r6]			//Increase num of occurances
	b    read				//Read next 

cont:
	ldr r9,  =freq			//In r9 we'll store num of occurances
	ldr r10, =char			//and in r10 the most frequent char

	ldr r6, =chars	
	mov r8, #0				//r8 for iterator

find_max:
	ldrb r2, [r6], #1
	ldrb r4, [r9]
	cmp  r2, r4
	ble  tyn				//If smaller than max look for the next one
	strb r2, [r9]			//Else update max
	strb r8, [r10] 			//Update most frequent char
tyn:
    add  r8, r8, #1
	cmp  r8, #256
	blt  find_max

write_mfchar:	
	mov r0, r5			
	ldr r1,	=char 		
	mov r2, #1
	mov r7, #4
	swi 0					//Write most frequent char

	cmp r0, #0
	ble write_mfchar		//Error checking

write_freq:
	mov r0, r5		
	ldr r1, =freq
	mov r2, #1
	mov r7, #4
	swi 0					//Write num of occurances			

	cmp r0, #0
	ble write_freq			//Error checking

close:
	mov r0, r5
	mov r7, #6
	swi 0 					//Close opened serial port

exit:
	mov r0, #0		
	mov r7, #1
	swi 0					//Exit

error_open:
	mov r0, #1
	ldr r1, =error_msg
	ldr r2, =len
	mov r7, #4
	swi 0
	b exit

error_config:
	mov r0, #1
	ldr r1, =error_msg2
	ldr r2, =len2
	mov r7, #4
	swi 0
	b exit

error_flush:
	mov r0, #1
	ldr r1, =error_msg3
	ldr r2, =len3
	mov r7, #4
	swi 0
	b exit


.data
	serial_port		:	.ascii "/dev/ttyAMA0\000"
	chars			:	.skip 256
	in_str			:	.ascii "\0\0"
	freq			:	.ascii "\0"
	char			:	.ascii "\0"
	mode			: 	.word 0x00000902
	options			:	.word 0x00000000	/* c_iflag */
						.word 0x00000000	/* c_oflag */
						.word 0x000008bd	/* c_cflag - Control options*/
						//Perfoming AND operation between the following flags we get 0x08bd in hex.
						//Baud = B9600                     	-> 0000015
						//8 bits data = CS8                 -> 0000060 
						//CREAD = Enable receiver           -> 0000200
						//CLOCAL = Ignore modem status lines-> 0004000
						/*The c_cflag member contains two options that should always be enabled, CLOCAL and CREAD.
						These will ensure that your program does not become the 'owner' of the port subject to sporatic job control and hangup signals, 
						and also that the serial interface driver will read incoming data bytes.*/
						.word 0x00000000	/* c_lflag */
						.byte 0x00		    /* c_line */
						.word 0x00000000	/* c_cc[0-3] */
						.word 0x00010000	/* c_cc[4-7] */
						//From termios.h -> byte 6 is for VMIN (little endian)
						//VMIN: Minimum number of characters to read
						.word 0x00000000	/* c_cc[8-11] */
						.word 0x00000000	/* c_cc[12-15] */
						.word 0x00000000	/* c_cc[16-19] */
						.word 0x00000000	/* c_cc[20-23] */
						.word 0x00000000	/* c_cc[24-27] */
						.word 0x00000000	/* c_cc[28-31] */
						.byte 0x00		    /* padding 	*/
						.hword 0x0000		/* padding 	*/
						.word 0x0000000		/* c_ispeed */
						.word 0x0000000		/* c_ospeed */
	error_msg: .ascii "Error: Could not open device.\n"
	len= .-error_msg
	error_msg2: .ascii "Error: Could not configure device.\n"
	len2= .-error_msg2
	error_msg3: .ascii "Error: Could not flush device.\n"
	len3= .-error_msg3
.end
