#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>
#include <windows.h>

HHOOK g_hHook = NULL;
ma_engine engine;

void ma_PlaySound(char* filePath) {
  ma_engine_play_sound(&engine, filePath, NULL);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode >= 0) {
    KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
    
  if (wParam == WM_KEYDOWN) {
      printf("Virtual key code: %lu\n", pKeyStruct->vkCode);

      if (pKeyStruct->vkCode == 27) {
        UnhookWindowsHookEx(g_hHook);
        ma_engine_uninit(&engine);
        exit(0);
      }
      switch (pKeyStruct->vkCode) {
        case 65: // a
          ma_PlaySound("sounds/nk-cream/a.wav");
        case 66: // b
        case 67: // c
        case 68: // d
        case 69: // e
        case 70: // f
        case 71: // g
        case 72: // h
        case 73: // i
        case 74: // j
        case 75: // k
        case 76: // l
        case 77: // m
        case 78: // n
        case 79: // o
        case 80: // p
        case 81: // q
        case 82: // r
        case 83: // s
        case 84: // t
        case 85: // u
        case 86: // v
        case 87: // w
        case 88: // x
        case 89: // y
        case 90: // z
          break;      
      }
      // if (pKeyStruct->vkCode == 60) {
      //   PlaySound(&engine);
      // }
      ma_PlaySound("sounds/nk-cream/a.wav");
    }
  }

  return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

int main(void) {
  printf("Hello, miniaudio\n");

  ma_result result;
  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    return -1;
  }

  g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
  if (g_hHook == NULL) {
    printf("Failed to set windows keyboard hook.\n");
    return 1;
  }

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    printf("GetMessage return true i guess\n");
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(g_hHook);
  ma_engine_uninit(&engine);
  
  return 0;
}
