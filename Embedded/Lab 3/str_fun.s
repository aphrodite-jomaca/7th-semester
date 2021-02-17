.text
.align  4

.global strlen
.type   strlen,%function

.global strcpy
.type   strcpy,%function


.global strcmp
.type   strcmp,%function

.global strcat
.type   strccat,%function


strlen:
    push	{r1-r7, lr}
    mov  r1,r0
    mov  r0,#0
loop:    
    ldrb r2,[r1], #1
    cmp  r2,#0x00
    addne  r0,r0,#1
    bne  loop
    pop		{r1-r7, pc}
	

strcpy:
        push	{r1-r7, lr}
loop_strcpy:    
        
        ldrb r2,[r1],#1
        strb r2,[r0],#1
        cmp  r2,#0x00
        bne loop_strcpy    
        pop		{r1-r7, pc}


strcmp:
      push	{r1-r7, lr}
       mov r5,r0
       mov r0,#0
       mov r3,#1
loop_strcmp:
       cmp r3,#0
       beq end  
       ldrb r3,[r5],#1
       ldrb r4,[r1],#1
       cmp  r3,r4
       beq   loop_strcmp
       sublt r0,r0,#1
       addgt r0,r0,#1
end:
      pop		{r1-r7, pc}


strcat:
       push	{r1-r7, lr}

loop_strcat:
        ldrb  r4,[r0],#1
        cmp   r4,#0x00
        bne   loop_strcat

        sub   r0,r0,#1
loop_strcat_2:
        ldrb  r3,[r1],#1
        strb  r3,[r0],#1
        cmp   r3,#0x00
        bne   loop_strcat_2

       pop		{r1-r7, pc}
