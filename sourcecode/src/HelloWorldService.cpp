// HelloWorldService.cpp
#include <iostream>
#include <thread>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include "HelloWorldStubImpl.hpp"
#include <v1/commonapi/HelloWorldProxy.hpp>

using namespace std;
using namespace v1_0::commonapi;

int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<HelloWorldStubImpl> myService =
    std::make_shared<HelloWorldStubImpl>();

    runtime->registerService("local", "test", myService);

    std::cout << "Successfully Registered Service!" << std::endl;

    std::shared_ptr<HelloWorldProxy<>> myProxy =

	runtime->buildProxy<HelloWorldProxy>("local", "test");
	std::cout << "buildProxy returned: " << myProxy << std::endl;
	std::cout << "Checking availability!" << std::endl;
	while (!myProxy->isAvailable())
	{
		usleep(10);
	}
	std::cout << "Available..." << std::endl;

	CommonAPI::CallStatus callStatus;
	std::string returnMessage;
	myProxy->sayHello("Bob", callStatus, returnMessage);
	std::cout << "Got message: '" << returnMessage << "'\n";
	return 0;

 }
