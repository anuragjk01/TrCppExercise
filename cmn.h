/******************************************************************************\
	@Author: 	Anurag J K
	@date:		17AUG2020
	@file 		cmn.h
\******************************************************************************/
#ifndef _CMN_H_
#define _CMN_H_

#include <iostream>
#include <cstring>

void cmn_print_usage(char* pgm);
std::string cmn_get_arg_from_tag(int argc, char** argv, const std::string tag);

#endif /*_CMN_H_*/
