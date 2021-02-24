#include "base64.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
using namespace std;

#define FPS 60
#define PROCESS_DELAY 250

#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2main.lib")
#pragma comment (lib, "SDL2_image.lib")
#pragma comment (lib, "SDL2_ttf.lib")

#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")

#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

string strBase64QRCodeImage = "iVBORw0KGgoAAAANSUhEUgAAAZAAAAGQBAMAAABykSv/AAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAHlBMVEX///8Bd9cKfNgxkd8xkd8Oftn8/v9Em+L6/P4xkd+3YNCgAAAAAWJLR0QAiAUdSAAAAAlwSFlzAAAXEQAAFxEByibzPwAAA4tJREFUeNrt2rGR2zAQBVCyA7IDzVwDmnEFlzhWC5c4vhbcgUv2jBLzgOUCsOWzRb4fcagl9j/EmiYRERERERGRj1m7cilny2Pm8ouRt/csw3VAQEBAQEBAYsjLl9283gdunwrprBNArtNu3sqBuWwUf5egs4HhOiAgICAgICBHh6xFrsmX97dL+djHW8Jty5/UAQEBAQEBATkxJK6cQKqBxP9H9woCAgICAgJyYkj52TJFabZfWwMgICAgICAgD4CU//t4/7eQkTofvwyTQZrZSGNebBqvAwICAgIC8gjI12+7+X4f+PGpkPE63Y0unwoZrzP4Zbnwbz2CgICAgICA/F3I7f+C3KYHZL4ftXnc1EguqNlzGejwkICAgICAgIA8ByRZuIQD8e45aV9exRQOxNc2tRaDgICAgICAHAwyDxxS8fq2dDZqXjgICAgICAjIKSCbH8rHKptG5XnV27WVkWtLFoOAgICAgICcAtLcMncfPTawtmarviAgICAgICDngVSm+Mvh3dkFJYf1XxsICAgICAjI4SDNRnNSIxnoTHyZgyVBQEBAQEBATgKZ10aau7NGiWkzUN0VCAgICAgIyCkg5Xj8throax/XqNInjUuCgICAgICAHB2yqZEsnJMaTWlyQtVh5AZBQEBAQEBAjgiJa2TtY3S5O6vcvMzmYhAQEBAQEJDjQuIvk0NiSNMUb5vCxdm9goCAgICAgJwCkixck7fxQHxuclfZvY58BgICAgICAnJcyHCWsEbszxol525m52QxCAgICAgIyBEhVcpGzUOqhX3nxpC1dQIICAgICAjI0SGbH0baJ7Nr32fl4qxDz2WCgICAgICAHAkS12gOxCl3x9fWPCELCAgICAgIyCkgmx/Kx87K5dHV23hgmJddEAgICAgICMjBICNJjq4ehy9oaW2rLh4EBAQEBATkuJC1K5dfH8zlb83dCW8N3y7hYdUJICAgICAgIDHk5ctuXu8DtyeBXKfdvG0GBo/eg2Ttm7cCAgICAgICcjZIueWaQPpqLH2N1v1szp3LE0BAQEBAQEBA9ntutjQrl7PNq9gcVn0GAgICAgICAtLfPlsYnxA/xlIQEBAQEBCQTkj5N5T3Z4WEeUsGfrNGnJg3td6CgICAgIA8DvL1226+3wd+PAmkmcvJIJv08dbks5hXvgUBAQEBAQEZh9z+f4iIiIiIiIjIIfITgQWJuUiA380AAAAASUVORK5CYII=";

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

	string strFontPath = "C:/Windows/Fonts/";
	TTF_Font* pFontEmoji = TTF_OpenFont((strFontPath + "msyh.ttc").c_str(), 200);

	if (!pFontEmoji)
	{
		pFontEmoji = TTF_OpenFont("msyh.ttc", 200);
		if (!pFontEmoji)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "字体文件加载失败", "检测到字体文件默认路径错误：C:\\Windows\\Fonts\\msyh.ttc\n\n• 以下方式可能修复程序：\n      进入系统盘对应字体目录复制此字体文件或联网下载此字体文件至程序同一目录下，\n并重启程序，注意确保字体文件名为：msyh.ttc\n\n联系开发者：Voidmatrix@outlook.com", nullptr);
			IMG_Quit();
			TTF_Quit();
			SDL_Quit();
			return -1;
		}
		else
			strFontPath = "";
	}

	TTF_Font* pFont_1 = TTF_OpenFont((strFontPath + "msyh.ttc").c_str(), 35);
	TTF_Font* pFont_2 = TTF_OpenFont((strFontPath + "msyh.ttc").c_str(), 25);
	TTF_Font* pFont_3 = TTF_OpenFont((strFontPath + "msyh.ttc").c_str(), 20);

	SDL_Window* pWindow = SDL_CreateWindow("蓝屏模拟器", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_Renderer* pWRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_ShowCursor(0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

	SDL_Color clrText = { 255, 255, 255, 255 };

	int iProcessValue = 0, iTimerProcess = 0;

	SDL_Surface* pSurfaceQRCode = IMG_Load_RW(SDL_RWFromMem((void*)(base64_decode(strBase64QRCodeImage).c_str()), strBase64QRCodeImage.length()), 1);
	SDL_Surface* pSurfaceEmoji = TTF_RenderUTF8_Blended(pFontEmoji, ":(", clrText);
	SDL_Surface* pSurfaceText_1 = TTF_RenderUTF8_Blended(pFont_1, "你的电脑遇到问题，需要重新启动。", clrText);
	SDL_Surface* pSurfaceText_2 = TTF_RenderUTF8_Blended(pFont_1, "我们只收集某些错误信息，然后为你重新启动。", clrText);
	SDL_Surface* pSurfaceText_3 = TTF_RenderUTF8_Blended(pFont_2, "有关此问题的详细信息和可能的解决方法，请访问", clrText);
	SDL_Surface* pSurfaceText_4 = TTF_RenderUTF8_Blended(pFont_2, "http://windows.com/stopcode", clrText);
	SDL_Surface* pSurfaceText_5 = TTF_RenderUTF8_Blended(pFont_3, "如果致电支持人员，请向他们提供以下信息：", clrText);
	SDL_Surface* pSurfaceText_6 = TTF_RenderUTF8_Blended(pFont_3, "终止代码：PDC_WATCHDOG_TIMEOUT", clrText);
	SDL_Surface* pSurfaceText_7 = TTF_RenderUTF8_Blended(pFont_1, "完成", clrText);
	SDL_Surface* pSurfaceTextProcess = TTF_RenderUTF8_Blended(pFont_1, (to_string(iProcessValue) + "%").c_str(), clrText);

	TTF_CloseFont(pFontEmoji);
	TTF_CloseFont(pFont_2);
	TTF_CloseFont(pFont_3);

	SDL_Texture* pTextureQRCode = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceQRCode);
	SDL_Texture* pTextureEmoji = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceEmoji);
	SDL_Texture* pTextureText_1 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_1);
	SDL_Texture* pTextureText_2 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_2);
	SDL_Texture* pTextureText_3 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_3);
	SDL_Texture* pTextureText_4 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_4);
	SDL_Texture* pTextureText_5 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_5);
	SDL_Texture* pTextureText_6 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_6);
	SDL_Texture* pTextureText_7 = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceText_7);
	SDL_Texture* pTextureTextProcess = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceTextProcess);

	SDL_Rect rcQRCode = { 175, 535, 200, 200 };
	SDL_Rect rcEmoji = { 175, 50, pSurfaceEmoji->w, pSurfaceEmoji->h };
	SDL_Rect rcText_1 = { 175, 330, pSurfaceText_1->w, pSurfaceText_1->h };
	SDL_Rect rcText_2 = { 175, 380, pSurfaceText_2->w, pSurfaceText_2->h };
	SDL_Rect rcText_3 = { rcQRCode.x + rcQRCode.w + 25, rcQRCode.y - 17, pSurfaceText_3->w, pSurfaceText_4->h };
	SDL_Rect rcText_4 = { rcQRCode.x + rcQRCode.w + 25, rcQRCode.y - 17 + 45, pSurfaceText_4->w, pSurfaceText_4->h };
	SDL_Rect rcText_5 = { rcQRCode.x + rcQRCode.w + 25, rcQRCode.y + 100, pSurfaceText_5->w, pSurfaceText_5->h };
	SDL_Rect rcText_6 = { rcQRCode.x + rcQRCode.w + 25, rcQRCode.y + 135, pSurfaceText_6->w, pSurfaceText_6->h };
	SDL_Rect rcTextProcess = { 175, 458, pSurfaceTextProcess->w, pSurfaceTextProcess->h };
	SDL_Rect rcText_7 = { rcTextProcess.x + rcTextProcess.w + 18, rcTextProcess.y, pSurfaceText_7->w, pSurfaceText_7->h };

	SDL_FreeSurface(pSurfaceQRCode);
	SDL_FreeSurface(pSurfaceEmoji);
	SDL_FreeSurface(pSurfaceText_1);
	SDL_FreeSurface(pSurfaceText_2);
	SDL_FreeSurface(pSurfaceText_3);
	SDL_FreeSurface(pSurfaceText_4);
	SDL_FreeSurface(pSurfaceText_5);
	SDL_FreeSurface(pSurfaceText_6);
	SDL_FreeSurface(pSurfaceText_7);
	SDL_FreeSurface(pSurfaceTextProcess);

	SDL_SetRenderDrawColor(pWRenderer, 1, 119, 215, 255);

	while (true)
	{
		unsigned int _start = SDL_GetTicks();

		SDL_RenderClear(pWRenderer);

		SDL_Event _event;
		if (SDL_PollEvent(&_event) && _event.type == SDL_QUIT)
			break;

		if (iTimerProcess >= PROCESS_DELAY)
		{
			iProcessValue = iProcessValue < 100 ? iProcessValue + 10 : 0;
			iTimerProcess = 0;

			pSurfaceTextProcess = TTF_RenderUTF8_Blended(pFont_1, (to_string(iProcessValue) + "%").c_str(), clrText);
			SDL_DestroyTexture(pTextureTextProcess);
			pTextureTextProcess = SDL_CreateTextureFromSurface(pWRenderer, pSurfaceTextProcess);
			rcTextProcess.w = pSurfaceTextProcess->w, rcTextProcess.h = pSurfaceTextProcess->h;
			SDL_FreeSurface(pSurfaceTextProcess);
			rcText_7.x = rcTextProcess.x + rcTextProcess.w + 18;
		}

		iTimerProcess++;

		SDL_RenderCopy(pWRenderer, pTextureQRCode, nullptr, &rcQRCode);
		SDL_RenderCopy(pWRenderer, pTextureEmoji, nullptr, &rcEmoji);
		SDL_RenderCopy(pWRenderer, pTextureText_1, nullptr, &rcText_1);
		SDL_RenderCopy(pWRenderer, pTextureText_2, nullptr, &rcText_2);
		SDL_RenderCopy(pWRenderer, pTextureText_3, nullptr, &rcText_3);
		SDL_RenderCopy(pWRenderer, pTextureText_4, nullptr, &rcText_4);
		SDL_RenderCopy(pWRenderer, pTextureText_5, nullptr, &rcText_5);
		SDL_RenderCopy(pWRenderer, pTextureText_6, nullptr, &rcText_6);
		SDL_RenderCopy(pWRenderer, pTextureText_7, nullptr, &rcText_7);
		SDL_RenderCopy(pWRenderer, pTextureTextProcess, nullptr, &rcTextProcess);

		SDL_RenderPresent(pWRenderer);

		unsigned int _end = SDL_GetTicks();

		if (_end - _start < 1000 / FPS)
			SDL_Delay(1000 / FPS - (_end - _start));
	}

	SDL_DestroyRenderer(pWRenderer);
	SDL_DestroyWindow(pWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}