#include <windows.h>
#include <stdio.h>
#include<inttypes.h>

#include<winuser.h>
#include<string>

#include "mapping.h"


HANDLE hStdin;
DWORD fdwSaveOldMode;
std::string s;
SpecialCharacters *specialCharactersObj;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD,Mapping* mappingObject);

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

int service(VOID) {
	specialCharactersObj = new SpecialCharacters;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter=0;
	s="";
//    Mapping mappingObject = new Mapping();
	Mapping * mappingObject = new Mapping;

	// Get the standard input handle.

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit.

	if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events.

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (! SetConsoleMode(hStdin, fdwMode) )
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events.

	while (true) {
		// Wait for the events.

		if (! ReadConsoleInput(
		            hStdin,      // input buffer handle
		            irInBuf,     // buffer to read into
		            128,         // size of read buffer
		            &cNumRead) ) // number of records read
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler.

		for (i = 0; i < cNumRead; i++) {
			switch(irInBuf[i].EventType) {
				case KEY_EVENT: // keyboard input
					KeyEventProc(irInBuf[i].Event.KeyEvent,mappingObject);
					break;

				case MOUSE_EVENT: // mouse input
					break;

				case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
					break;

				case FOCUS_EVENT:  // disregard focus events

				case MENU_EVENT:   // disregard menu events
					break;

				default:
					ErrorExit("Unknown event type");
					break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}

VOID ErrorExit (LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}



VOID KeyEventProc(KEY_EVENT_RECORD ker,Mapping* mappingObject) {

	if(ker.bKeyDown) {
		char characterPressed= mappingObject->getCharMapping((int)ker.wVirtualKeyCode,specialCharactersObj);
		if(characterPressed==13) {
			std::cout<<s<<std::endl;
			s="";
		} else if(characterPressed==8) {
			if(!s.empty()) s.pop_back();
		} else if(characterPressed!=0) {
			s=s+characterPressed;
		}

	}
}


