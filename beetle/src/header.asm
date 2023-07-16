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
