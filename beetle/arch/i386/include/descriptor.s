%ifndef __DESCRIPTOR_H__
%define __DESCRIPTOR_H__

;All the types for code and data descriptors : 16 type from 0x0 to 0xF with the flag S set to 1
%define DATA_READ_ONLY							0x10 ;Data read only
%define DATA_READ_ONLY_ACCESSED					0x11 ;Data read only accessed
%define DATA_READ_WRITE							0x12 ;Data read/write
%define DATA_READ_ONLY_ACCESSED					0x13 ;Data read/write accessed
%define DATA_READ_ONLY_EXPAND_DOWN				0x14 ;Data read only expand down
%define DATA_READ_ONLY_EXPAND_DOWN_ACCESSED		0x15 ;Data read only expand down accessed
%define DATA_READ_WRITE_ACCESSED				0x16 ;Data read write expand down
%define DATA_READ_WRITE_EXPAND_DOWN_ACCESSED	0x17 ;Data read write expand down accessed

%define CODE_EXECUTE_ONLY						0x18 ;Code execute only
%define CODE_EXECUTE_ONLY_ACCESSED				0x19 ;Code execute only accessed
%define CODE_EXECUTE_READ						0x1A ;Code execute read
%define CODE_EXECUTE_READ_ACCESSED				0x1B ;Code execute read accessed
%define CODE_EXECUTE_ONLY_CONFORMING			0x1C ;Code execute only conforming
%define CODE_EXECUTE_ONLY_CONFORMING_ACCESSED	0x1D ;Code execute only confirming accessed
%define CODE_EXECUTE_READ_CONFORMING			0x1E ;Code execute read conforming
%define CODE_EXECUTE_READ_CONFORMING_ACCESSED	0x1F ;Code execute read conforming accessed

;0 = reserved
%define TSS_A_16  1 ;16 bits TSS available
%define LDT		  2;LDT
%define TSS_B_16  3;16 bits TSS busy
%define CG_16	  4;16 bits call gate
%define TG		  5;task gate
%define IG_16	  6;16 bits interrupt gate
%define TG_16	  7;16 bits trap gate
;8 = reserved
%define TSS_A_32  9;32 bits TSS available
;10 = reserved
%define TSS_B_32 11;32 bits TSS busy
%define CG_32	 12 ;32 bits call gate
; 13 = reserved
%define IG_32	 14 ;32 bits interrupt gate
%define TG_32	 15 ;32 bits trap gate

%define PRIVILEDGE0 0
%define PRIVILEDGE1 1
%define PRIVILEDGE2 2
%define PRIVILEDGE3 3

%define PRESENT (1 << 2)

%define SIZE16 (0 << 2)
%define SIZE32 (1 << 2)

%define GRANULARITY_BYTE (0 << 3)
%define GRANNULARITY_4K  (1 << 3)

%define DESCRIPTOR(BASE,LIMIT,TYPE,ACCESS,OTHER) dw (LIMIT & 0xFFFF), (BASE & 0xFFFF), (((BASE >> 16) & 0xFF) | (((TYPE & 0x1F) | ((ACCESS & 0x7) << 5)) << 8)), ((((LIMIT >> 16) & 0xF) | ((OTHER & 0xF) << 4)) | ((BASE >> 16) & 0xFF00))

%define GATE_DESCRIPTOR(SELECTOR,OFFSET,TYPE,PRESENT,DPL) dw (OFFSET & 0xFFFF), (SELECTOR & 0xFFFF), (((PRESENT & 1) << 15) | ((DPL & 0b11) << 13) | ((TYPE & 0b11111) << 8)), ((OFFSET >> 16) & 0xFFFF)

%define TASK_GATE_DESCRIPTOR(TSS_SEGMENT_SELECTOR,PRESENT,DPL) GATE_DESCRIPTOR(TSS_SEGMENT_SELECTOR,0,TG,PRESENT,DPL)

%define INTERRUPT_GATE_DESCRIPTOR(SEGMENT_SELECTOR,OFFSET,PRESENT,DPL) GATE_DESCRIPTOR(SEGMENT_SELECTOR,OFFSET,IG_32,PRESENT,DPL)

%define TRAP_GATE_DESCRIPTOR(SEGMENT_SELECTOR,OFFSET,PRESENT,DPL) GATE_DESCRIPTOR(SEGMENT_SELECTOR,OFFSET,TG_32,PRESENT,DPL)

%endif