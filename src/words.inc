; stack manipulations block
native "drop", drop
    add rsp, 8
    jmp next

native "swap", swap
    pop rax
    pop rdx
    push rax
    push rdx
    jmp next

native "dup", dup
    pop rax
    push rax 
    push rax
    jmp next
    
native ".", dot
    pop rdi
    call print_int
    jmp next
    
native ".S", show_stack
    mov rcx, rsp
    mov r9, [stack_base]
    .loop:
        cmp rcx, r9
        jae next
        mov rdi, [rcx]
        push rcx
        call print_int
        mov rdi, 0x20
        call print_char
        pop rcx
        add rcx, 8
        jmp .loop

section .data
    stack_base: dq 0
    
native "init", init
    call setup_trap
    mov qword [state], 0
    mov rstack, rstack_start
    mov pc, interpreter_stub
    mov [stack_base], rsp
    jmp next

; rstack manipulations block
native ">r", to_r
    pop rax
    rpush rax
    jmp next

native "r>", from_r
    rpop rax
    push rax
    jmp next

native "r@", r_fetch
    mov rax, [rstack]
    push rax
    jmp next
; arifmetics block
native "+", plus
    pop rax
    add [rsp], rax
    jmp next

native "*", mul
    pop rax
    pop rdx
    imul rdx
    push rax
    jmp next

native "/", div
    pop rcx
    pop rax
    cqo
    idiv rcx
    push rax
    jmp next

native "%", mod
    pop rcx
    pop rax
    cqo
    idiv rcx
    push rdx
    jmp next

native "-", minus
    pop rax
    sub [rsp], rax
    jmp next
    
; logic block
native "not", not
    pop rax
    test rax, rax
    je .yes
    push 0
    jmp next
    .yes: push 1
    jmp next

native "=", equals
    pop rax
    pop rdx
    cmp rax, rdx
    je .yes
    push 0
    jmp next
    .yes: push 1
    jmp next

native "<", lt
    pop rdx
    pop rax
    cmp rax, rdx
    js .yes 
    push 0 
    jmp next
    .yes: push 1
    jmp next

native "and", and
    pop rax
    and [rsp], rax
    jmp next

native "or", or
    pop rax
    or [rsp], rax
    jmp next

native "land", land
    pop rax
    pop rdx
    test rax, rax
    jz .no
    push rdx
    jmp next
.no:
    push rax
    jmp next

native "lor", lor
    pop rax
    pop rdx
    test rax, rax
    jnz .yes
    push rdx
    jmp next
.yes:
    push rax
    jmp next


native "exit", exit
    rpop pc
    jmp next
; io and string block
native "emit", emit
    pop rdi
    call print_char
    jmp next

native "word", word
    pop rdi
    call read_word
    push rdx
    jmp next

native "count", count
    pop rdi
    call string_length
    push rax
    jmp next 

native "number", number
    pop rdi
    call parse_int
    push rax
    push rdx
    jmp next

native "printc", printc
  pop rdx
  pop rsi
  mov rdi, 1
  mov rax, 1
  syscall
  jmp next

native "prints", prints
    pop rdi
    call print_string
    jmp next


; syscall and service block

native "bye", bye
  mov rax, 60
  syscall

native "syscall", syscall
    pop r9
    pop r8
    pop r10
    pop rdx
    pop rsi
    pop rdi
    pop rax
    syscall
    push rax
    push rdx
    jmp next
    
;memory manipulations
native "find", find
    mov rsi, [last_word]
    mov rax, [state]
    test rax, rax
    jz .loop
    mov rsi, [rsi]
.loop:
    mov rdi, [rsp]
    push rsi
    add rsi, 9
    call string_equals
    pop rsi
    test rax, rax
    jnz .found

    mov rsi, [rsi]
    test rsi, rsi
    jnz .loop
.not_found:
    mov qword [rsp], 0
    jmp next
.found:
    mov [rsp], rsi
    jmp next

native "cfa", cfa
    pop rsi
    add rsi, 9
    .loop:
    mov al, [rsi]
    test al, al
    jz .end
    inc rsi
    jmp .loop

    .end:
    add rsi, 2
    push rsi
    jmp next
    
native "@", fetch
    pop rax
    mov rdx, [rax]
    push rdx
    jmp next
    
native "!", write
    pop r9
    pop r10
    mov [r9], r10
    jmp next
    
native "c!", write_char
    pop r9
    pop rdx
    mov [r9], dl
    jmp next
    
native "c@", fetch_char
    pop rax
    movzx rax, byte [rax]
    push rax
    jmp next    
  ;native calls
%ifdef NATIVE_CALLS

native "ncall", ncall
    pop rax, 
    movq xmm7, rax
    pop rax 
    movq xmm6, rax
    pop rax 
    movq xmm5, rax
    pop rax 
    movq xmm4, rax
    pop rax 
    movq xmm3, rax
    pop rax 
    movq xmm2, rax
    pop rax
    movq xmm1, rax
    pop rax
    movq xmm0, rax
    pop rax
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    add rsp, 8
    call [rsp-8]
    push rax
    push rdx
    movq rcx, xmm0
    push rcx 
    movq rcx, xmm1 
    push rcx 
    jmp next

%endif
  
;service utils
native "docol", docol
    rpush pc
    add w, 8
    mov pc, w
    jmp next

_trap:
    push qword [stack_base]
    push rdx
    mov rax, xt_trap_dispatch
    mov w, rax
    jmp [rax]

native "branch", branch
    mov pc, [pc]
    jmp next

native "0branch", branch0
    pop rax
    test rax, rax
    jnz .skip
    mov pc, [pc]
    jmp next
    .skip:
    add pc, 8
    jmp next

native "lit", lit
    push qword [pc]
    add pc, 8
    jmp next
   
    native "execute", execute
    pop rax
    mov w, rax
    jmp [rax]

native ",", comma
    mov rax, [here]
    pop qword [rax]
    add qword [here], 8
    jmp next

native "c,", char_comma
    mov rax, [here]
    pop rdx
    mov [rax], dl
    add qword[here], 1
    jmp next

native "create", create
    mov rcx, [last_word]
    mov rsi, [here]
    mov [rsi], rcx
    mov [last_word], rsi
    add rsi, 8
    mov byte [rsi], 0
    inc rsi

    pop rdi
    push rsi
    call string_copy
    pop rsi
    push rsi
    mov rdi, rsi
    call string_length
    pop rsi
    add rsi, rax
    inc rsi
    pop rax
    mov [rsi], al
    inc rsi

    mov [here], rsi
    jmp next 
;consts
const inbuf, input_buf

const mem, user_mem

const last_word, last_word

const state, state

const here, [here]
const in_fd, in_fd
const dp, dp
    
colon "trap_dispatch", trap_dispatch
    dq xt_lit, trapword
    dq xt_find, xt_cfa, xt_execute
    dq xt_bye

colon "trap", trap
    dq xt_lit, trapword
    dq xt_prints, xt_lit, 10, xt_emit
    dq xt_exit
    
colon ":", colon
    .restart:
    dq xt_inbuf, xt_word
    branch0 .restart
    dq xt_lit, 0, xt_inbuf, xt_create
    dq xt_lit, 1, xt_state, xt_write
    dq xt_lit, i_docol, xt_comma
    dq xt_exit

colon ";", semicolon, 1
    dq xt_lit, 0, xt_state, xt_write
    dq xt_lit, xt_exit, xt_comma
    dq xt_exit

section .rodata
interpreter_stub:
    dq xt_lit, 0  
    dq xt_interpret_fd
    dq xt_bye

colon "interpret-fd", interpret_fd
    dq xt_lit, in_fd, xt_fetch, xt_to_r
    dq xt_lit, in_fd
    dq xt_write
    .loop:
    dq xt_inbuf, xt_word
    branch0 .end_of_input

    dq xt_inbuf
    dq xt_interpret

    branch .loop

    .end_of_input:
    dq xt_from_r
    dq xt_lit, in_fd, xt_write
    dq xt_exit


colon "interpret", interpret
.start:

    dq xt_dup, xt_find       

    dq xt_dup
    branch0 .number  
    dq xt_cfa

    dq xt_state, xt_fetch
    branch0 .interpreting

    dq xt_dup
    dq xt_lit, 1, xt_minus, xt_fetch_char, xt_not
    branch0 .interpreting

    dq xt_swap, xt_drop
    dq xt_comma
    dq xt_exit

    .interpreting: 
    dq xt_swap, xt_drop
    dq xt_execute
    dq xt_exit

    .number: 
    dq xt_drop, xt_dup
    dq xt_number 
    branch0 .no_word

   
    dq xt_swap, xt_drop
    dq xt_state, xt_fetch  
    branch0 .exit
                            
    dq xt_here, xt_lit, 8, xt_minus, xt_fetch

    dq xt_dup
    dq xt_lit, xt_branch0
    dq xt_equals, xt_not
    branch0 .is_branch

    dq xt_dup
    dq xt_lit, xt_branch
    dq xt_equals, xt_not
    branch0 .is_branch

    dq xt_lit, xt_lit, xt_comma

.is_branch: 
    dq xt_drop
    dq xt_comma
    dq xt_exit

.no_word: 
    dq xt_drop
    dq xt_prints
    dq xt_lit, msg_no_such_word, xt_prints
.exit:
    dq xt_exit
colon "'", tick, 1
	dq xt_inbuf
	dq xt_word
	dq xt_drop
	dq xt_inbuf
	dq xt_find, xt_dup
    branch0 .no_such_word
	dq xt_cfa
    dq xt_state, xt_fetch
    branch0 .interpret
    dq xt_lit, xt_lit
    dq xt_comma
    dq xt_comma
.interpret:
	dq xt_exit
    .no_such_word:
    dq xt_inbuf, xt_prints
    dq xt_lit, msg_no_such_word, xt_prints
    dq xt_exit