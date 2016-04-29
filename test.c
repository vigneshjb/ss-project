#include <stdio.h>

int main()
{
	int a =1;
	printf("kajgkab %%%n dfkjv %213d fan %n", &a, a, &a);
}

// #include <string.h>

// int nonNformat(char a){
// 	int res = 1;
// 	switch(a){
// 		case 'd': break;
// 		case 'i': break;
// 		case 'o': break;
// 		case 'u': break;
// 		case 'x': break;
// 		case 'X': break;
// 		case 'e': break;
// 		case 'E': break;
// 		case 'f': break;
// 		case 'F': break;
// 		case 'g': break;
// 		case 'a': break;
// 		case 'A': break;
// 		case 'c': break;
// 		case 's': break;
// 		case 'p': break;
// 		case 'm': break; 
// 		default: res=0; break;
// 	}
// 	return res;
// }

// int main(){
// 	int numArgs, i=0, testflg=0;

// 	char *format_str = "shvdbkjsdnlk %n ask nkef awn %498535$*.7d";
// 	char our_format_str[10000];

// 	strcpy(our_format_str, format_str);

// 	puts(our_format_str);

// 	while(1){
// 		if (format_str[i]=='\0'|| i>strlen(format_str))
// 			break;
// 		else if(format_str[i]=='%' && format_str[i+1]=='%')
// 			i++;
// 		else if (format_str[i]=='%'){
// 			testflg=1;
// 		}
// 		if (testflg==1 && nonNformat(format_str[i])==1){
// 			testflg=0;
// 		}
// 		else if(testflg==1 && format_str[i]=='n'){
// 			testflg=0; 
// 			our_format_str[i]='p';
// 		}
// 		i++;
// 	}

// 	puts(our_format_str);
// }