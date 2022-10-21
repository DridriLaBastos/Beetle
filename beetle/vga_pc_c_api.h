//
// Created by Adrien COURNAND on 21/10/2022.
//

#ifndef BEETLEOS_VGA_PC_C_API_HPP
#define BEETLEOS_VGA_PC_C_API_HPP

#ifdef __cplusplus
extern "C" {
#endif

	void vga_pc_c_puts(const char* str);
	void vga_pc_c_putc(const int c);

#ifdef __cplusplus
};
#endif

#endif //BEETLEOS_VGA_PC_C_API_HPP
