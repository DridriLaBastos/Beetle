//
// Created by Adrien COURNAND on 08/11/2022.
//

#ifdef __cplusplus
extern "C"
#else
extern
#endif

int main(int argc, const char** argv);

#ifdef __cplusplus
extern "C"
#endif

int _start(int argc, const char** argv){
	return main(argc, argv);
}