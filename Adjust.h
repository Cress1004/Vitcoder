#include<ctype.h>
void Adjust(char *str)
{
    int i,j;
    //xoa ki tu dac biet
   	for(i=0; i<strlen(str); i++){
	   	for(i=0; i<strlen(str); i++){
    		if((isalpha(str[i])==0)&&(str[i]!=' ')){
				strcpy(&str[i], &str[i+1]);
	  			i--;
			}
		}
	}
	
    //xoa ki tu trang o dau chuoi
    while(str[0]==' '){
  	for(i=0; i<(strlen(str)); i++){
	  	str[i]=str[i+1];
	  	}
	}
	
    //xoa ki tu trong o giua
  	for(i=0; i<(strlen(str)-1); i++){
    	if((str[i]==' ')&&(str[i+1]==' ')){
	  	strcpy(&str[i], &str[i+1]);
	  	i--;
	  	}
    }
    
  	//xoa ki tu trang o cuoi cau
  	while (str[strlen(str)-1]==' ')
    strcpy(&str[strlen(str)-1],&str[strlen(str)]);
    
    
  	//chuyen het tat ca thanh chu thuong
  	for(i=0; i<strlen(str); i++) {
  		if ((str[i]>=65)&&(str[i]<=90))
		str[i]=tolower(str[i]);
    }
    
  	// viet hoa ki tu dau
  	if ((str[0]>=97)&&(str[0]<=122)) str[0]=toupper(str[0]);
  	for (i=1; i<strlen(str); i++){
    	if(str[i]==' '){
	  		if ((str[i+1]>=97)&&(str[i+1]<=122)) str[i+1]=toupper(str[i+1]);
	 	}	
    }	
}

