#pragma once
#include "manager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_syswm.h>
#include<imm.h>
#pragma comment(lib,"imm32.lib")

class InputMethodManager : public Manager<InputMethodManager>
{
    friend class Manager<InputMethodManager>;
public:
    // 保存当前输入法并设置为英文
    bool SetEnglishInput(SDL_Window* window) {
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);

        if (SDL_GetWindowWMInfo(window, &wmInfo)) {
            HWND hwnd = wmInfo.info.win.window;

            // 保存原来的输入法
            originalLayout = GetKeyboardLayout(0);
            isLayoutChanged = true;

            // 设置为英文输入法
            HKL englishLayout = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE);
            if (englishLayout) {
                ActivateKeyboardLayout(englishLayout, KLF_SETFORPROCESS);
                ImmAssociateContextEx(hwnd, NULL, IACE_DEFAULT);
                return true;
            }
        }
        return false;
    }

    void RestoreInputMethod() {
        if (isLayoutChanged && originalLayout) {
            ActivateKeyboardLayout(originalLayout, KLF_SETFORPROCESS);
            isLayoutChanged = false;
        }
    }

protected:
    InputMethodManager();
    ~InputMethodManager();

private:
    HKL originalLayout;
    bool isLayoutChanged;

   

};