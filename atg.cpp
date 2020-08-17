/******************************************************************************\
	@Author: 	Anurag J K
	@date:		17AUG2020
	@file 		atg.cpp
\******************************************************************************/
#include "atg.h"

/* Class instance */
atg::atgClass* atg::atgClass::instance = nullptr;
/* Constructor */
atg::atgClass::atgClass(){}

/*******************************************\
	Main initialization class
\*******************************************/
atg::atgClass* atg::atgClass::init(TG_TYPE_E trigger, TG_ACTION_E action)
{
	if(instance == nullptr){
		instance = new atg::atgClass();
	}
	if( trigger == TG_TYPE_TIMER ){
		instance->proxyObj = new atgTimerClass(action);
	}else if( trigger == TG_TYPE_USR_CMD ){
		instance->proxyObj = new atgCmdClass(action);
	}else{
		instance->proxyObj = nullptr;
	}

	return instance;
}

/*******************************************\
	Main start class
\*******************************************/
void atg::atgClass::action_start()
{
	if(proxyObj == nullptr){
		return;
	}
	proxyObj->start();
}

/*******************************************\
	Main exit class
\*******************************************/
void atg::atgClass::exit()
{
	if(proxyObj != nullptr){
//		delete proxyObj;
	}
	if(instance != nullptr){
		delete instance;
	}
}

/*******************************************\
	Base class constructor
\*******************************************/
TG_ACTION_E atg::atgBaseClass::action = TG_ACTION_NONE;
std::string atg::atgBaseClass::trigger = "";
atg::atgBaseClass::atgBaseClass(){}
atg::atgBaseClass::atgBaseClass(TG_ACTION_E action)
{
	this->action = action;
}

/*******************************************\
	Base class logging function
\*******************************************/
void atg::atgBaseClass::logger( std::string msg )
{
	std::ofstream fout;

	if( this->action == TG_ACTION_CONSOLE ){
		std::cout<< "[" << this->trigger <<"]";
		std::cout<< msg << std::endl;
	}else if( this->action == TG_ACTION_FILE ){
		fout.open( LOG_FILE_NAME, std::ios::app );
		fout << "[" << this->trigger <<"]";
		fout << msg << std::endl;
		fout.close();
	}
}

/*******************************************\
	Timer class constructor
\*******************************************/
atg::atgTimerClass::atgTimerClass(TG_ACTION_E action) : atg::atgBaseClass::atgBaseClass(action)
{
	this->trigger = "Timer";
}

/*******************************************\
	Cmd class Constructor
\*******************************************/
atg::atgCmdClass::atgCmdClass(TG_ACTION_E action) : atg::atgBaseClass::atgBaseClass(action)
{
	this->trigger = "User cmd";
}

/*******************************************\
	Timer class timer callback function
\*******************************************/
void atg::atgTimerClass::timed(Poco::Timer& timer)
{
	static int count;

	logger( "Message: " + std::to_string(count++) );
}

/*******************************************\
	Timer class entry point
\*******************************************/
void atg::atgTimerClass::start()
{
	logger( "Starting timer for " + std::to_string(TIMER_CALLBACK_END_TIME)+ "ms " +
			"with intervel of " + std::to_string(TIMER_CALLBACK_INTERVEL) + "ms" );
	Poco::Timer timer(TIMER_CALLBACK_START_TIME, TIMER_CALLBACK_INTERVEL);
	timer.start(Poco::TimerCallback<atgTimerClass>(*this, &atgTimerClass::timed));
	Poco::Thread::sleep(TIMER_CALLBACK_END_TIME);
	timer.stop();
}

/*******************************************\
	Cmd class entry point
\*******************************************/
void atg::atgCmdClass::start()
{
	Poco::Thread thread;

	thread.start(this);
	thread.join();
}

/*******************************************\
	Cmd class thread function
\*******************************************/
void atg::atgCmdClass::run()
{
	const std::string dataList[8] = {
		"Pineapple",
		"Mango",
		"Apple",
		"Banana",
		"Cherry",
		"Peach",
		"Plum",
		"Orange"
	};

	cache_init(3);
	for(int i=0;i<8;i++){
		cache_push(dataList[i]);
		Poco::Thread::sleep(200);
	}
	cache_destroy();
}

/*******************************************\
	Cmd class - Cache init size
\*******************************************/
int atg::atgCmdClass::cache_init(unsigned int size)
{
	this->size = size;
	cache.clear();
	logger( "cache initialized with size " + std::to_string(size) );

	return 0;
}

/*******************************************\
	Cmd class - Cache push (to back)
\*******************************************/
int atg::atgCmdClass::cache_push(std::string data)
{
	std::string tmp;

	while( cache.size() >= this->size ){
		tmp = cache_pop();
	}
	cache.push_back( data );
	logger( "Cached: " + data );

	return 0;
}

/*******************************************\
	Cmd class - Cache pop (from front)
\*******************************************/
std::string atg::atgCmdClass::cache_pop()
{
	std::string tmp;

	tmp = cache.front();
	cache.erase( cache.begin() );
	logger( "Cache clear: " + tmp );

	return tmp;
}

/*******************************************\
	Cmd class - Cache clear
\*******************************************/
int atg::atgCmdClass::cache_destroy()
{
	logger( "Cache destroy" );
	for(unsigned int i=0; i<cache.size(); i++){
		cache_pop();
	}

	return 0;
}
