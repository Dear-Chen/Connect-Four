#include "log.h"


log4cplus::Logger logger = log4cplus::Logger::getInstance(L"log");

void initLog()
{
	log4cplus::Logger root = log4cplus::Logger::getRoot();
	log4cplus::PropertyConfigurator::doConfigure(L"log.cfg");
}
