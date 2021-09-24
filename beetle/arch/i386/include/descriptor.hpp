#ifndef __DESCRIPTOR_HPP__
#define __DESCRIPTOR_HPP__

namespace ARCH::I386
{
	//0 = reserved
	constexpr unsigned int TSS_A_16  = 1;//16 bits TSS available
	constexpr unsigned int LDT		 = 2;//LDT
	constexpr unsigned int TSS_B_16  = 3;//16 bits TSS busy
	constexpr unsigned int CG_16	 = 4;//16 bits call gate
	constexpr unsigned int TG		 = 5;//task gate
	constexpr unsigned int IG_16	 = 6;//16 bits interrupt gate
	constexpr unsigned int TG_16	 = 7;//16 bits trap gate
	//8 = reserved
	constexpr unsigned int TSS_A_32  = 9;//32 bits TSS available
	//10 = reserved
	constexpr unsigned int TSS_B_32	 = 11;//32 bits TSS busy
	constexpr unsigned int CG_32	 = 12;//32 bits call gate
	//13 = reserved
	constexpr unsigned int IG_32	 = 14;//32 bits interrupt gate
	constexpr unsigned int TG_32	 = 15;//32 bits trap gate

	constexpr unsigned int PRIVILEGE0 = 0;
	constexpr unsigned int PRIVILEGE1 = 1;
	constexpr unsigned int PRIVILEGE2 = 2;
	constexpr unsigned int PRIVILEGE3 = 3;
}

#endif