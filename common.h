char* sock_ntop(const struct sockaddr* sa,socklen_t salen);		/*将ipv4/ipv6 地址结构转换成字符串形式*/

int Read(int fd,void* ptr,int num);		/*读取n个字节*/

int readline(int fd,void* ptr,int max_len);		/*读取一行内容*/

int Write(int fd,void* ptr,int num);		/**/

/*overflow*/