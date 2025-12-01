#pragma once
#include <windows.h>
int rg_main();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
  switch(message){
  case WM_DESTROY:
  PostQuitMessage(0);
  break;
  default:
  return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

#ifdef RG_UTF
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow){
  RG_Prog_Work = 1;
  MSG msg;
  WNDCLASSEXW wcex{0};
  // Заполнить поля структуры
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = L"RGmenu";
  // Ругистрировать класс окна
  RegisterClassExW(&wcex);
  // Создать окно и отобразить
  HWND hWnd = CreateWindowW(L"RGmenu", L"Powered By Rinegine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
  ShowWindow(hWnd, nCmdShow);
  int errcode = rg_main();
  //errcode 
  //thread rgmain([&](){errcode = rg_main(); RG_Prog_Work = 0;});
  /*while(GetMessage(&msg, nullptr, 0, 0)){
    DispatchMessage(&msg);
  }*/
  //if(!rgmain.joinable())return -1;
  //rgmain.join();
  //return errcode;
  return errcode;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
  RG_Debug::addl(RG_LOG_CRITICAL, "You are using RG_UTF but did not specify this during compilation. Please add 'utf' to your rgset file.");
  return -1;
}

#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
  RG_Prog_Work = 1;
  MSG msg;
  WNDCLASSEXA wcex{0};
  // Заполнить поля структуры
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = "RGmenu";
  // Ругистрировать класс окна
  RegisterClassExA(&wcex);
  // Создать окно и отобразить
  HWND hWnd = CreateWindowA("RGmenu", "Powered By Rinegine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
  ShowWindow(hWnd, nCmdShow);
  int errcode = rg_main();
  //errcode 
  //thread rgmain([&](){errcode = rg_main(); RG_Prog_Work = 0;});
  /*while(GetMessage(&msg, nullptr, 0, 0)){
    DispatchMessage(&msg);
  }*/
  //if(!rgmain.joinable())return -1;
  //rgmain.join();
  //return errcode;
  return errcode;
}
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int){
  RG_Debug::addl(RG_LOG_CRITICAL, "You are not using RG_UTF, but you specified it at compile time. Please remove \"utf\" from your rgset file or define RG_UTF in the main file.");
  return -1;
}

#endif


