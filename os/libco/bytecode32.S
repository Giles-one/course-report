.section .text
switch_stack_call:
    movl  %esp, %ecx
    movl  0(%ecx), %eax
    movl  4(%ecx), %esp
    pushl %ecx
    pushl %eax
    movl 12(%ecx), %eax
    pushl %eax
    movl 8(%ecx), %eax
    call *%eax
    popl %eax
    popl %eax
    popl %esp
    popl %ecx
    jmpl *%eax
    int3
