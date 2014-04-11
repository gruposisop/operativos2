/*
 * kernel.c *
 *  Created on: 10/04/2014
 *      Author: maximiliano
 */
#include "kernel.h"


void arrancarSelect()
{

			fd_set master,read_fds;
			int fdmax;
			int i=0;
			FD_ZERO(&master);
			FD_ZERO(&read_fds);
			char * buffer=malloc(2000);
			int sockserverfd,sockclientfd;
			struct sockaddr_in * local = malloc(sizeof(struct sockaddr_in));
			struct sockaddr_in * client = malloc(sizeof(struct sockaddr_in));
			sockserverfd = socket(AF_INET,SOCK_STREAM,0);
			local->sin_addr.s_addr=inet_addr("127.0.0.1");
			local->sin_port=htons(5000);
			local->sin_family=AF_INET;
			bind(sockserverfd,(struct sockaddr*)local,sizeof(struct sockaddr_in));
			printf("bind ok \n");
			listen(sockserverfd,10);
			printf("listen ok \n");
			FD_SET(sockserverfd,&master);
			fdmax = sockserverfd;
			printf("escuchando en puerto: %d\n",ntohs(local->sin_port));
			unsigned int len = sizeof(struct sockaddr);
			struct timeval tv;
			tv.tv_sec=2;
			tv.tv_usec=500000;
			while(1)
			{

				read_fds = master;
				select(fdmax+1,&read_fds,NULL,NULL,&tv);

				for(i=0;i<=fdmax;i++)
				{	if(FD_ISSET(i,&read_fds))
					{	if(i==sockserverfd)//server
						{
							sockclientfd = accept(sockserverfd,(struct sockaddr*)client,&len);
							FD_SET(sockclientfd,&master);
							if(sockclientfd>fdmax){fdmax=sockclientfd;}
							printf("nueva conexion\n");
						}
						else
						{	int bytes = recv(sockclientfd,buffer,2000,MSG_WAITALL);
							if(bytes==0){printf("el cliente cerro la conexion\n");
										FD_CLR(i,&master);										}
							if(bytes<0){printf("error\n");}
							if(bytes>0){printf("el cliente %d envia: %s\n",i,buffer);}

						}




					}

				}





			}
}
