//
// Created by Adrien COURNAND on 08/11/2022.
//

extern int main();
extern void _init(void);
extern void _fini(void);

//TODO: Continue implementing a System V ABI compliant _start function
// https://wiki.osdev.org/Calling_Global_Constructors#Using_crti.o.2C_crtbegin.o.2C_crtend.o.2C_and_crtn.o_in_User-Space
// https://wiki.osdev.org/Creating_a_C_Library

//TODO: Why when I follow the tutorials mentioned in the above comment, I still have an undefined reference to the _init function ?
int _start(int argc, const char** argv){
	// _init();
	const int ret = main(argc,argv);
	// _fini();
	return ret;
}
