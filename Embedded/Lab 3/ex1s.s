.text
.global main

conv_routine:
    push {r5, lr}
    sub  r3, r3, #1
    ldrb r5, [r1,#1]!       //load a byte for conversion
    cmp r5, #0x30
    blt end_conv            //if < 0 ignore
    cmp r5, #0x35           
    addlt r5, r5, #5        //'0-4'--> +5
    blt end_conv
    cmp r5, #0x39
    suble r5, r5, #5        //'5-9'--> -5
    ble end_conv
    cmp r5, #0x41
    blt end_conv            //if < A ignore
    cmp r5, #0x5A
    addle r5, r5, #32       //'A-Z'-->'a-z'
    ble end_conv
    cmp r5, #0x61
    blt end_conv            //if < a ignore
    cmp r5, #0x7A
    suble r5, r5, #32       //'a-z'-->'A-Z'
end_conv:
    strb r5, [r1]
    cmp r3, #0
    bne conv_routine
    pop {r5, pc}

main:
    mov r0, #0              //r0 holds the ascii val for null ptr
    mov r2, #100
    ldr r1, =input_str
    sub r1, r1, #1          //offset for the 1st iteration
cleaning:
    strb r0,[r1,#1]!        //fill with nulls
    sub r2, r2, #1
    cmp r2, #0
    bne cleaning

    mov r0, #1              //stdout
    ldr r1, =intro          //input message
    ldr r2, =leni           //num of bytes of input message
    mov r7, #4              //write sys call (4)
    swi 0

reading:
    mov r0, #0              //stdin
    ldr r1, =input_str      //input string
    mov r2, #100            //num of bytes to be read
    mov r7, #3              //read sys call (3)
    swi 0

    mov r3, r0              //num of bytes read stored in r3
    mov r4, r0

    cmp r3, #2
    beq checkforq
cont:
    sub r1, r1, #1          //for the 1st iteration
    add r3, #1

    bl conv_routine
    
printing:
    mov r0, #1
    ldr r1, =input_str
    mov r2, #32
    mov r7, #4
    swi 0

    cmp r4, #33
    blt main
    mov r0, #1
    ldr r1, =bckn
    mov r2, #1
    mov r7, #4
    swi 0
    b main

checkforq:
    ldrb r0, [r1]           //read the first byte in mem addr pointed by r1
    cmp r0,#0x71
    beq end                 //check if first char is 'q' (ascii code: 0x71)
    cmp r0,#0x51
    beq end                 //check if first char is 'Q' (ascii code: 0x51)
    b cont

end:
    mov r0, #1              //stdout
    ldr r1, =outro          //exiting message
    ldr r2, =leno           //num of bytes of input message
    mov r7, #4              //write sys call (4)
    swi 0

    mov r0, #0
    mov r7, #1
    swi 0                   //exit sys call(1)


.data
    intro: .ascii "Please, input a string of up to 32 chars long: "
leni = . - intro        //length of output_string is the current memory indicated by (.) 
                        //minus the memory location of the first element of string
    outro: .ascii "Exiting...\n"
leno = . - outro
    bckn: .ascii "\n"
    input_str: .ascii "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\n"
