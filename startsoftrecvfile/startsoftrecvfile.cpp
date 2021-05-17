#include <WinSock.h>
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cstring>
#include <string.h>
#include<tlhelp32.h>
#include<string>
#pragma warning(disable:4996)

using namespace std;
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"wmainCRTStartup\"" )

//可完善内容，判断程序是否已经启动在做操作

/*int find_process(string process_name)
{
    int count=0;//进程计数 
    PROCESSENTRY32 pe32;
    
    pe32.dwSize=sizeof(PROCESSENTRY32);
    HANDLE process_snapshot_handle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//创建进程快照句柄
    
    if(process_snapshot_handle==INVALID_HANDLE_VALUE) return -1;//创建句柄失败
    
    bool is_exist=Process32First(process_snapshot_handle,&pe32);//找第一个
    while(is_exist)
    {
		char *str = (char *)pe32.szExeFile;
		if(!stricmp(process_name.c_str(),str)) count++;//进程名不区分大小写
        is_exist=Process32Next(process_snapshot_handle,&pe32);//找下一个
    }
    
    return count;
}
*/


BOOL IsProcessExit(const WCHAR* strFilename) 
{ 
	BOOL bRet = FALSE;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		return FALSE;
	}
 
	PROCESSENTRY32 pe32 = {0};
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32)){
		do{
			if(_wcsicmp(pe32.szExeFile, strFilename) == 0){
				bRet = TRUE;
				break;
			}
		}
		while (Process32Next(hProcessSnap, &pe32));
	} 
	else{
		bRet = FALSE;
	}
	CloseHandle(hProcessSnap);
	return bRet;
}


int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR sz[50];
	TCHAR *p=TEXT("recvfile.exe");
	_tcscpy(sz,p);

	while(1){
	
	BOOL process = IsProcessExit(sz); 
	
	if(!process)
		{
			cout<<"recvfile.exe没有运行"<<endl;
			char filepos[1024] = "cmd.exe /c C\:\\recvapp\\tool\\recvfile.exe";//启动接收程序
			//cout << "filepos:" << filepos << endl;
			WinExec(filepos, SW_HIDE);
			Sleep(10000);//启动后休眠10s
		}
	else 
		{
			cout<<"recvfile.exe is running"<<endl;
			Sleep(15000);//程序还在运行就睡眠等待
		}
	}
	return 0;
}

/*bool isProcessExist()
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    DWORD dwPid = 0;
    int nProcCount = 0;
 
    // 截取系统中运行进程的快照
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return false;
    }
 
    pe32.dwSize = sizeof(PROCESSENTRY32);
 
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return false;
    }
 
    // 获取自己程序的进程名，用于比对
    TCHAR szFileFullPath[_MAX_PATH] = {0};
 
    ::GetModuleFileName(NULL, static_cast<LPTSTR>(szFileFullPath), _MAX_PATH);
 
    int iLength = 0;
    char szFullPath[_MAX_PATH] = {0};
    //获取字节长度
    iLength = WideCharToMultiByte(CP_ACP, 0, szFileFullPath, -1, NULL, 0, NULL, NULL);
    //将tchar值赋给_char
    WideCharToMultiByte(CP_ACP, 0, szFileFullPath, -1, szFullPath, iLength, NULL, NULL);
 
    std::string strProcPath = szFullPath;
    // 得到自身进程名
    std::string szProcName = strProcPath.substr(strProcPath.find_last_of("\\") + 1);
 
    bool bRet = false;
    char szPeProcName[_MAX_PATH] = {0};
    do
    {
        // 遍历进程快照，比对是否有同名进程
        memset(szPeProcName, 0, _MAX_PATH);
 
        // wchar 转 char*
        sprintf_s(szPeProcName, "%ws", pe32.szExeFile );
 
        if (0 == strcmp(szProcName.c_str(), szPeProcName))
        {
            dwPid = pe32.th32ProcessID;
 
            ++nProcCount;
			//if ((nProcCount = 1)&&(0 == strcmp(szProcName.c_str(),"recvfile.exe")))
            //if ((nProcCount > 1)&&(0 == strcmp(szProcName.c_str(),"startsoftrecvfile.exe")))
			if ((nProcCount >= 1)&&(0 == strcmp(szProcName.c_str(),"cmd.exe")))
            {
                // 不止有一个进程
                bRet = true;
				cout << "————————————————————-程序已经运行" << endl;
                break;
            }
        }
 
    } while (Process32Next(hProcessSnap, &pe32));
 
    CloseHandle(hProcessSnap);
	 
    return bRet;
}*/

/*
//打开文件判断内容（真执行代码，假sleep等待）
		char stat[10] = { 0 }; //获取服务端ip
		FILE *fp = NULL;
		fp = fopen("C:\\ip\\runsoft.txt", "r");
		if (fp == NULL)
			return -1;
		int ret;
		while (1)//读取软件运行状态
		{
			memset(stat, 0, 256);
			if(ret = fread(stat, sizeof(char), 10, fp) != 0);//读取内容	
			break;
		}
		fseek(fp, 0, SEEK_SET);
		fclose(fp);//关闭文件
		cout << "程序运行态 :" << stat << endl;*/