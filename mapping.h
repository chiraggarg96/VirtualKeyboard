#include <windows.h>
#include <stdio.h>
#include<inttypes.h>
#include "specialCharacters.h"
#include<winuser.h>

class Mapping {
		bool shiftFlag =false;
		bool capsFlag =false;
		bool controlFlag=false;


		void getShiftStatus() {
			if ((GetKeyState(VK_LSHIFT) & 0x8000) || (GetKeyState(VK_RSHIFT) & 0x8000)) {
				shiftFlag=true;
			}

		}
		void getCapsStatus() {
			if ((GetKeyState(VK_CAPITAL) & 0x0001)!=0 ) {
				capsFlag=true;
			} else {
				capsFlag=false;
			}

		}
		void getControlStatus() {
			if ((GetKeyState(VK_LCONTROL) & 0x8000) || (GetKeyState(VK_RCONTROL) & 0x8000)) {
//    		printf("Control key is downnnn");
				controlFlag=true;
			}

		}
	public:
		char getCharMapping(int keyCode,SpecialCharacters *specialCharactersObj) {


			shiftFlag =false;
			controlFlag=false;


			getShiftStatus();
			getCapsStatus();
			getControlStatus();

			int asciiValue= MapVirtualKeyA(keyCode,MAPVK_VK_TO_CHAR);

			if(controlFlag && asciiValue=='Q') exit(0);

			bool mainFlag=capsFlag^shiftFlag;

			if(shiftFlag) {
				if(specialCharactersObj->specialCharacters.find((char)asciiValue) !=specialCharactersObj->specialCharacters.end()) {
					return  specialCharactersObj->specialCharacters[(char)asciiValue];

				}
			}
			if(!mainFlag && asciiValue<='Z'  && asciiValue>='A') {
				asciiValue=asciiValue-'A'+'a';
			}
			return asciiValue;

		}

};
