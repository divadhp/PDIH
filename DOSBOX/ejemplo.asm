pila segment stack 'stack'
dw 100h dup (?)
pila ends
datos segment 'data'
datos ends
codigo segment 'code'
assume cs:codigo, ds:datos, ss:pila
main PROC
mov ax,datos
mov ds,ax
; modo de vídeo GRAFICO
mov al, 13h
mov ah,0
int 10h
; inicializar el ratón
mov ax,0001
int 33h
esperar_izq:
mov ax,5
mov bx,0 ; 0=botón_izq
int 33h  ;1=botón_der
cmp bx,0
je esperar_izq
; restaurar modo de vídeo TEXTO
mov al, 3h
mov ah,0
int 10h
; terminar y salir
mov ax,4C00h
int 21h
main ENDP
codigo ends
END main
