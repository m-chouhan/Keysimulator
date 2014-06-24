#define _WIN32_WINNT 0x0500 //For INPUT class

#include "KeySimulatorServer.h"
#include <QMessageBox>
#include <windows.h>
#include "Utility.h"


KeySimulatorServer::KeySimulatorServer(QString addr,QWidget *parent) : QDialog(parent)
{
    Bindings();

    connect(&serversocket,SIGNAL(readyRead()),this,SLOT(readData()));

    if(!serversocket.bind(QHostAddress::Any,19000)) //if error occurs
    {
        QMessageBox::critical(this,tr("!!ERROR!!"),tr("Unable To Start"));
    }
    width = GetSystemMetrics(SM_CXSCREEN);height = GetSystemMetrics(SM_CYSCREEN);
    //qDebug()<<width<<":"<<height;
    label = new QLabel(this); //to display info on gui
    label->setText("listening on 19000");
}



/*read data will be called to respond to the commands sent by the client*/
void KeySimulatorServer::readData()
{
    // TODO :
    // From String shift to numbers, send key codes from clients
    //

    char D[20]={0};
    int size = serversocket.pendingDatagramSize();
    QHostAddress sender;quint16 sport = 0;
    //qDebug()<<size<<"before"<<(short)*(D+1);
    serversocket.readDatagram(D,size,&sender,&sport);
    switch(D[0])
    {
        case 0: sendtoKeyBoard(D[1]);
                break;

        case 1: HandleSensorMovements(D);
                break;

        case 2: HandleTouchMovements(D);
                break;

        case 3: //For absolute mouse movements
                {
                float *dx = (float*)(D+1),*dy = (float *)(D+5);
                //Mouse_Move_Abs((int)*dx,(int)*dy);
                }
                break;

        case 4: //For replying to broadcast message
                {
                QByteArray temp;
                qDebug()<<"MessageFrom"<<sender<<sport<<temp;
                temp.clear();temp.append(sender.toString()+":"+QString(sport));
                serversocket.writeDatagram(temp,sender,sport);
                }
                break;
        case 5://For handling input text
                char *etext = D+1;
                //QString str(etext);
                //str = str.toUpper();
                SendText(etext);
                //qDebug()<<"after"<<etext;
                break;
    }

}

/*for simulating press and release key functions individually */

void KeySimulatorServer::PressKey(char c)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
}

void KeySimulatorServer::ReleaseKey(char c)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
}

void KeySimulatorServer::Sendchar(quint8 c)
{
    INPUT ip={0};
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;    
    SendInput(1, &ip, sizeof(INPUT));
    //Sleep(1);
}

void KeySimulatorServer::SendText(char*text)
{
    INPUT ip = {0};
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = VK_LSHIFT;
    int len  = strlen(text);
    for(int i=0;i<len;i++)
    {

        if(isupper(text[i]))
        {
            ip.ki.dwFlags = 0;
            SendInput(1,&ip,sizeof(INPUT));
            Sendchar(text[i]);
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1,&ip,sizeof(INPUT));
        }
        else if(islower(text[i]))
            Sendchar(toupper(text[i]));
        else
        {
            //qDebug()<<(int)text[i]<<"_";
            std::map<char,KEY>::iterator it = mapper.find(text[i]);
            if(it != mapper.end())
            {
                qDebug()<<"Found";
                if(it->second.SHIFT)
                {
                    ip.ki.dwFlags = 0;
                    SendInput(1,&ip,sizeof(INPUT));
                }
                Sendchar(it->second.V_Key);
                if(it->second.SHIFT)
                {
                    ip.ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(1,&ip,sizeof(INPUT));
                }
            }
            else Sendchar(text[i]);
        }
    }
}

void KeySimulatorServer::SendInt(char number)
{
    char buff[32];
    memset(buff,0,32);
    itoa(number,buff,10);
    SendText(buff);
}

void KeySimulatorServer::HandleSensorMovements(char Data[])
{
    static float x = 0,y = 0;
    static quint64 tstamp = 0;
    static float xvelo = 0,yvelo = 0;

    float *a = (float *)(Data+1),*b = (float *)(Data+5);
    quint64 *time = (quint64 *) (Data+9);
    quint64  dT = (*time-tstamp)/1000000;

    x = (-x)+(*a);y = (-y) + (*b);
    if(x>50 || x<-50)
    {
        x = 0;
        qDebug()<<"resetting";
    }
    float xvel = (float)x/dT,yvel = (float)y/dT;
    xvelo = (xvel - xvelo)/dT; yvelo = (yvel-yvelo)/dT;

/*    qDebug()<<"dX:"<<x<<"\ndY:"<<y<<"\tt:"<<*time<<"\t"<<dT;
    qDebug()<<"Xvel"<<xvel<<"\t"<<xvelo
            <<"\nYvel"<<yvel<<"\tyvelo"<<yvelo<<"\ndT"
            <<dT<<"\t"<<xvel<<"\t"<<yvel;*/
    Mouse_Move(x*5+xvel*3+xvelo,y*5+yvel*03+yvelo);
    x = *a;y = *b;
    tstamp = *time;
    xvelo = xvel;yvelo = yvel;
}

void KeySimulatorServer::HandleTouchMovements(char Data[])
{
    float *dx = (float*)(Data+1),*dy = (float *)(Data+5);
    quint8 action = Data[9];quint32 *mousedata = (quint32*)(Data+10);
    //qDebug()<<"Action"<<action;
    if(action == mouseActions::MOVE)
        Mouse_Move((int)*dx,(int)*dy);
    else
        Mouse_Press((int)*dx,(int)*dy,*mousedata,action);
}

void KeySimulatorServer::Mouse_Move(int x,int y)
{
    //qDebug()<<"Mouse_MOVE";
    INPUT ip;
    ZeroMemory(&ip, sizeof(ip));
    ip.type = INPUT_MOUSE; // Input is mouse event
    ip.mi.dx = x; //Relative movementes of x,y coordi
    ip.mi.dy = y;
    ip.mi.mouseData = 0; // 0 for movements
    ip.ki.time = 0; //timestamp 0 means system will provide it
    ip.mi.dwFlags = MOUSEEVENTF_MOVE; // for mouse movements

    SendInput(1, &ip, sizeof(INPUT));
}

void KeySimulatorServer::Mouse_Move_Abs(int x,int y)
{
    qDebug()<<"Mouse_MOVE_Abs"<<x<<y;
    INPUT ip;
    ZeroMemory(&ip, sizeof(ip));
    ip.type = INPUT_MOUSE; // Input is mouse event
    ip.mi.dx = x; //Relative movementes of x,y coordi
    ip.mi.dy = y;
    ip.mi.mouseData = 0; // 0 for movements
    ip.ki.time = 0; //timestamp 0 means system will provide it
    ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE; // for mouse movements

    SendInput(1, &ip, sizeof(INPUT));
}


void KeySimulatorServer::Mouse_Press(int x,int y,qint32 data,int action)
{
    qDebug()<<"Mouse_Press"<<action;
    INPUT ip = {0};
    ip.type = INPUT_MOUSE;
    ip.ki.time = 0;
    switch(action)
    {
        case mouseActions::LEFT_SINGLE:
        {
            ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1,&ip,sizeof(INPUT));
            ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }
        case mouseActions::LEFT_HOLD:
        {
            ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }
        case mouseActions::LEFT_RELEASE:
        {
            ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }
        case mouseActions::ROLL:
        {
            ip.mi.dwFlags = MOUSEEVENTF_WHEEL;
            ip.mi.mouseData = data;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }
        case mouseActions::RIGHT_SINGLE:
        {
            ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            SendInput(1,&ip,sizeof(INPUT));
            ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }

        case mouseActions::RIGHT_HOLD:
        {
            ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }

        case mouseActions::RIGHT_RELEASE:
        {
            ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            SendInput(1,&ip,sizeof(INPUT));
            break;
        }

    }
}

void KeySimulatorServer::sendtoKeyBoard(quint8 data)
{
    this->Sendchar(data);
}
