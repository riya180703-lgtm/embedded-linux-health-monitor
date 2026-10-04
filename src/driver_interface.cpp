#include "driver_interface.h"

#include<fcntl.h>
#include<unistd.h>

#include<cerrno>
#include<cstring>

std::string DriverInterface::readStatus()
{
	int fd = open("/dev/health_monitor",O_RDONLY);
	
	if(fd < 0){
		return "Driver unavailable:" + std::string(std::strerror(errno));
	}
	char buffer[256] = {};
	ssize_t n = read(fd,buffer, sizeof(buffer) - 1);
	
	close(fd);
	
	if (n<0) {
		return "Driver read failed: " + std::string(std::strerror(errno));
		}
	buffer[n] = '\0';
	return std::string(buffer);
		

}
