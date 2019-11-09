#include<arpa/inet.h>
#include<sys/socket.h>
#include<fcntl.h>
char* sock_ntop(const struct sockaddr* sa,socklen_t salen)
{
	char* str=malloc(sizeof(128));
	if(sa->sa_family==AF_INET)
	{
		struct sockaddr_in* sin=(struct sockaddr_in*)sa;
		if(inet_ntop(AF_INET,&sin->sin_addr,str,128)==NULL)
			return NULL;
		return str;
	}
	else if(sa->sa_family==AF_INET6)
	{
		struct sockaddr_in6* sin=(struct sockaddr_in6*)sa;
		if(inet_ntop(AF_INET6,&sin->sin6_addr,str,128)==NULL)
			return NULL;
		return str;		
	}
}

int Read(int fd,void* ptr,int num)
{
	int left_read=num;
	int al_read=0;
	char* vptr=ptr;
	while(left_read>0)
	{
		int n=0;
		if((n=read(fd,vptr,left_read))>=0)
		{
			if(n==0)
				break;
			al_read+=n;
			left_read-=n;
		}
		else if(EINTR==errno&&n<0)
			continue;
		else
			return -1;
	}
	return al_read;
}

int Write(int fd,void* ptr,int num)
{
	int left_write=num;
	int al_write=0;
	char* vptr=ptr;
	while(left_write>0)
	{
		int n=0;
		if((n=write(fd,vptr,left_write)>=0))
		{
			if(n==0)
				break;
			else
			{
				left_write-=n;
				al_write+=n;
			}
		}
		else if(n<0&&errno==EINTR)
			continue;
		else
			return -1;
	}
	return al_write;
}

int readline(int fd,void* ptr,int max_len)
{
	int n=0;
	if(-1!=(n=Read(fd,vptr,max_len)))
	{
		for(int i=0;i<max_len;i++)
		{
			if(vptr[i]=='\n')
			{
				memset(vptr+i+1,0,max_len-i-1);
				return i+1;
			}
		}
		return max_len;
	}
	return -1;
}

