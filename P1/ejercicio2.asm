pixel MACRO X, Y, C
    push ax
    push cx
    push dx
    
    mov ax, Y
    mov cx, X
    mov dx, ax
    mov al, C
    mov ah, 0Ch
    int 10h

    pop dx
    pop cx
    pop ax
ENDM

rectangulo MACRO x, y, w, h

    mov cx, 0
    mov dx, x	
	bucle:
    	pixel dx, y, 3
    	inc dx	
	    inc cx
    	cmp cx, w
	    jne bucle

    mov cx, 0
    mov ax, y	
	bucle1:
    	pixel dx, ax, 3
	    inc ax
    	inc cx
	    cmp cx, h
    	jne bucle1
	
    mov cx, 0
	bucle2:
    	pixel dx, ax, 3
	    dec dx
	    inc cx
	    cmp cx, w
	    jne bucle2

    mov cx, 0
	bucle3:
	    pixel dx, ax, 3
	    dec ax
	    inc cx
	    cmp cx, h
	    jne bucle3

	;; Añadir puntos al rectángulo 
    add dx, 4
    add ax, 3
    pixel dx, ax, 1

    add dx, 4
    add ax, 3
    pixel dx, ax, 2    
ENDM

    pila segment stack 'stack'
        dw 100h dup (?)
    pila ends

    datos segment 'data'
        Cadena db 13,10,'pulsa una tecla...',13,10,'$'
    datos ends

    codigo segment 'code'
        assume cs:codigo, ds:datos, ss:pila
        main PROC
            mov ax, datos
            mov ds, ax

            ;; Modo gráfico 320x200
            mov al, 4
            mov ah, 0
            int 10h


            ;; Pintar pixeles
            rectangulo 50, 50, 100, 50


            ;; Esperar la pulsación de una tecla
            mov ah,8
            int 21h

            ;; Modo 80x25
            mov al, 3
            mov ah, 0
            int 10h


            mov ax, 4C00h
            int 21h

        main ENDP

    codigo ends
    END main
