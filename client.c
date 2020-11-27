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
#define num 1000
int main(int argc,char *argv[]){
	int sock,port=18888,i,j,k,l;
	struct sockaddr_in srv;
	char msg[] = "Hello world!\n";
	char buf[num];

	FILE *fp;
	FILE *fbir;
	char shuzu[num],temp[num];

	fp=fopen("sheet.csv","r+");
	fbir=fopen("sheet.bin","wb+");
	fread(shuzu,sizeof(shuzu),1,fp);

	for(l=0;l<3;l++){
			if(l==0){
				for(i=0,j=0;j<num;j++,i++){
					temp[i]=shuzu[j];			
					if((int)shuzu[j]==0) {
						sock = socket(AF_INET,SOCK_STREAM,0);
						srv.sin_addr.s_addr = inet_addr("127.0.0.1");
						srv.sin_family = AF_INET;
						srv.sin_port = htons(port+l);
	
						connect(sock,(struct sockaddr* )&srv,sizeof(srv));
						send(sock,temp,sizeof(temp),0);
						recv(sock,buf,sizeof(buf),0);

						close(sock);

						break;
						}
					}

				for(i=0,k=0;i<=num;i++){//二进制文件
					fprintf(fbir,"%d",buf[i]);
					if(buf[i]==0) k=k+1;
					else k=0;
					if(k==12) break;
					}
				}
			else{
				for(i=0,j=j+1;j<num;j++,i++){
					temp[i]=shuzu[j];			
					if((int)shuzu[j]==0) {
						sock = socket(AF_INET,SOCK_STREAM,0);
						srv.sin_addr.s_addr = inet_addr("127.0.0.1");
						srv.sin_family = AF_INET;
						srv.sin_port = htons(port+l);
	
						connect(sock,(struct sockaddr* )&srv,sizeof(srv));
						send(sock,temp,sizeof(temp),0);
						recv(sock,buf,sizeof(buf),0);

						close(sock);

						break;
						}
					}

				for(i=0,k=0;i<=num;i++){
					fprintf(fbir,"%d",buf[i]);
					if(buf[i]==0) k=k+1;
					else k=0;
					if(k==12) break;
					}
				}
			
		}
	
	

	return 0;
}