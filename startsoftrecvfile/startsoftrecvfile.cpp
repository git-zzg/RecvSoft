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

//���������ݣ��жϳ����Ƿ��Ѿ�������������

/*int find_process(string process_name)
{
    int count=0;//���̼��� 
    PROCESSENTRY32 pe32;
    
    pe32.dwSize=sizeof(PROCESSENTRY32);
    HANDLE process_snapshot_handle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//�������̿��վ��
    
    if(process_snapshot_handle==INVALID_HANDLE_VALUE) return -1;//�������ʧ��
    
    bool is_exist=Process32First(process_snapshot_handle,&pe32);//�ҵ�һ��
    while(is_exist)
    {
		char *str = (char *)pe32.szExeFile;
		if(!stricmp(process_name.c_str(),str)) count++;//�����������ִ�Сд
        is_exist=Process32Next(process_snapshot_handle,&pe32);//����һ��
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
			cout<<"recvfile.exeû������"<<endl;
			char filepos[1024] = "cmd.exe /c C\:\\recvapp\\tool\\recvfile.exe";//�������ճ���
			//cout << "filepos:" << filepos << endl;
			WinExec(filepos, SW_HIDE);
			Sleep(10000);//����������10s
		}
	else 
		{
			cout<<"recvfile.exe is running"<<endl;
			Sleep(15000);//���������о�˯�ߵȴ�
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
 
    // ��ȡϵͳ�����н��̵Ŀ���
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
 
    // ��ȡ�Լ�����Ľ����������ڱȶ�
    TCHAR szFileFullPath[_MAX_PATH] = {0};
 
    ::GetModuleFileName(NULL, static_cast<LPTSTR>(szFileFullPath), _MAX_PATH);
 
    int iLength = 0;
    char szFullPath[_MAX_PATH] = {0};
    //��ȡ�ֽڳ���
    iLength = WideCharToMultiByte(CP_ACP, 0, szFileFullPath, -1, NULL, 0, NULL, NULL);
    //��tcharֵ����_char
    WideCharToMultiByte(CP_ACP, 0, szFileFullPath, -1, szFullPath, iLength, NULL, NULL);
 
    std::string strProcPath = szFullPath;
    // �õ����������
    std::string szProcName = strProcPath.substr(strProcPath.find_last_of("\\") + 1);
 
    bool bRet = false;
    char szPeProcName[_MAX_PATH] = {0};
    do
    {
        // �������̿��գ��ȶ��Ƿ���ͬ������
        memset(szPeProcName, 0, _MAX_PATH);
 
        // wchar ת char*
        sprintf_s(szPeProcName, "%ws", pe32.szExeFile );
 
        if (0 == strcmp(szProcName.c_str(), szPeProcName))
        {
            dwPid = pe32.th32ProcessID;
 
            ++nProcCount;
			//if ((nProcCount = 1)&&(0 == strcmp(szProcName.c_str(),"recvfile.exe")))
            //if ((nProcCount > 1)&&(0 == strcmp(szProcName.c_str(),"startsoftrecvfile.exe")))
			if ((nProcCount >= 1)&&(0 == strcmp(szProcName.c_str(),"cmd.exe")))
            {
                // ��ֹ��һ������
                bRet = true;
				cout << "����������������������������������������-�����Ѿ�����" << endl;
                break;
            }
        }
 
    } while (Process32Next(hProcessSnap, &pe32));
 
    CloseHandle(hProcessSnap);
	 
    return bRet;
}*/

/*
//���ļ��ж����ݣ���ִ�д��룬��sleep�ȴ���
		char stat[10] = { 0 }; //��ȡ�����ip
		FILE *fp = NULL;
		fp = fopen("C:\\ip\\runsoft.txt", "r");
		if (fp == NULL)
			return -1;
		int ret;
		while (1)//��ȡ�������״̬
		{
			memset(stat, 0, 256);
			if(ret = fread(stat, sizeof(char), 10, fp) != 0);//��ȡ����	
			break;
		}
		fseek(fp, 0, SEEK_SET);
		fclose(fp);//�ر��ļ�
		cout << "��������̬ :" << stat << endl;*/