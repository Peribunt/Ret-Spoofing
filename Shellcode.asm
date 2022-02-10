.code

InitSpoofCall PROC
mov rsi, rcx
mov rdi, rdx
ret
InitSpoofCall ENDP

SpoofCall PROC
mov rbx, qword ptr[ rsp ]
mov qword ptr[ rsp ], rdi
jmp rsi
SpoofCall ENDP

END
