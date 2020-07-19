// 文字コード：UTF-8
#include <ae/base/AppEvent.hpp>
#include <ae/base/Application.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/DisplayContext.hpp>
#include <ae/base/EntryPoint.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/SdkHeader.hpp>
#include <ae/gfx_low/Device.hpp>
#include <ae/gfx_low/DeviceCreateInfo.hpp>
#include <ae/gfx_low/QueueCreateInfo.hpp>
#include <ae/gfx_low/SwapchainCreateInfo.hpp>
#include <ae/gfx_low/SwapchainMaster.hpp>
#include <ae/gfx_low/SwapchainMasterCreateInfo.hpp>
#include <ae/gfx_low/System.hpp>
#include <ae/gfx_low/SystemCreateInfo.hpp>
#include <memory>

extern int WINAPI DemoWinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);

//------------------------------------------------------------------------------
int aemain(::ae::base::Application& app) {
    // コンソール出力
    AE_BASE_COUT_LINE_WITH_TIME("Adel runtime start.");

    // ディスプレイの作成
    ::ae::base::Display display =
        ::ae::base::Display(::ae::base::DisplayContext());

    // ディスプレイの表示
    display.show();

    // グラフィックスシステムインスタンス作成
    ::std::unique_ptr<::ae::gfx_low::System> gfxLowSystem(
        new ::ae::gfx_low::System(
            ::ae::gfx_low::SystemCreateInfo().SetDebugLevel(
                ::ae::gfx_low::SystemDebugLevel::Normal)));

    // Device & Queue 作成
    ::std::unique_ptr<::ae::gfx_low::Device> gfxLowDevice;
    {
        // デバッグダンプ
        gfxLowSystem->DumpAllPhysicalDeviceInfo();

        // Queue の作成情報を用意
        const int queueCount = 1;
        ::ae::gfx_low::QueueCreateInfo queueCreateInfos[queueCount];
        queueCreateInfos[0] =
            ::ae::gfx_low::QueueCreateInfo()
                .SetType(::ae::gfx_low::QueueType::Normal)
                .SetPriority(::ae::gfx_low::QueuePriority::Normal);

        // Device の作成
        gfxLowDevice.reset(new ::ae::gfx_low::Device(
            ::ae::gfx_low::DeviceCreateInfo()
                .SetSystem(gfxLowSystem.get())
                .SetQueueCreateInfos(queueCount, queueCreateInfos)));
    }

    // Swapchain の作成
    ::std::unique_ptr<::ae::gfx_low::SwapchainMaster> swapchainMaster;
    {
        auto createInfo = ::ae::gfx_low::SwapchainMasterCreateInfo()
            .SetDevice(gfxLowDevice.get());
#if defined(AE_BASE_OS_WINDOWS)
        createInfo.SetWin32Props(
            (HINSTANCE)GetModuleHandle(0), GetDesktopWindow());
#endif
        swapchainMaster.reset(new ::ae::gfx_low::SwapchainMaster(createInfo));
    }
    auto swapchain =
        swapchainMaster->CreateSwapchain(ae::gfx_low::SwapchainCreateInfo());

    // メインループ
    while (app.receiveEvent() != ::ae::base::AppEvent::Quit) {
        // 更新以外は何もしない
        if (app.lastEvent() != ::ae::base::AppEvent::Update) {
            continue;
        }

        // ディスプレイが閉じられたら終了する
        if (display.isClosed()) {
            app.quit();
        }
    }

    // 終了
    return 0;
}
// EOF
