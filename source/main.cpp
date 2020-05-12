#include <nds.h>

#include <stdio.h>

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	extern void dsiOnly(void);
	dsiOnly();

	consoleDemoInit();

	iprintf("Hello DSi world!\n");

	while(1) {
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
	}

	return 0;
}
