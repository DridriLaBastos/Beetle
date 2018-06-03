;*****************************************;
;*      COURNAND Adrien - 1/06/2018      *;
;*             GNU GPl v3.0              *;
;*                                       *;
;* This file will  go at the top of  the *;
;* boot-stage-1 program. Its goal is too *;
;* declares   datas  needed  for   being *;
;* multiboot  compliant. The  bootloader *;
;* will  first  load  boot-stage-1 which *;
;* will performes any early cpu          *;
;* initilizations                        *;
;*****************************************;

%define MULTIBOOT_MAGIC 0x1BADB002
%define MULTIBOOT_FLAGS 0
%define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

SECTION .header
multiboot_header:
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

SECTION .text
    _start:
        xchg bx, bx
        mov ah, 0x02
        mov al, "H"
        mov word [0xB8000], ax

        mov al, "e"
        mov word [0xB8002], ax

        mov al, "l"
        mov word [0xB8004], ax

        mov al, "l"
        mov word [0xB8006], ax

        mov al, "o"
        mov word [0xB8008], ax

        mov al, " "
        mov word [0xB800A], ax

        mov al, "W"
        mov word [0xB800C], ax

        mov al, "o"
        mov word [0xB800E], ax

        mov al, "r"
        mov word [0xB8010], ax

        mov al, "l"
        mov word [0xB8012], ax

        mov al, "d"
        mov word [0xB8014], ax

        cli
        hlt