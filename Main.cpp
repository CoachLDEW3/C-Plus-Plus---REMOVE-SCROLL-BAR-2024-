/************************************************************************************************
Name:		CoachLDEW
Date:	 	10.16.2024
Purpose: 	This program will remove the scrollbar. To remove the scrollbar, simply set the 
            screen buffer height to be the same size as the height of the window. Get the window 
            size with GetConsoleScreenBufferInfo, srWindow member. Set the buffer size with 
            SetConsoleScreenBufferSize().
*************************************************************************************************/


#include <iostream>			//This library contains standard input and output processes
#include <windows.h>		//This library contains the function to control the cursor position


using namespace std;

int main()
{
    //Get handle to the console window
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    //Retrieve screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    //Current window size
    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

    //Current screen buffer size
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    //In order to remove the scrollbar, make sure the window height matches the screen buffer height
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    //Set the new screen buffer dimensions
    int Status = SetConsoleScreenBufferSize(hOut, newSize);
    if (Status == 0)
    {
        cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
        exit(Status);
    }

    //Printing out the current screen buffer dimensions
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    cout << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << endl;

    return 0;
}