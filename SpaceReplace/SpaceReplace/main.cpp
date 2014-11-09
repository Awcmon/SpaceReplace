
#include <iostream>
#include <windows.h>

using namespace std;


void SendKeysEx(BYTE myCommand)
{
	keybd_event(myCommand, 0, 0, 0);
	keybd_event(myCommand, 0, KEYEVENTF_KEYUP, 0);
}


void KeyPressVK(short keyIn, unsigned char keyOut)
{
	if (GetAsyncKeyState(keyIn))
	{
		SendKeysEx(keyOut);
		Sleep(1);
	}
}

void KeyPress(short keyIn, short keyOut)
{
	if (GetAsyncKeyState(keyIn))
	{
		keybd_event((unsigned char)keyOut, 0, 0, 0);
		keybd_event((unsigned char)keyOut, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1);
	}
}

class Key{
public:
	Key(short _keyIn, short _keyOut);
	void HandleEvents();
private:
	bool keyDown;
	short keyIn;
	short keyOut;
};

Key::Key(short _keyIn, short _keyOut)
{
	keyIn = _keyIn;
	keyOut = _keyOut;
	keyDown = false;
}

void Key::HandleEvents()
{
	if (GetAsyncKeyState(keyIn) && !keyDown)
	{
		keybd_event((unsigned char)keyOut, 0, 0, 0);
		keyDown = true;
	}
	if (!GetAsyncKeyState(keyIn) && keyDown)
	{
		keybd_event((unsigned char)keyOut, 0, KEYEVENTF_KEYUP, 0);
		keyDown = false;
	}
}

int main()
{

	Key spaceReplace(VK_SHIFT, VK_SPACE);

	while (1)
	{
		spaceReplace.HandleEvents();
	}

	return 0;
}
