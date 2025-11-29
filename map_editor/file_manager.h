#pragma once
#include "manager.h"

#include <windows.h>
#include <shobjidl.h>
#include <iostream>
#include <string>

class FileManager:public Manager<FileManager>
{
	friend class Manager<FileManager>;
protected:
	FileManager();
	~FileManager();
public:
    std::wstring open_file()
    {
        file_path = OpenFileDialogModern();
        return file_path;
    }

    std::wstring get_current_file()
    {
        if (file_path.empty()) open_file();
        return file_path;
    }

private:
    std::wstring file_path;

    std::wstring OpenFileDialogModern() {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(hr)) return L"";

        std::wstring result;
        IFileOpenDialog* pFileOpen;

        // 创建文件对话框对象
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr)) {
            // 设置文件类型过滤器
            COMDLG_FILTERSPEC fileTypes[] = {
                {L"csv文件", L"*.csv"},
            };

            hr = pFileOpen->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);

            // 设置默认选择的文件类型索引（从1开始）
            if (SUCCEEDED(hr)) {
                hr = pFileOpen->SetFileTypeIndex(1); // 默认选择第一种类型
            }

            // 设置默认扩展名（当用户没有输入扩展名时自动添加）
            if (SUCCEEDED(hr)) {
                hr = pFileOpen->SetDefaultExtension(L"csv");
            }

            // 显示对话框
            hr = pFileOpen->Show(NULL);

            if (SUCCEEDED(hr)) {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    if (SUCCEEDED(hr)) {
                        result = pszFilePath;
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
        return result;
    }
};

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}