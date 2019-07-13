#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"intal.h"

long max(long a, long b);
void* multiply(void* intal1,int i);
char* computing_multiplier(char* rem,void* intal,int* cnt);

void* intal_create(const char* str)
{
    int i=0,j;
    char *s=(char*)malloc(sizeof(char));
    if(strcmp(str,"0")==0 || !str)
    {
        strcpy(s,"0");
    }
    else
    {
        while(str[i]=='0')
                i++;
        int size=strlen(str)-i;
        s=(char*)malloc(sizeof(char)*size);
   
        for(j=0;j<size;j++)
        {
            if(isdigit(str[i+j]))
                s[j]=str[i+j];
        }

        if(!strcmp(s,"\0"))
            strcpy(s,"0");
    }
    return s;
}


void intal_destroy(void* intal){

	free(intal);
	
}

char* intal2str(void* intal)
{
  if(intal==NULL)
   {
     char *null=(char *)malloc(4*sizeof(char));
     null[0]='N';
     null[1]='a';
     null[2]='N';
     null[3]='\0';
     return null;
   }

  return (char*)intal_create((char*)intal);
}

void* intal_increment(void* intal){
	char *one=(char*)malloc(sizeof(char));
	one[0] = '1';
	return intal_add(intal,one);
}

void* intal_decrement(void* intal){
	
	long size=0;
	char *temp,*one;
	size = strlen(intal);
	temp = (char*)malloc(sizeof(char)*(size));
	temp = intal;
	one = (char*)malloc(sizeof(char));
	one[0] = '1';
	
	if(size == 1 && temp[0] == '0'){
		return temp;
	}
	temp = intal_diff(temp , one);
	return intal_create(temp); 
}

void* intal_add(void* intal1, void* intal2){
	
	if(intal1==NULL && intal2==NULL)
		return NULL;
	if(intal1==NULL)
		return intal2;
	if(intal2==NULL)
		return intal1;
		
	long size1=0,size2=0,size3=0,i=0;
	char *temp1,*temp2,*temp3;
	int carry = 0,sum = 0;
	size1 = strlen(intal1);
	size2 = strlen(intal2);
	size3 = max(size1,size2);
	temp1 = (char*)malloc(sizeof(char)*(size1));
	temp2 = (char*)malloc(sizeof(char)*(size2));
	temp3 = (char*)malloc(sizeof(char)*(size3 + 1));
	temp1 = intal1;
	temp2 = intal2;
	size1--;size2--;
	
	while(size1 != -1 && size2 != -1){
		sum = (temp1[size1] - '0') + (temp2[size2] - '0') + carry;
		carry = sum/10;
		temp3[size3] = (sum % 10) + '0';
		size1--;size2--;size3--;
	}
	if(size1 == -1){
		while(size2 != -1){
			sum = (temp2[size2] - '0') + carry;
			carry = sum/10;
			temp3[size3] = (sum % 10) + '0';
			size2--;size3--;		
		}
		temp3[0] = carry +'0';
	}
	if(size2 == -1){
		while(size1 != -1){
			sum = (temp1[size1] - '0') + carry;
			carry = sum/10;
			temp3[size3] = (sum % 10) + '0';
			size1--;size3--;		
		}
		temp3[0] = carry +'0';
	}
	
	return intal_create(temp3);
}

void* intal_diff(void* intal1, void* intal2){
	
	if(intal1==NULL && intal2==NULL)
		return NULL;
	if(intal1==NULL)
		return intal2;
	if(intal2==NULL)
		return intal1;
		
	long size1=0,size2=0,size3=0;
	char *temp1,*temp2,*temp3;
	int carry = 0,diff = 0;
	size1 = strlen(intal1);
	size2 = strlen(intal2);
	size3 = max(size1,size2);
	temp1 = (char*)malloc(sizeof(char)*(size1));
	temp2 = (char*)malloc(sizeof(char)*(size2));
	temp3 = (char*)malloc(sizeof(char)*(size3));
	temp1 = intal1;
	temp2 = intal2;
	size1--;size2--;size3--;
	
	if(intal_compare(intal1 , intal2) == 1){
		while(size2 != -1){
			if((temp1[size1] - carry) > temp2[size2]){
				diff = (temp1[size1] - '0') - (temp2[size2] - '0') - carry;
				carry = 0;
			}
			if((temp1[size1] - carry) < temp2[size2]){
				diff = (temp1[size1] - '0') - (temp2[size2] - '0') + 10 - carry;
				carry = 1;
			}
			if((temp1[size1] - carry) == temp2[size2]){
				diff = 0;
				carry = 0;
			}
			temp3[size3] = diff + '0';
			size1--;size2--;size3--;
		}
		if(size1 != -1){
			while(size1 != -1 && temp1[size1] == '0' && carry == 1){
				temp3[size3] = '9';
				size1--;size3--;
			}
			temp3[size3--] = temp1[size1--] - carry;
			while(size1 != -1){
				temp3[size3--] = temp1[size1--];
			}
		}
					
	}
	else if(intal_compare(intal1 , intal2) == -1){
		while(size1 != -1){
			if((temp2[size2] - carry) > temp1[size1]){
				diff = (temp2[size2] - '0') - (temp1[size1] - '0') - carry;
				carry = 0;
			}
			if((temp2[size2] - carry) < temp1[size1]){
				diff = (temp2[size2] - '0') - (temp1[size1] - '0') + 10;
				carry = 1;
			}
			if((temp2[size2] - carry) == temp1[size1]){
				diff = 0;
				carry = 0;
			}
			temp3[size3] = diff + '0';
			size1--;size2--;size3--;
		}
		if(size2 != -1){
			while(size2 != -1 && temp2[size2] == '0' && carry == 1){
				temp3[size3--] = '9';
				size2--;
			}
			temp3[size3--] = temp2[size2--] - carry;
			while(size2 != -1){
				temp3[size3--] = temp2[size2--];
			}
		}
	}
	else if(intal_compare(intal1 , intal2) == 0){
		temp3[0] = '0';
	}	
	
	return intal_create(temp3);
}
	
int intal_compare(void* intal1, void* intal2){

	long size1=0,size2=0;
	char *temp1,*temp2;
	int i=0;
	size1 = strlen(intal1);
	size2 = strlen(intal2);
	temp1 = (char*)malloc(sizeof(char)*(size1));
	temp2 = (char*)malloc(sizeof(char)*(size2));
	temp1 = intal1;
	temp2 = intal2;
	
	if(size1 > size2)
		return 1;
	else if(size2 > size1)
		return -1;
	for(i=0;i<size1;i++){
		if(temp1[i]>temp2[i])
			return 1;
		if(temp1[i]<temp2[i])
			return -1;
	}
	return 0;	
	
}

void* intal_multiply(void* intal1, void* intal2){

	if(intal1==NULL || intal2==NULL)
		return NULL;
		
	int i=0,ch=0,j=0,x=0;
	long size1=0,size2=0;
	char *temp1,*temp2,*table[10];
	size1 = strlen(intal1);
	size2 = strlen(intal2);
	if(size1 > size2){
		temp1 = (char*)malloc(sizeof(char)*(size1));
		temp2 = (char*)malloc(sizeof(char)*(size2));
		temp1 = intal1;
		temp2 = intal2;
	}
	else{
		temp1 = (char*)malloc(sizeof(char)*(size2));
		temp2 = (char*)malloc(sizeof(char)*(size1));
		temp1 = intal2;
		temp2 = intal1;
	}
	
	for(i=0;i<10;i++){
		table[i] = (char*)malloc(sizeof(char)*(strlen(temp1) +1));
		table[i] = multiply(temp1 , i);
	}
	char *sum;
	sum = (char*)malloc(sizeof(char)*(size1 + size2));
	
	i = 0;
	while(i < strlen(temp2)){
		x = strlen(sum);
		sum[x] = '0';
		ch = temp2[i] - '0';
		sum = intal_add(sum , table[ch]);
		i++;
	}
	
	return sum;	
}

void* multiply(void* intal , int i){
	
	int carry=0,product=0,j=0;
	long size=0,x=0;
	char *temp,*ans,*zero;
	size = strlen(intal);
	temp = (char*)malloc(sizeof(char)*size);
	temp = intal;
	ans = (char*)malloc(sizeof(char)*(size + 1));
	zero = (char*)malloc(sizeof(char));
	zero[0] = '0';
	
	if(i == 0){
		return zero;
	}
	
	x = size;
	while(x>0){
		j = temp[x-1] -'0';
		product = (i*j) + carry;
		carry = product / 10;
		product = product % 10;
		ans[x] = '0' + product;
		x--;
	}
	ans[x] = '0' + carry ;
	
	return intal_create(ans);
}

void* intal_pow(void* intal1, void* intal2)
{

  if(intal1==NULL || intal2==NULL)
      return NULL;
  char *string1=(char *)intal1;
  char *string2=(char *)intal2;
  char *string2_temp=(char *)malloc((strlen(string2)+1)*sizeof(char));
  strcpy(string2_temp,string2);
  char *product;
  if(string1[0]=='0' && string2[0]=='0')
  {
   product=(char *)malloc(2*sizeof(char));
   product[0]='0';
   product[1]='\0';
  }
  else if(string2_temp[0]-'0'==0)
  {
    product=(char *)malloc(2*sizeof(char));
    product[0]='1';
    product[1]='\0';
  }
  else
  {
    product=(char *)malloc(2*sizeof(char));
    product[0]='1';
    product[1]='\0';
    while(!(string2_temp[0]=='0' && strlen(string2_temp)==1))
    {
      product=(char *)intal_multiply((void *)product,(void *)string1);
      string2_temp=(char *)intal_decrement((void *)string2_temp);
    }
  }
  return (void *)product;
}

char* computing_multiplier(char* rem,void* intal,int* cnt)
{
    int flag=intal_compare((void*)(rem),intal);
    *cnt=0;
    while(flag==1)
    {
       (*cnt)++;
       rem=intal_diff((void*)(rem),intal);
       flag=intal_compare((void*)(rem),intal);
    }
    if(flag==0)
    {
        (*cnt)++;
        rem=intal_diff((void*)(rem),intal);
    }
    return rem;
}

void* intal_divide(void* intal1,void* intal2)
{
    if(intal1==NULL || intal2==NULL)
        return NULL;
        
    if(intal_compare(intal2,intal_create("0")) == 0 ){
    	return NULL;
    }
    if(intal_compare(intal1,intal2)==-1)
        return intal_create("0");
    char* temp1= (intal_create(intal1));   
    char* temp2= (intal_create(intal2));   
    int l1=strlen(temp1);
    int l2=strlen(temp2);
    char* rem=(char*)malloc(sizeof(char)*(l2+1));
    char* quo=(char*)malloc(sizeof(char)*(l1));
    int i,k=0;
    for(i=0;i<l2;i++)
    { 
        rem[i]=temp1[i];
    }
    int len,cnt;
    while(i<=l1)
    {
        rem=computing_multiplier(rem,intal2,&cnt);
        quo[k++]=cnt+48;
        len=strlen(rem);
        rem[len]=temp1[i++];
        rem[len+1]='\0';
     }
     quo[k]='\0';
     return intal_create((void*)(quo));
}
	          
long max(long a, long b){
	if(a > b)
		return a;
	else
		return b;
}

