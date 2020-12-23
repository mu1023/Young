#include<Logging.h>
#include<ConsoleAppender.h>
#include<FileAppender.h>
using namespace std;
using namespace Young;
int main() {
	
	std::shared_ptr<FileAppender<std::mutex>> ptr1 = std::make_shared< FileAppender<std::mutex>>(".\\log\\test.log", Timestamp::Now());
	std::shared_ptr<ConsoleAppender<std::mutex>> ptr2 = std::make_shared< ConsoleAppender<std::mutex>>();
	std::shared_ptr<UdpAppender<std::mutex>> ptr3 = std::make_shared<UdpAppender<std::mutex>>("101.101.010.101", 123);
	Logger::Instance()->InsertAppenderPtr(ptr1);
	Logger::Instance()->InsertAppenderPtr(ptr2);
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
	LOGGER_DEBUG("afwrwa{0}", "xxx");
}
