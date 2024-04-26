.section .text
switch_stack_call: # (sp /*rdi*/, entry /*rsi*/, arg /*rdx*/)
	popq  %rax
	movq  %rsp, %rcx
	movq  %rdi, %rsp
	pushq %rcx
	pushq %rax
	movq  %rdx, %rdi
	callq *%rsi
	popq  %rax
	popq  %rsp
	jmpq  *%rax
	int3	
	
