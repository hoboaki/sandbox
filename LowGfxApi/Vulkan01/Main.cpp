// 文字コード：UTF-8
#include <ae/base/Console.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>

extern int WINAPI DemoWinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);

//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine,
    int nCmdShow) {
#if 0
    return DemoWinMain(hInstance, hPrevInstance, pCmdLine, nCmdShow);
#else
    // グラフィックスシステムインスタンス作成
    ::ae::gfx_low::System gfxLowSystem(
        ::ae::gfx_low::SystemCreateInfo().SetDebugLevel(
            ::ae::gfx_low::SystemDebugLevel::Normal));

    // Queue 構成選択
    gfxLowSystem.DumpAllPhysicalDeviceInfo();

    return 0;
#endif
}
// EOF
