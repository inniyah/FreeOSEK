.cpu cortex-m0
.thumb

#~ .thumb_func
#~ .globl ResetISR
#~ ResetISR:
#~     bl main
#~     b hang

.thumb_func
.globl hang
hang:   b .

.thumb_func
.globl GETPC
GETPC:
    mov r0,pc
    bx lr

.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.thumb_func
.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.thumb_func
.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.thumb_func
.globl GET16
GET16:
    ldrh r0,[r0]
    bx lr

.thumb_func
.globl GET8
GET8:
    ldrb r0,[r0]
    bx lr

.thumb_func
.globl PUTGETCLR
PUTGETCLR:
    ldr r2,[r0]
    bic r2,r1
    str r2,[r0]
    bx lr

.thumb_func
.globl PUTGETSET
PUTGETSET:
    ldr r2,[r0]
    orr r2,r1
    str r2,[r0]
    bx lr

.end
