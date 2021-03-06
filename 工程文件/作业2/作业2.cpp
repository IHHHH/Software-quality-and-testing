// 作业2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

char* t;        //result
char* wr;       //output
char a[50];     //记录输入数据
char b[50];     //记录读取的文件地址
char WC[1000];  //保存打开的文件内容

int col_count(const char* t);                                             //统计字符数
int col_row(const char* t);                                               //统计行数
int col_word(const char* t);                                              //统计单词数
void result(const char* t, const char* a, int num);                       //产生结果文件
void output(const char* t, const char* w, int count, int row, int word);  //产生输出文件

int main()
{
	int count = 0;
	int row = 0;
	int word = 0;
		
	scanf_s("%[^\n]", a, 50);
	
	for (int i = 0; a[i] != NULL; i++)   
	{
		if(a[i] == '-')
			if (a[i+1] == 'o')
				for (int j = i+1; a[j] != NULL; j++)       
				{
					if (a[j] == ' ')
						if (a[j + 1] != ' '&&a[j + 1] != '-')       //输出文件入口判断
						{
							wr = a + j + 1;
							break;
						}
				}				
	}
	
	for (int i = 1; a[i] != NULL; i++)
	{
		if (a[i - 1] == ' ')
			if (a[i] != ' '&&a[i] != '-')   //目标文件名入口判断
			{
				int j = i;
				while (a[i] != ' '&&a[i] != NULL)         //目标文件名出口判断
				{ 
					b[i] = a[i];
					i++;
				}
				t = b + j;
				break;
			}
	}
	
	for (int i = 0; a[i] != NULL; i++)
	{
		if(a[i] == '-')
		{ 
			if (a[i + 1] == 'c')
			{
				count = col_count(t);
				printf_s("字符数：%d", count);
				result(t, "字符数", count);
				printf_s("\n");
			}
			if (a[i + 1] == 'l')
				{
					row = col_row(t);
					printf_s("行数：%d", row);
					result(t, "行数", row);
					printf_s("\n");
				}
			if (a[i + 1] == 'w')
				{
					word = col_word(t);
					printf_s("单词数：%d", word);
					result(t, "单词数", word);
					printf_s("\n");
				}
			if (a[i + 1] == 'o')
				{
					output(t, wr, count, row, word);
					printf_s("\n");
				}		
		}						
	

	}
	
	getchar();
	return 0;
}

int col_count(const char* t)
{
	char data;
	FILE *fp;
	errno_t err;
	int count = 0;
	err = fopen_s(&fp, t, "r");
	if (err != 0)
	{
		printf("can't open file\n");
		count = -1;
	}
	while ((data = getc(fp)) != EOF)
	{
		WC[count] = data;
		count++;
	}
	fclose(fp);
	return count;
}

int col_row(const char* t)
{
	char data;
	FILE *fp;
	errno_t err;
	int row = 0;
	err = fopen_s(&fp, t, "r");
	if (err != 0)
	{
		printf("can't open file\n");
		row = -1;
	}
	while ((data = getc(fp)) != EOF)
		if (data == '\n')
			row++;
	fclose(fp);
	return row;
}

int col_word(const char* t)
{
	char data;
	FILE *fp;
	errno_t err;
	int word = 0;
	int i = 0;
	err = fopen_s(&fp, t, "r");
	if (err != 0)
	{
		printf("can't open file\n");
		word = -1;
	}
	while ((data = getc(fp)) != EOF)
	{
		WC[i] = data;
		i++;
	}
	if (WC[0] != ' ' && WC[0] != ',' && WC[0] != '\n')
		word++;
	for (i = 0; WC[i] != NULL; i++)
	{
		if (WC[i] == ' ' || WC[i] == ',' || WC[i] == '\n')
			if (WC[i + 1] != ' ' && WC[i + 1] != ',' && WC[i + 1] != '\n')
				word++;
	}
	fclose(fp);
	return word;
}

void result(const char* t, const char* a, int num)
{
	FILE *wt;
	errno_t err;
	err = fopen_s(&wt, "result.txt", "a+");
	if (err != 0)
	{
		printf("can't write file\n");
	}
	fprintf(wt, "%s，%s：%d\n", t, a, num);
	fclose(wt);
}

void output(const char* t, const char* w, int count, int row, int word)
{
	FILE *wt;
	errno_t err;
	err = fopen_s(&wt, w, "a+");
	if (err != 0)
	{
		printf("can't write file\n");
	}
	fprintf(wt, "%s，字符数：%d，行数：%d，单词数：%d", t, count, row, word);
	fclose(wt);
}