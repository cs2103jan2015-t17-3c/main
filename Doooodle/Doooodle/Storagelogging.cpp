#include "boost\log\trivial.hpp"
#include "Storage.h"

class Foo{
public:
	void bar(){
    //log a message at INFO level
		BOOST_LOG_TRIVIAL(info) << "going to start processing";
		try{
			//processInput();
			
		}
		catch(std::exception ex){
			//log a message at WARNING level
			BOOST_LOG_TRIVIAL(warning) << "processing error" << ex;
		}
		BOOST_LOG_TRIVIAL(info) << "end of processing";
	}
};