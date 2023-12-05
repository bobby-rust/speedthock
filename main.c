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
char *soundpack;

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

    char buffer[100];
    sprintf(buffer, "sounds/%s/", soundpack);
    char filepath[100];

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
        strcat_s(filepath, "a.wav");
        ma_PlaySound(filepath);
        break;
      case 66: // b
        ma_PlaySound("sounds/nk-cream/b.wav");
        break;
      case 67: // c
        ma_PlaySound("sounds/nk-cream/c.wav");
        break;
      case 68: // d
        ma_PlaySound("sounds/nk-cream/d.wav");
        break;
      case 69: // e
        ma_PlaySound("sounds/nk-cream/e.wav");
        break;
      case 70: // f
        ma_PlaySound("sounds/nk-cream/f.wav");
        break;
      case 71: // g
        ma_PlaySound("sounds/nk-cream/g.wav");
        break;
      case 72: // h
        ma_PlaySound("sounds/nk-cream/h.wav");
        break;
      case 73: // i
        ma_PlaySound("sounds/nk-cream/i.wav");
        break;
      case 74: // j
        ma_PlaySound("sounds/nk-cream/j.wav");
        break;
      case 75: // k
        ma_PlaySound("sounds/nk-cream/k.wav");
        break;
      case 76: // l
        ma_PlaySound("sounds/nk-cream/l.wav");
        break;
      case 77: // m
        ma_PlaySound("sounds/nk-cream/m.wav");
        break;
      case 78: // n
        ma_PlaySound("sounds/nk-cream/n.wav");
        break;
      case 79: // o
        ma_PlaySound("sounds/nk-cream/o.wav");
        break;
      case 80: // p
        ma_PlaySound("sounds/nk-cream/p.wav");
        break;
      case 81: // q
        ma_PlaySound("sounds/nk-cream/q.wav");
        break;
      case 82: // r
        ma_PlaySound("sounds/nk-cream/r.wav");
        break;
      case 83: // s
        ma_PlaySound("sounds/nk-cream/s.wav");
        break;
      case 84: // t
        ma_PlaySound("sounds/nk-cream/t.wav");
        break;
      case 85: // u
        ma_PlaySound("sounds/nk-cream/u.wav");
        break;
      case 86: // v
        ma_PlaySound("sounds/nk-cream/v.wav");
        break;
      case 87: // w
        ma_PlaySound("sounds/nk-cream/w.wav");
        break;
      case 88: // x
        ma_PlaySound("sounds/nk-cream/x.wav");
        break;
      case 89: // y
        ma_PlaySound("sounds/nk-cream/y.wav");
        break;
      case 90: // z
        ma_PlaySound("sounds/nk-cream/z.wav");
        break;
      case 32: // spacebar
        ma_PlaySound("sounds/nk-cream/space.wav");
        break;
      case 13: // enter
        ma_PlaySound("sounds/nk-cream/enter.wav");
        break;
      case 20: // capslock
        ma_PlaySound("sounds/nk-cream/caps lock.wav");
        break;
      case 219: // [
        ma_PlaySound("sounds/nk-cream/[.wav");
        break;
      case 221: // ]
        ma_PlaySound("sounds/nk-cream/].wav");
        break;
      case 8: // backspace
        ma_PlaySound("sounds/nk-cream/backspace.wav");
        break;
      case 160:
        ma_PlaySound("sounds/nk-cream/shift.wav");
        break;
      case 161: // right shift
        ma_PlaySound("sounds/nk-cream/shift.wav");
      case 9: // tab
        ma_PlaySound("sounds/nk-cream/tab.wav");
        break;
      case 164: // left alt
        ma_PlaySound("sounds/nk-cream/a.wav");
      }
    } else if (wParam == WM_KEYUP) {
      isKeyPressed[pKeyStruct->vkCode] = 0;
      printf("key up\n");
      ma_PlaySound("sounds/nk-cream/a-up.wav");
    } else if (wParam == WM_SYSKEYDOWN) { // for alt and other sys keys
      if (isKeyPressed[pKeyStruct->vkCode]) {
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
      } else {
        isKeyPressed[pKeyStruct->vkCode] = 1;
      }

      printf("wParam: %llu\n", wParam);
      ma_PlaySound("sounds/nk-cream/tab.wav");
    } else if (wParam == WM_SYSKEYUP) {
      isKeyPressed[pKeyStruct->vkCode] = 0;
      ma_PlaySound("sounds/nk-cream/a-up.wav");
    }
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
    soundpack = argv[2];
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

  g_hHook =
      SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
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
