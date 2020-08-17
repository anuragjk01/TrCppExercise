/******************************************************************************\
	@Author: 	Anurag J K
	@date:		17AUG2020
	@file 		cmn.cpp
\******************************************************************************/
#include "cmn.h"

void cmn_print_usage(char* pgm)
{
	std::cout<<"USAGE: "<<std::endl;
	std::cout<<pgm<<" -t {timer/usercmd} -a {consol/file}"<<std::endl;
}

std::string cmn_get_arg_from_tag(int argc, char** argv, const std::string tag)
{
	int i;
	for( i = 1; i <= argc ; i++)
		if( std::string(argv[i]) == tag )
			break;
	if( i < argc ){
		return std::string(argv[i+1]);
	}else{
		return std::string("");
	}
}
