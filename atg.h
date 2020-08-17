/******************************************************************************\
	@Author: 	Anurag J K
	@date:		17AUG2020
	@file 		atg.h
\******************************************************************************/
#ifndef _ATG_H_
#define _ATG_H_

#include <iostream>
#include <fstream>
#include <vector>

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Timer.h"

#define TIMER_CALLBACK_INTERVEL			(10000U)	/*ms*/
#define TIMER_CALLBACK_START_TIME		(0U)		/*ms*/
#define TIMER_CALLBACK_END_TIME			(60000U)	/*ms*/

#define USER_UPDATE_INTERVEL			(10000U)	/*ms*/

#define CACHE_SIZE						(5U)

#define LOG_FILE_NAME					"logfile"

typedef enum{
	TG_TYPE_NONE,
	TG_TYPE_TIMER,
	TG_TYPE_USR_CMD,
}TG_TYPE_E;

typedef enum{
	TG_ACTION_NONE,
	TG_ACTION_CONSOLE,
	TG_ACTION_FILE,
}TG_ACTION_E;

namespace atg
{
	class atgBaseClass
	{
	private:
	public:
		static TG_ACTION_E 			action;
		static std::string 			trigger;

							atgBaseClass();
							atgBaseClass(TG_ACTION_E action);
		virtual void 		start() = 0;
		void 				logger( std::string msg );

	};

	class atgTimerClass : public atgBaseClass
	{
	private:
	public:
						atgTimerClass(TG_ACTION_E action);
		void 			start();
		void 			timed(Poco::Timer& timer);
	};

	class atgCmdClass : public atgBaseClass , public Poco::Runnable
	{
	private:
		std::vector<std::string> 	cache;
		unsigned int 				size;

		int 			cache_init(unsigned int size);
		int 			cache_push( std::string data );
		std::string 	cache_pop();
		int 			cache_destroy();

	public:
						atgCmdClass(TG_ACTION_E action);
		void 			start();
		virtual void 	run();
	};

	class atgClass
	{
	protected:
		static atgClass 			*instance;
		atgBaseClass 				*proxyObj;

		atgClass();

	public:
		static atgClass* 	init(TG_TYPE_E trigger, TG_ACTION_E action);
		void 				action_start();
		void 				exit();
	};

}


#endif /*_ATG_H_*/
