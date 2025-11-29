#define SDL_MAIN_HANDLED
//#include <fstream>
//#include <filesystem>
//
//#include "total_manager.h"
//#include "file_manager.h"
//
//#pragma comment(lib, "ole32.lib")
//
//int main(int argc, char** argv) 
//{
//    // 设置本地化（使用系统默认）
//    std::locale::global(std::locale(""));
//    std::wcout.imbue(std::locale());
//
//    TotalManager::instance()->run(argc, argv);
//    
//    return 0;
//}

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <iostream>
#include <locale>

// 定义宏来抑制弃用警告
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

// 输入区域结构体
struct InputField {
    SDL_Rect rect;
    std::string text;
    bool isActive;
    SDL_Color bgColor;
    SDL_Color textColor;
    SDL_Color borderColor;
    std::string placeholder;
    bool isPassword;

    bool cursorVisible;
    Uint32 cursorTimer;
    int cursorPosition;
};

class InputManager {
private:
    std::vector<InputField> fields;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool fontLoaded;

public:
    InputManager(SDL_Renderer* renderer) : renderer(renderer), font(nullptr), fontLoaded(false) {
        // 设置本地化
        std::locale::global(std::locale(""));

        // 设置SDL文本输入提示
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

        // 加载支持中文的字体
        loadChineseFont();

        createDefaultFields();
    }

    ~InputManager() {
        if (font) {
            TTF_CloseFont(font);
        }
        TTF_Quit();
    }

private:
    void loadChineseFont() {
        if (TTF_Init() == -1) {
            std::cout << "TTF_Init失败: " << TTF_GetError() << std::endl;
            return;
        }

        // 更详细地尝试加载中文字体
        const char* fontPaths[] = {
            // Windows 路径
            "C:/Windows/Fonts/simhei.ttf",           // 黑体
            "C:/Windows/Fonts/simsun.ttc",           // 宋体
            "C:/Windows/Fonts/msyh.ttc",             // 微软雅黑
            "C:/Windows/Fonts/msyhbd.ttc",           // 微软雅黑粗体
            "C:/Windows/Fonts/simkai.ttf",           // 楷体
            "C:/Windows/Fonts/simfang.ttf",          // 仿宋

            // Linux 路径
            "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",
            "/usr/share/fonts/truetype/arphic/ukai.ttc",
            "/usr/share/fonts/truetype/arphic/uming.ttc",
            "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf",
            "/usr/share/fonts/truetype/noto/NotoSansCJK-Regular.ttc",

            // macOS 路径
            "/System/Library/Fonts/PingFang.ttc",
            "/System/Library/Fonts/STHeiti Light.ttc",
            "/System/Library/Fonts/STHeiti Medium.ttc",
            "/Library/Fonts/Arial Unicode.ttf",
            "/System/Library/Fonts/Hiragino Sans GB.ttc",

            // 当前目录和常见位置
            "./simhei.ttf",
            "./wqy-microhei.ttc",
            "./msyh.ttc",
            "fonts/simhei.ttf",
            "fonts/wqy-microhei.ttc",
            nullptr
        };

        std::cout << "正在尝试加载中文字体..." << std::endl;

        for (int i = 0; fontPaths[i] != nullptr; i++) {
            std::cout << "尝试字体路径: " << fontPaths[i] << std::endl;
            font = TTF_OpenFont(fontPaths[i], 20);
            if (font) {
                std::cout << "✓ 成功加载字体: " << fontPaths[i] << std::endl;

                // 测试字体是否支持中文显示
                if (testFontChineseSupport()) {
                    fontLoaded = true;
                    std::cout << "✓ 字体支持中文显示" << std::endl;
                    return;
                }
                else {
                    std::cout << "✗ 字体不支持中文显示，继续尝试..." << std::endl;
                    TTF_CloseFont(font);
                    font = nullptr;
                }
            }
            else {
                std::cout << "✗ 无法加载字体: " << TTF_GetError() << std::endl;
            }
        }

        // 如果所有指定字体都失败，尝试系统默认字体
        std::cout << "尝试系统默认字体..." << std::endl;
        font = TTF_OpenFontIndex(nullptr, 20, 0);
        if (font) {
            std::cout << "使用系统默认字体" << std::endl;
            if (testFontChineseSupport()) {
                fontLoaded = true;
            }
        }
        else {
            std::cout << "警告: 无法加载任何字体，文本将无法显示" << std::endl;
            fontLoaded = false;
        }
    }

    bool testFontChineseSupport() {
        // 测试渲染中文字符
        const char* testText = "中文测试";
        SDL_Color color = { 0, 0, 0, 255 };

        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, testText, color);
        if (surface) {
            bool success = (surface->w > 0 && surface->h > 0);
            SDL_FreeSurface(surface);
            return success;
        }
        return false;
    }

public:
    void createDefaultFields() {
        // 使用UTF-8编码的中文文本
        InputField usernameField = {
            {100, 100, 350, 35},
            "",
            true,
            {255, 255, 255, 255},
            {0, 0, 0, 255},
            {100, 100, 100, 255},
            "请输入用户名",
            false,
            true,
            SDL_GetTicks(),
            0
        };

        InputField passwordField = {
            {100, 160, 350, 35},
            "",
            false,
            {255, 255, 255, 255},
            {0, 0, 0, 255},
            {100, 100, 100, 255},
            "请输入密码",
            true,
            false,
            SDL_GetTicks(),
            0
        };

        InputField emailField = {
            {100, 220, 350, 35},
            "",
            false,
            {255, 255, 255, 255},
            {0, 0, 0, 255},
            {100, 100, 100, 255},
            "请输入邮箱地址",
            false,
            false,
            SDL_GetTicks(),
            0
        };

        fields.push_back(usernameField);
        fields.push_back(passwordField);
        fields.push_back(emailField);
    }

    void handleEvent(const SDL_Event& event) {
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                handleMouseClick(event.button.x, event.button.y);
            }
            break;

        case SDL_TEXTINPUT:
            handleTextInput(event.text.text);
            break;

        case SDL_KEYDOWN:
            handleKeyDown(event.key);
            break;
        }
    }

private:
    void handleMouseClick(int x, int y) {
        bool anyFieldActivated = false;

        for (auto& field : fields) {
            field.isActive = false;
        }

        for (auto& field : fields) {
            if (x >= field.rect.x && x <= field.rect.x + field.rect.w &&
                y >= field.rect.y && y <= field.rect.y + field.rect.h) {
                field.isActive = true;
                anyFieldActivated = true;

                field.cursorTimer = SDL_GetTicks();
                field.cursorVisible = true;
                field.cursorPosition = field.text.length();

                std::cout << "激活输入框: " << field.text << std::endl;
                break;
            }
        }

        if (anyFieldActivated) {
            if (!SDL_IsTextInputActive()) {
                SDL_StartTextInput();
            }
        }
        else {
            SDL_StopTextInput();
        }
    }

    void handleTextInput(const char* text) {
        for (auto& field : fields) {
            if (field.isActive) {
                std::cout << "收到输入: " << text << std::endl;

                // 直接使用SDL提供的UTF-8文本
                if (field.cursorPosition <= field.text.length()) {
                    field.text.insert(field.cursorPosition, text);
                    field.cursorPosition += strlen(text);
                }
                else {
                    field.text += text;
                    field.cursorPosition = field.text.length();
                }

                std::cout << "更新后文本: " << field.text << std::endl;
                break;
            }
        }
    }

    void handleKeyDown(const SDL_KeyboardEvent& key) {
        for (auto& field : fields) {
            if (field.isActive) {
                SDL_Keycode keycode = key.keysym.sym;

                switch (keycode) {
                case SDLK_BACKSPACE:
                    if (!field.text.empty() && field.cursorPosition > 0) {
                        // 对于UTF-8，需要删除整个字符而不是单个字节
                        int bytesToRemove = 1;

                        // 检查是否是UTF-8多字节字符的开始
                        if (field.cursorPosition >= 2) {
                            unsigned char prevChar = static_cast<unsigned char>(
                                field.text[field.cursorPosition - 1]);
                            if ((prevChar & 0xC0) == 0x80) { // 是多字节字符的后续字节
                                // 继续向前查找字符起始字节
                                for (int i = 2; i <= 4 && field.cursorPosition >= i; i++) {
                                    unsigned char checkChar = static_cast<unsigned char>(
                                        field.text[field.cursorPosition - i]);
                                    if ((checkChar & 0xC0) == 0xC0) { // 找到起始字节
                                        bytesToRemove = i;
                                        break;
                                    }
                                }
                            }
                        }

                        field.text.erase(field.cursorPosition - bytesToRemove, bytesToRemove);
                        field.cursorPosition -= bytesToRemove;
                    }
                    break;

                case SDLK_DELETE:
                    if (field.cursorPosition < field.text.length()) {
                        // 类似Backspace，但删除光标后的字符
                        int bytesToRemove = 1;
                        unsigned char nextChar = static_cast<unsigned char>(
                            field.text[field.cursorPosition]);

                        if ((nextChar & 0xC0) == 0xC0) { // 是多字节字符的起始字节
                            // 计算这个UTF-8字符的字节数
                            if ((nextChar & 0xE0) == 0xC0) bytesToRemove = 2;
                            else if ((nextChar & 0xF0) == 0xE0) bytesToRemove = 3;
                            else if ((nextChar & 0xF8) == 0xF0) bytesToRemove = 4;
                        }

                        field.text.erase(field.cursorPosition, bytesToRemove);
                    }
                    break;

                case SDLK_LEFT:
                    if (field.cursorPosition > 0) {
                        // UTF-8感知的光标左移
                        int bytesToMove = 1;
                        unsigned char prevChar = static_cast<unsigned char>(
                            field.text[field.cursorPosition - 1]);

                        if ((prevChar & 0xC0) == 0x80) { // 是多字节字符的后续字节
                            // 继续向前查找字符起始字节
                            for (int i = 2; i <= 4 && field.cursorPosition >= i; i++) {
                                unsigned char checkChar = static_cast<unsigned char>(
                                    field.text[field.cursorPosition - i]);
                                if ((checkChar & 0xC0) == 0xC0) { // 找到起始字节
                                    bytesToMove = i;
                                    break;
                                }
                            }
                        }

                        field.cursorPosition -= bytesToMove;
                    }
                    break;

                case SDLK_RIGHT:
                    if (field.cursorPosition < field.text.length()) {
                        // UTF-8感知的光标右移
                        int bytesToMove = 1;
                        unsigned char nextChar = static_cast<unsigned char>(
                            field.text[field.cursorPosition]);

                        if ((nextChar & 0xC0) == 0xC0) { // 是多字节字符的起始字节
                            // 计算这个UTF-8字符的字节数
                            if ((nextChar & 0xE0) == 0xC0) bytesToMove = 2;
                            else if ((nextChar & 0xF0) == 0xE0) bytesToMove = 3;
                            else if ((nextChar & 0xF8) == 0xF0) bytesToMove = 4;
                        }

                        field.cursorPosition += bytesToMove;
                    }
                    break;

                case SDLK_HOME:
                    field.cursorPosition = 0;
                    break;

                case SDLK_END:
                    field.cursorPosition = field.text.length();
                    break;

                case SDLK_TAB:
                    switchActiveField();
                    return;

                case SDLK_RETURN:
                    performSubmit();
                    break;

                case SDLK_c:
                    if (SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(field.text.c_str());
                    }
                    break;

                case SDLK_v:
                    if (SDL_GetModState() & KMOD_CTRL) {
                        if (SDL_HasClipboardText()) {
                            char* clipboardText = SDL_GetClipboardText();
                            if (clipboardText) {
                                field.text.insert(field.cursorPosition, clipboardText);
                                field.cursorPosition += strlen(clipboardText);
                                SDL_free(clipboardText);
                            }
                        }
                    }
                    break;
                }

                field.cursorTimer = SDL_GetTicks();
                field.cursorVisible = true;
                break;
            }
        }
    }

public:
    void switchActiveField() {
        int currentIndex = -1;
        for (int i = 0; i < fields.size(); ++i) {
            if (fields[i].isActive) {
                currentIndex = i;
                fields[i].isActive = false;
                break;
            }
        }

        if (currentIndex != -1) {
            int nextIndex = (currentIndex + 1) % fields.size();
            fields[nextIndex].isActive = true;
            fields[nextIndex].cursorPosition = fields[nextIndex].text.length();
            fields[nextIndex].cursorTimer = SDL_GetTicks();
            fields[nextIndex].cursorVisible = true;
        }
    }

    void performSubmit() {
        std::cout << "\n=== 表单提交 ===" << std::endl;
        for (int i = 0; i < fields.size(); ++i) {
            std::string displayText = fields[i].isPassword ?
                std::string(fields[i].text.length(), '*') : fields[i].text;
            std::cout << "字段 " << i << ": " << displayText << std::endl;
        }
        std::cout << "================\n" << std::endl;
    }

    void update() {
        Uint32 currentTime = SDL_GetTicks();
        for (auto& field : fields) {
            if (field.isActive && currentTime - field.cursorTimer > 500) {
                field.cursorVisible = !field.cursorVisible;
                field.cursorTimer = currentTime;
            }
        }
    }

    void render() {
        // 渲染说明文字
        if (fontLoaded) {
            renderText("SDL2 中文输入演示 - 点击输入框输入中文，Tab切换，Enter提交",
                10, 50, { 0, 0, 0, 255 });
            renderText("确保系统安装了中文字体(如黑体、微软雅黑等)",
                10, 70, { 100, 100, 100, 255 });
        }
        else {
            // 如果没有字体，显示英文提示
            renderText("SDL2 Input Demo - Click to input, Tab to switch, Enter to submit",
                10, 50, { 0, 0, 0, 255 });
            renderText("Chinese font not found, please install a Chinese font",
                10, 70, { 255, 0, 0, 255 });
        }

        for (auto& field : fields) {
            renderInputField(field);
        }
    }

private:
    void renderInputField(const InputField& field) {
        // 绘制背景
        SDL_SetRenderDrawColor(renderer,
            field.bgColor.r, field.bgColor.g, field.bgColor.b, field.bgColor.a);
        SDL_RenderFillRect(renderer, &field.rect);

        // 绘制边框
        if (field.isActive) {
            SDL_SetRenderDrawColor(renderer, 0, 120, 215, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer,
                field.borderColor.r, field.borderColor.g, field.borderColor.b, field.borderColor.a);
        }
        SDL_RenderDrawRect(renderer, &field.rect);

        // 绘制文本
        std::string displayText;
        SDL_Color textColor = field.textColor;

        if (field.text.empty() && !field.isActive) {
            displayText = field.placeholder;
            textColor = { 150, 150, 150, 255 };
        }
        else if (field.isPassword && !field.text.empty()) {
            displayText = std::string(field.text.length(), '*');
        }
        else {
            displayText = field.text;
        }

        if (!displayText.empty()) {
            renderText(displayText, field.rect.x + 8, field.rect.y + 8, textColor);
        }

        // 绘制光标
        if (field.isActive && field.cursorVisible) {
            renderCursor(field);
        }
    }

    void renderText(const std::string& text, int x, int y, SDL_Color color) {
        if (font && !text.empty()) {
            SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture) {
                    SDL_Rect dstRect = { x, y, surface->w, surface->h };
                    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
                    SDL_DestroyTexture(texture);
                }
                SDL_FreeSurface(surface);
            }
        }
        else if (!font) {
            // 如果没有字体，在控制台输出调试信息
            std::cout << "无法渲染文本（无字体）: " << text << std::endl;
        }
    }

    void renderCursor(const InputField& field) {
        int cursorX = field.rect.x + 8;
        if (!field.text.empty() && font) {
            // 计算光标前的文本
            std::string textBeforeCursor = field.text.substr(0, field.cursorPosition);
            if (field.isPassword && !textBeforeCursor.empty()) {
                textBeforeCursor = std::string(textBeforeCursor.length(), '*');
            }

            if (!textBeforeCursor.empty()) {
                int textWidth = 0;
                TTF_SizeUTF8(font, textBeforeCursor.c_str(), &textWidth, nullptr);
                cursorX += textWidth;
            }
        }

        SDL_Rect cursorRect = { cursorX, field.rect.y + 5, 2, field.rect.h - 10 };
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &cursorRect);
    }
};

int main(int argc, char* argv[]) {
    // 设置控制台支持中文输出
    std::locale::global(std::locale(""));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL初始化失败: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2中文输入演示",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 400,
        SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "窗口创建失败: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "渲染器创建失败: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    InputManager inputManager(renderer);
    SDL_StartTextInput();

    std::cout << "中文输入已启用" << std::endl;

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            inputManager.handleEvent(event);
        }

        inputManager.update();

        SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
        SDL_RenderClear(renderer);

        inputManager.render();

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}