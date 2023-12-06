#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define NUM_KEYS 512 // 2^9

HHOOK g_hHook = NULL;
ma_engine engine;
unsigned short isKeyPressed[NUM_KEYS] = {0}; // bool array
volatile int g_exitRequested = 0;
char soundpack[100];

struct HashMap {
	int key;
	char *data;
} HashMap;

void SignalHandler(int signum) {
	if (signum == SIGINT) {
		// clean up
		UnhookWindowsHookEx(g_hHook);
		ma_engine_uninit(&engine);
		exit(0);
	}
}

void ma_PlaySound(char *filePath) {
	ma_engine_play_sound(&engine, filePath, NULL);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		KBDLLHOOKSTRUCT *pKeyStruct = (KBDLLHOOKSTRUCT *)lParam;

		char filepath[100];
		sprintf(filepath, "sounds/%s/", soundpack);

		if (wParam == WM_KEYDOWN) {
			if (pKeyStruct->vkCode == VK_MENU) {
				printf("alt pressed\n");
			}
			if (isKeyPressed[pKeyStruct->vkCode]) {
				return CallNextHookEx(g_hHook, nCode, wParam, lParam);
			} else {
				isKeyPressed[pKeyStruct->vkCode] = 1;
			}

			printf("Virtual key code: %lu\n", pKeyStruct->vkCode);

			switch (pKeyStruct->vkCode) {
				case 65: // a
					strcat(filepath, "a.wav");
					break;
				case 66: // b
					strcat(filepath, "b.wav");
					break;
				case 67: // c
					strcat(filepath, "c.wav");
					break;
				case 68: // d
					strcat(filepath, "d.wav");
					break;
				case 69: // e
					strcat(filepath, "e.wav");
					break;
				case 70: // f
					strcat(filepath, "f.wav");
					break;
				case 71: // g
					strcat(filepath, "g.wav");
					break;
				case 72: // h
					strcat(filepath, "h.wav");
					break;
				case 73: // i
					strcat(filepath, "i.wav");
					break;
				case 74: // j
					strcat(filepath, "j.wav");
					break;
				case 75: // k
					strcat(filepath, "k.wav");
					break;
				case 76: // l
					strcat(filepath, "l.wav");
					break;
				case 77: // m
					strcat(filepath, "m.wav");
					break;
				case 78: // n
					strcat(filepath, "n.wav");
					break;
				case 79: // o
					strcat(filepath, "o.wav");
					break;
				case 80: // p
					strcat(filepath, "p.wav");
					break;
				case 81: // q
					strcat(filepath, "q.wav");
					break;
				case 82: // r
					strcat(filepath, "r.wav");
					break;
				case 83: // s
					strcat(filepath, "s.wav");
					break;
				case 84: // t
					strcat(filepath, "t.wav");
					break;
				case 85: // u
					strcat(filepath, "u.wav");
					break;
				case 86: // v
					strcat(filepath, "v.wav");
					break;
				case 87: // w
					strcat(filepath, "w.wav");
					break;
				case 88: // x
					strcat(filepath, "x.wav");

					break;
				case 89: // y
					strcat(filepath, "y.wav");

					break;
				case 90: // z
					strcat(filepath, "z.wav");

					break;
				case 32: // spacebar
					strcat(filepath, "space.wav");

					break;
				case 13: // enter
					strcat(filepath, "enter.wav");
					break;
				case 20: // capslock
					strcat(filepath, "capslock.wav");
					break;
				case 219: // [
					strcat(filepath, "[.wav");

					break;
				case 221: // ]
					strcat(filepath, "].wav");

					break;
				case 8: // backspace
					strcat(filepath, "[.wav");

					break;
				case 160:
					strcat(filepath, "[.wav");

					break;
				case 161: // right shift
					strcat(filepath, "[.wav");

					break;
				case 9: // tab
					strcat(filepath, "[.wav");

					break;
				case 164: // left alt
					strcat(filepath, "[.wav");

					break;
			}
		} else if (wParam == WM_KEYUP) {
			isKeyPressed[pKeyStruct->vkCode] = 0;
			strcat(filepath, "keyup.wav");

		} else if (wParam == WM_SYSKEYDOWN) { // for alt and other sys keys
			if (isKeyPressed[pKeyStruct->vkCode]) {
				return CallNextHookEx(g_hHook, nCode, wParam, lParam);
			} else {
				isKeyPressed[pKeyStruct->vkCode] = 1;
			}

			printf("wParam: %llu\n", wParam);
			strcat(filepath, "tab.wav");

		} else if (wParam == WM_SYSKEYUP) {
			isKeyPressed[pKeyStruct->vkCode] = 0;
			strcat(filepath, "keyup.wav");
		}
		ma_PlaySound(filepath);
	}

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

void print_usage() {
	printf("Usage: `./SpeedThock.exe <soundpack> <volume>`\n");
	printf("<volume> must range from 0-100\n");
}

int main(int argc, char **argv) {
	float volume;
	if (argc >= 3) {
		volume = atof(argv[1]);
		if (volume < 0.0 || volume > 100.0) {
			print_usage();
			exit(1);
		}
		volume /= 100;
		printf("volume: %0.2f\n", volume);
		strcpy(soundpack, argv[2]);
	} else {
		print_usage();
	}

	const char *ascii_art = ANSI_COLOR_RED
		" ____                      _ _____ _                _    \n"
		"/ ___| _ __   ___  ___  __| |_   _| |__   ___   ___| | __\n"
		"\\___ \\| '_ \\ / _ \\/ _ \\/ _` | | | | '_ \\ / _ \\ / __| |/ /\n"
		" ___) | |_) |  __/  __/ (_| | | | | | | | (_) | (__|   < \n"
		"|____/| .__/ \\___|\\___|\\__,_| |_| |_| |_|\\___/ \\___|_|\\_\\\n"
		"      |_|                                                "
		" " ANSI_COLOR_RESET;
	printf("%s\n", ascii_art);

	ma_result result;
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		return -1;
	}

	ma_engine_set_volume(&engine, volume);

	signal(SIGINT, SignalHandler);

	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc,
							   GetModuleHandle(NULL), 0);
	if (g_hHook == NULL) {
		printf("Failed to set windows keyboard hook.\n");
		return 1;
	}

	while (!g_exitRequested) {
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			printf("GetMessage return true i guess\n");
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			printf("What\n");
		}
	}

	UnhookWindowsHookEx(g_hHook);
	ma_engine_uninit(&engine);

	return 0;
}
