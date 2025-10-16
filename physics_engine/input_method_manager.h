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
    // ���浱ǰ���뷨������ΪӢ��
    bool SetEnglishInput(SDL_Window* window) {
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);

        if (SDL_GetWindowWMInfo(window, &wmInfo)) {
            HWND hwnd = wmInfo.info.win.window;

            // ����ԭ�������뷨
            originalLayout = GetKeyboardLayout(0);
            isLayoutChanged = true;

            // ����ΪӢ�����뷨
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