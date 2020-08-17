/******************************************************************************\
	@Author: 	Anurag J K
	@date:		17AUG2020
	@file 		p.cpp

	@description:
	*	Use below command for compiling
		g++ -I. -Wall <inputs> -lPocoFoundation -lPocoUtil
	*	Make sure Poco library is installed in default lib location
		or lib and Includes are mentioned in Makefile
	*	Set LD_LIBRARY_PATH if linker failes to locate shared library
		path
\******************************************************************************/
#include <iostream>

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Timer.h"

#include "atg.h"
#include "cmn.h"

int main(int argc, char** argv)
{
	TG_TYPE_E 		triggerType 	= TG_TYPE_NONE;
	TG_ACTION_E		actionType		= TG_ACTION_NONE;
	std::string 	arg;

	if(argc < 5){
		cmn_print_usage(argv[0]);
		return 0;
	}

	arg = cmn_get_arg_from_tag(argc, argv, "-t");
	if( arg == "timer" ){
		triggerType = TG_TYPE_TIMER;
	}else if( arg == "usercmd" ){
		triggerType = TG_TYPE_USR_CMD;
	}

	arg = cmn_get_arg_from_tag(argc, argv, "-a");
	if( arg == "console" ){
		actionType = TG_ACTION_CONSOLE;
	}else if( arg == "file" ){
		actionType = TG_ACTION_FILE;
	}

	if( (triggerType == TG_TYPE_NONE) ||
				(actionType == TG_ACTION_NONE)){
		cmn_print_usage(argv[0]);
		return 0;
	}

	atg::atgClass *atgobj = atg::atgClass::init(triggerType, actionType);
	atgobj->action_start();
	atgobj->exit();

	std::cout << "*END*" << std::endl;

	return 0;
}
