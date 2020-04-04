/*
 * @Author Shi Zhangkun
 * @Date 2020-04-03 23:53:21
 * @LastEditTime 2020-04-04 00:30:28
 * @LastEditors Shi Zhangkun
 * @Description none
 * @FilePath /project/lib/atox.c
 */
#include "stdlib.h"
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
double atof(char *str)
{

}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
int atoi(char *str)
{

}
/**
 * @brief  
 * @note  
 * @param {type} none
 * @retval none
 */
long atol(char *str)
{

}
/**
 * @brief  int to char
 * @note   copyed from stdlib source,
 * @param {int} num : int to transfer,when radix != 10 num regard as unsigned int
 * @param {char*} str : str buf to recive
 * @param {int} radix 
 * @retval str
 */
char* itoa(int num,char* str,int radix)
{
  if(radix > 16)
    radix = 16;

  char index[]="0123456789ABCDEF";
  unsigned unum;
  int i=0,j,k;
  
  if(radix==10&&num<0)
  {
    unum=(unsigned)-num;
    str[i++]='-';
  }
  else 
    unum=(unsigned)num;
  
  do{
      str[i++]=index[unum%(unsigned)radix];
      unum/=radix;
    }while(unum);
  str[i]='\0';
  
  if(str[0]=='-')
    k=1;
  else
    k=0;
    
  for(j=k;j<=(i-1)/2;j++)
  {      
    char temp;
    temp=str[j];
    str[j]=str[i-1+k-j];
    str[i-1+k-j]=temp;
  }
  return str;
}