#include <nds.h>
#include "dsiOnly_top.h"
#include "dsiOnly_bot.h"

static void dsiOnly_setBrightness(u8 screen, s8 bright) {
	u16 mode = 1 << 14;

	if (bright < 0) {
		mode = 2 << 14;
		bright = -bright;
	}
	if (bright > 31) {
		bright = 31;
	}
	*(u16*)(0x0400006C + (0x1000 * screen)) = bright + mode;
}

void dsiOnly(void) {
	if (isDSiMode()) return;	// Proceed running on DSi

	*(u16*)0x0400006C |= BIT(14);
	*(u16*)0x0400006C &= BIT(15);
	dsiOnly_setBrightness(0, 31);
	dsiOnly_setBrightness(1, 31);

	videoSetMode(MODE_4_2D);
	videoSetModeSub(MODE_4_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_LCD);

	// Display DSi Only screen
	int bg3 = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 1, 0);
	bgSetScroll(bg3, 0, 0);
	decompress(dsiOnly_topBitmap, bgGetGfxPtr(bg3), LZ77Vram);

	int bg3sub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 1, 0);
	bgSetScroll(bg3sub, 0, 0);
	decompress(dsiOnly_botBitmap, bgGetGfxPtr(bg3sub), LZ77Vram);

	dsiOnly_setBrightness(0, 0);
	dsiOnly_setBrightness(1, 0);

	while (1) {
		swiWaitForVBlank();
	}
}