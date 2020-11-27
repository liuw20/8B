#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define num 2000

char *handle(char* buf);
int main(int argc,char *argv[]){
	int srv_sock,clt_sock,c,read_size;
	struct sockaddr_in srv,clt;
	char buf[num],*buf_finish;

	pid_t pid;
	int flag=0,i;
	
	while(flag<=2){
		pid=fork();//创建进程
		if(pid<0){
			printf("error in fork");	
			}
		flag++;
		if(pid==0) break;
		
	}

	if(pid>0){//父进程
		srv_sock = socket(AF_INET,SOCK_STREAM,0);
	
		srv.sin_family = AF_INET;
		srv.sin_addr.s_addr = INADDR_ANY;
		srv.sin_port=htons(18888);

		bind(srv_sock,(struct sockaddr*)&srv,sizeof(srv));
		listen(srv_sock,3);

		c=sizeof(struct sockaddr_in);
		clt_sock = accept(srv_sock,(struct sockaddr*)&clt,(socklen_t*)&c);

		while(1){
			read_size=recv(clt_sock,buf,sizeof(buf),0);
			if(read_size==0){
				puts("Client disconnected");
				break;
			}
			else if(read_size == -1){
				perror("recv failed");
				break;
			}
			handle(buf);
			printf("Recved1 has finish\n");
			send(clt_sock,buf,read_size,0);
			break;
		}
		close(clt_sock);close(srv_sock);
		}

	if(flag==1){
		srv_sock = socket(AF_INET,SOCK_STREAM,0);
	
		srv.sin_family = AF_INET;
		srv.sin_addr.s_addr = INADDR_ANY;
		srv.sin_port=htons(18889);

		bind(srv_sock,(struct sockaddr*)&srv,sizeof(srv));
		listen(srv_sock,3);
	
		c=sizeof(struct sockaddr_in);
		clt_sock = accept(srv_sock,(struct sockaddr*)&clt,(socklen_t*)&c);
	
		while(1){
			read_size=recv(clt_sock,buf,sizeof(buf),0);
			if(read_size==0){
				puts("Client disconnected");
				break;
			}
			else if(read_size == -1){
				perror("recv failed");
				break;
			}
			handle(buf);
			printf("Recved2 has finish\n");
			send(clt_sock,buf,read_size,0);break;
		}
		close(clt_sock);close(srv_sock);
	}

	if(flag==2){
		srv_sock = socket(AF_INET,SOCK_STREAM,0);
	
		srv.sin_family = AF_INET;
		srv.sin_addr.s_addr = INADDR_ANY;
		srv.sin_port=htons(18890);
	
		bind(srv_sock,(struct sockaddr*)&srv,sizeof(srv));
		listen(srv_sock,3);
	
		c=sizeof(struct sockaddr_in);
		clt_sock = accept(srv_sock,(struct sockaddr*)&clt,(socklen_t*)&c);
	
		while(1){
			read_size=recv(clt_sock,buf,sizeof(buf),0);
			if(read_size==0){
				puts("Client disconnected");
				break;
			}
			else if(read_size == -1){
				perror("recv failed");
				break;
			}
			handle(buf);
			printf("Recved3 has finish\n");
			send(clt_sock,buf,read_size,0);break;
		}
		close(clt_sock);close(srv_sock);
	}

	return 0;
}



char *handle (char* buf){
	int i,k,l,ch;
	char line_temp[num],daduan[8],daduan_temp[num];

	for(i=0;i<num;i++)
		line_temp[i]='!';

	for(k=0;k<num;k++){
		line_temp[k]=buf[k];
		if((int)buf[k]==0) { break;}
	}
	
	for(k=0;k<(num-1) && line_temp[k]!='!';k++){
		ch=line_temp[k];

		for(l=0;l<=7;l++){
			daduan[l]=ch>>l&1;
			buf[k*8+l]=daduan[l];
		}	
	}	
			
	return buf;
}

