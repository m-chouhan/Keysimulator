#ifndef KEYSIMULATORSERVER_H
#define KEYSIMULATORSERVER_H

#include<QtNetwork>
#include<QDialog>
#include<QLabel>
#include<QObject>
#include<QDataStream>
#include<QDebug>

/*This class listens for commands from client and then simulates the
  keypresses accordingly */

namespace mouseActions{
    enum myActions {
        MOVE = 0,
        LEFT_SINGLE,LEFT_DOUBLE,LEFT_HOLD,LEFT_RELEASE,
        ROLL,
        RIGHT_SINGLE,RIGHT_DOUBLE,RIGHT_HOLD,RIGHT_RELEASE
    };
}

class KeySimulatorServer :public QDialog
    {
        Q_OBJECT
        QUdpSocket serversocket;
        QLabel *label;
        QByteArray temp;
        int width,height;

        /*Simulates mouse movement */
        void Mouse_Move(int x,int y);
        void Mouse_Move_Abs(int x,int y);

        void HandleSensorMovements(char Data[]);
        void HandleTouchMovements(char Data[]);

        /*Simulates mouse Press */
        void Mouse_Press(int x,int y,qint32 data, int action);
        /*Simulates a key press */
        void PressKey(char c);

        /*Simulates a key Release */
        void ReleaseKey(char c);

        /*Simulates a key press of the given char
          internally calls PressKey() */

        void Sendchar(quint8 c);
        /*Simulates a key presses of the given Text stream
          internally calls Sendchar() */
        void SendText(char*text);

        /*For sending integers */
        void SendInt(char number);

        void sendtoKeyBoard(quint8 data);
        public:
        KeySimulatorServer(QString addr,QWidget *parent = 0);
        public slots:
        void readData();
    };

#endif // KEYSIMULATORSERVER_H
