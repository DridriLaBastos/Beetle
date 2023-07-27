//
// Created by Adrien COURNAND on 08/11/2022.
//

extern int main();
extern void _init(void);
extern void _fini(void);

int _start(int argc, const char** argv){
	_init();
	const int ret = main(argc,argv);
	_fini();
	return ret;
}
