#include <stdio.h>
#include <string.h>
#include <math.h> 

#define n 10
#define t1 "BV17x411w7KC"

char *table="fZodR9XQDSUm21yCkr6zBqiveYah8bt4xsWpHnJE7jL5VG3guMTKNPAwcF";
int list[10]={9,8,1,6,2,4,0,7,3,5};
unsigned int ox_num=177451812;
unsigned long long add_num=100618342136696320;
unsigned long long dev_num;

char* AVtoBV (int AV);
int BVtoAV (char *BV);

int main ()
{
	
	int i;
	char in[15]={0};
	
	while(1)
	{
		printf("请输入AV号或BV号，输入exit退出\n");
		scanf("%s",in);
	
		if (strstr(in,"AV")==in||strstr(in,"av")==in){
			int AV=0;
			for (i=2;i<strlen(in);i++) {
				AV*=10;
				AV+=(int)(in[i]-'0');
			}
			char *bv=AVtoBV (AV);
			//printf("%s\n",bv);
		}
		
		else if (strstr(in,"BV")==in||strstr(in,"bv")==in){
			if(strlen(in)==12) {
				int av=BVtoAV (in+2);
				//printf("%d\n",av);
			} else {
				printf("BV号输入错误\n");
			}
		}
		
		else if (strstr(in,"exit")==in) {
			break;
		} 
		
		else {
			printf("请检查输入格式是否正确\n");
		}
	}
	
	
	return 0;
}

/**
  * @作用	将AV号转换为BV号 
  * @参数	AV：AV号号码 
  * @返回	BV号号码 
  */ 
char* AVtoBV (int AV) {
	int i;
	
	unsigned long long x=AV^ox_num;
	unsigned int y[n]={0};
	char ans[n+1]={0};
	static char bv[n+1]="0";
	x+=add_num;
	//printf("%lld\n",x);
	for (i=0;i<n;i++) {
		dev_num=pow(58,i);
		y[i]=x/dev_num%58;
		//printf("%d\t",y[i]);
		ans[i]=table[y[i]];
	}
	//printf("\n%s",ans);
	for (i=0;i<n;i++) {
		bv[list[i]]=ans[i];
	}
	printf("BV%s\n",bv);
	
	return bv;
}

/**
  * @作用	将BV号转换为AV号 
  * @参数	BV：BV号号码 
  * @返回	AV号号码 
  */ 
int BVtoAV (char *BV) {
	int i;
	int av;
	char ans[n+1]={0};
	unsigned int y[n]={0};
	unsigned long long x=0;
	
	for (i=0;i<n;i++) {
		ans[i]=BV[list[i]];
	}
	//printf("%s\n",ans);
	for (i=0;i<n;i++) {
		if (strchr(table,ans[i])!=NULL) {
			y[i]=(int)(strchr(table,ans[i])-table);
		} else {
			printf("BV号输入错误\n");
			return -1;
		}
		
		//printf("%d\t",y[i]);
		dev_num=pow(58,i);
		x+=y[i]*dev_num;
	}
	//printf("\n%lld\n",x);
	x-=add_num;
	av=x^ox_num;
	printf("AV%d\n",av);
	
	return av;
}
