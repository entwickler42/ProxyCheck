#include <vcl.h>
#include <winsock2.h>
#pragma hdrstop

#include "main.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TInterface *Interface;

//---------------------------------------------------------------------------
__fastcall TInterface::TInterface(TComponent* Owner)  : TForm(Owner)
{}

//---------------------------------------------------------------------------
void __fastcall TInterface::btnQuitClick(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TInterface::btnCheckClick(TObject *Sender)
{
    WSAData data;
    unsigned int cs;
    unsigned long addr;
    char vBuf[512], pBuf[512], buf[256], ch;
    WSAStartup(MAKEWORD(1,1),&data);

    struct sockaddr_in server;
    struct hostent *host;

    // Connect Verify Server
    if(Web->Text.Length() == 0)
    {
        Application->MessageBoxA("We need to enter a hostname !","Error",MB_OK);
        return;
    }

    addr = inet_addr(Web->Text.c_str());
    if(addr == INADDR_NONE)
    {
        host = gethostbyname(Web->Text.c_str());
        if(host != NULL) memcpy(&addr,host->h_addr,4);
        else             addr = INADDR_NONE;
    }

    if(addr == INADDR_NONE)
    {
        Application->MessageBoxA("Can not resolve verify hostname !","Error",MB_OK);
        return;
    }

    server.sin_family        = AF_INET;
    server.sin_port          = htons(WPort->Text.ToInt());
    *(long*)&server.sin_addr = addr;
    memset(server.sin_zero,0,8);

    cs = socket(AF_INET,SOCK_STREAM,0);
    if(connect(cs,(struct sockaddr*)&server,sizeof(struct sockaddr_in)) != 0)
    {
        Application->MessageBoxA("Can not connect verify server !","Error",MB_OK);
        closesocket(cs);
        return;
    }

    memset(vBuf,0,512);

    strcpy(buf,"GET / HTTP/1.0\n\n");

    send(cs,buf,strlen(buf),0);

    do
    {
        recv(cs,&ch,1,0);
    } while(ch!= '<');

    vBuf[0] = '<';
    recv(cs,vBuf+1,511,0);

    closesocket(cs);

    // Connect Proxy Server
    if(Proxy->Text.Length() == 0)
    {
        Application->MessageBoxA("We need to enter a proxy server !","Error",MB_OK);
        return;
    }

    addr = inet_addr(Proxy->Text.c_str());
    if(addr == INADDR_NONE)
    {
        host = gethostbyname(Web->Text.c_str());
        if(host != NULL) memcpy(&addr,host->h_addr,4);
        else             addr = INADDR_NONE;
    }

    if(addr == INADDR_NONE)
    {
        Application->MessageBoxA("Can not resolve verify hostname !","Error",MB_OK);
        return;
    }

    server.sin_family        = AF_INET;
    server.sin_port          = htons(WPort->Text.ToInt());
    *(long*)&server.sin_addr = addr;
    memset(server.sin_zero,0,8);

    cs = socket(AF_INET,SOCK_STREAM,0);
    if(connect(cs,(struct sockaddr*)&server,sizeof(struct sockaddr_in)) != 0)
    {
        Application->MessageBoxA("Can not connect proxy server !","Error",MB_OK);
        closesocket(cs);
        return;
    }

    memset(pBuf,0,512);

    strcpy(buf,"GET http://");
    strcat(buf,Web->Text.c_str());
    strcat(buf,"/ HTTP/1.0\n\n");

    send(cs,buf,strlen(buf),0);

    do
    {
        recv(cs,&ch,1,0);
    } while(ch!= '<');

    pBuf[0] = '<';
    recv(cs,pBuf+1,511,0);

    pBuf[511] = 0x0;    vBuf[511] = 0x0;

    if(strlen(pBuf) == strlen(vBuf))
    {
        if(strcmp(pBuf,vBuf) == 0) Application->MessageBoxA("Proxy is working fine !","Succsess",MB_OK);
        else                       Application->MessageBoxA("Proxy is doen't work !","Failure",MB_OK);
    }
    else Application->MessageBoxA("Proxy is working fine !","Succsess",MB_OK);

    closesocket(cs);
    WSACleanup();
}
//---------------------------------------------------------------------------
