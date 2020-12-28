#include<Logging.h>
#include<ConsoleAppender.h>
#include<FileAppender.h>
#include<Reactor.h>
#include<Acceptor.h>
#include<PollDemultiplexer.h>
using namespace std;
using namespace Young;
int main() {
	SOCKET_STARTUP
	auto reactor = std::make_shared<Reactor>(std::make_shared<PollDemultiplexer>());

	SocketFd fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long iMode = 1;
	ioctlsocket(fd, FIONBIO, &iMode);
	sockaddr_in addr;
	memset(&addr, 0, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	if (::bind(fd, (sockaddr *)&addr, sizeof addr) < 0)
	{
		std::cout << WSAGetLastError() << endl;
	}
	if (0 > listen(fd, 5))
	{
		std::cout << WSAGetLastError() << endl;
	}
	EventHandlerPtr b =std::make_shared<Acceptor>(fd, reactor);

	reactor->RegisterHandler(b, reactor->ReadEvent());

	thread th([&] {
		reactor->Run();
	});

	Sleep(1000);
	SocketFd cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(0 > connect(cfd, (sockaddr *)&addr, sizeof addr))
	{
		std::cout << WSAGetLastError() << endl;
	}
	Sleep(1000);
	send(cfd, "aaaa", 4, 0);
	th.join();
	std::shared_ptr<FileAppender<std::mutex>> ptr1 = std::make_shared< FileAppender<std::mutex>>(".\\log\\test.log", Timestamp::Now());
	std::shared_ptr<ConsoleAppender<std::mutex>> ptr2 = std::make_shared< ConsoleAppender<std::mutex>>();
	std::shared_ptr<UdpAppender<std::mutex>> ptr3 = std::make_shared<UdpAppender<std::mutex>>("101.101.010.101", 123);
	Logger::Instance()->InsertAppenderPtr(ptr1);
	Logger::Instance()->InsertAppenderPtr(ptr2);
	Logger::Instance()->InsertAppenderPtr(ptr3);
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

	SOCKET_CLEANUP
}
