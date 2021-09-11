//password (completed)
//error handling for files that doesnt exist
//multiple messages in single file (completed)
//file deleting 
//better encoding and decoding 
//exeutable file conversion (completed)




#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int no2=300;
int no=-300;

int pass(int item)
{
	no+=9;
	return item+no; 

}
int dpass(int item)
{
	no2-=9;
	return item+no2;
}
void coder(char * filename ,char * str)
{	
	FILE *fp;
	fp=fopen(filename,"a");
	int i=0,item;
	while(str[i]!='\0')
	{
		i++;
	}
	fprintf(fp, "%d\n",i);
	i=0;
	while(str[i]!='\0'){
		if(str[i]==' ')
		{
			fprintf(fp, "%d ",1000 );
			i++;
			continue;
		}
		item=(int)str[i];
		//code here
		item-=34;
		item=pass(item);
		fprintf(fp, "%d ",item);
		i++;
	}
	fprintf(fp,"\n");
	fclose(fp);
}
void decoder(char * filename,int str_len)
{
	FILE *fp;
	fp=fopen(filename,"r");
	fseek(fp,5+str_len*4+str_len,1);
	/*for debugging
	int n1,n2;
	n1=ftell(fp);
	n2=ftell(fp);
	printf("\npostion shifted from %d to %d \n",n1,n2);
	*/

	int i,len,item;
	printf("the decoded message is \n");
	fscanf(fp,"%d",&len);	
	for(i=0;i<len;i++)
	{	
		fscanf(fp,"%d",&item);
		//code here
		if(item==1000)
		{
			printf(" ");
			continue;
		}
		item=dpass(item);
		item+=34;
		printf("%c",item);
	}
}
void main()
{
	
	int choice,flag=1,item,i,pass_len;
	char string[200],filename[20],password[200]="",in_pass[200],setpassword[200],c_item;

		printf("Enter the choice 1.encode 2.decode 3.exit");
		scanf("%d",&choice);
		getchar();
		if(choice==1)
		{

			printf("Enter the message: ");
			//scanf("%s",string);
			fgets(string,100,stdin);
			printf("\nSave file as : ");
			scanf("%s",filename);
			printf("secure it with password  ");
			printf("Enter the password: ");
			scanf("%s",setpassword);
			FILE *fp;
			fp=fopen(filename,"w");
			fprintf(fp,"%d\n",strlen(setpassword));
			i=0;
			while(setpassword[i]!='\0')
			{
					item=(int)setpassword[i];
					//code here
					item-=34;
					item=pass(item);
					fprintf(fp, "%d ",item);
					i++;
			}
			fprintf(fp,"\n");
			fclose(fp);
			coder(filename,string);
		}
		else if(choice==2)
		{
			printf("Enter the file name:  ");
			scanf("%s",filename);
			FILE *fp;
			fp=fopen(filename,"r");
			fscanf(fp,"%d",&pass_len);
			printf("Enter the password");
			scanf("%s",in_pass);
			for(i=0;i<pass_len;i++)
			{	
				fscanf(fp,"%d",&item);
				//code here
				item=dpass(item);
				item+=34;
				c_item=(char)item;
				strcat(password,&c_item);
				
			}
			fclose(fp);
			if(strlen(password)!=0)
			{

				if(strlen(password)==strlen(in_pass))
				{	i=0;
					while(password[i]!='\0')
					{
						if(password[i]==in_pass[i])
						{	i++;

						}
						else
						{
							flag=0;
							printf("password doesnt match");
							break;
						}
					}
				}
				else
				{
							flag=0;
							printf("password doesnt match in length ");
				}
				if(flag==1)
				{
					printf("===============\n            access granted===============\n");
					decoder(filename,strlen(password));
				}
			}
			else
			{
					printf("access granted \n");
					decoder(filename,strlen(password));
			}
		}
		else
			exit(0);

}			

