// 文字コード：UTF-8
#include <ae/base/Console.hpp>
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

namespace {
POINT fMinsize;
}


LRESULT CALLBACK fWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE: PostQuitMessage(0); break;
    case WM_PAINT: 
        //demo.run(); 
        break;
    case WM_GETMINMAXINFO:  // set window's minimum size
        ((MINMAXINFO*)lParam)->ptMinTrackSize = fMinsize;
        return 0;
    case WM_ERASEBKGND: return 1;
    case WM_SIZE:
        // Resize the application to the new window size, except when
        // it was minimized. Vulkan doesn't support images or swapchains
        // with width=0 and height=0.
        //if (wParam != SIZE_MINIMIZED) {
        //    demo.width = lParam & 0xffff;
        //    demo.height = (lParam & 0xffff0000) >> 16;
        //    demo.resize();
        //}
        break;
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_ESCAPE: PostQuitMessage(0); break;
        //case VK_LEFT: demo.spin_angle -= demo.spin_increment; break;
        //case VK_RIGHT: demo.spin_angle += demo.spin_increment; break;
        //case VK_SPACE: demo.pause = !demo.pause; break;
        }
        return 0;
    default: break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine,
    int nCmdShow) {
#if 0
    return DemoWinMain(hInstance, hPrevInstance, pCmdLine, nCmdShow);
#else
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

    // Window 作成
#if defined(AE_BASE_OS_WINDOWS)
    HWND window = HWND();
    {
        int width = 500;
        int height = 500;
        WNDCLASSEX win_class;
        const char* name = "AdelEngine Vulkan Test";

        // Initialize the window class structure:
        win_class.cbSize = sizeof(WNDCLASSEX);
        win_class.style = CS_HREDRAW | CS_VREDRAW;
        win_class.lpfnWndProc = fWndProc;
        win_class.cbClsExtra = 0;
        win_class.cbWndExtra = 0;
        win_class.hInstance = hInstance;
        win_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        win_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
        win_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        win_class.lpszMenuName = nullptr;
        win_class.lpszClassName = name;
        win_class.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);

        // Register window class:
        if (!RegisterClassEx(&win_class)) {
            // It didn't work, so try to give a useful error:
            AE_BASE_ASSERT_NOT_REACHED_MSG(
                "Unexpected error trying to start the application!\n");
        }

        // Create window with the registered class:
        RECT wr = {0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
        AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
        window = CreateWindowEx(0,
            name,                  // class name
            name,                  // app name
            WS_OVERLAPPEDWINDOW |  // window style
                WS_VISIBLE | WS_SYSMENU,
            100, 100,            // x/y coords
            wr.right - wr.left,  // width
            wr.bottom - wr.top,  // height
            nullptr,             // handle to parent
            nullptr,             // handle to menu
            hInstance,          // hInstance
            nullptr);            // no extra parameters

        if (!window) {
            // It didn't work, so try to give a useful error:
            AE_BASE_ASSERT_NOT_REACHED_MSG("Cannot create a window in which to draw!\n");
        }

        // Window client area size must be at least 1 pixel high, to prevent
        // crash.
        fMinsize.x = GetSystemMetrics(SM_CXMINTRACK);
        fMinsize.y = GetSystemMetrics(SM_CYMINTRACK) + 1;
    }
#endif

    // Swapchain の作成
    ::std::unique_ptr<::ae::gfx_low::SwapchainMaster> swapchainMaster;
    {
        auto& createInfo = ::ae::gfx_low::SwapchainMasterCreateInfo().SetDevice(
                gfxLowDevice.get());
#if defined(AE_BASE_OS_WINDOWS)
        createInfo.SetWin32Props(hInstance, window);
#endif
        swapchainMaster.reset(new ::ae::gfx_low::SwapchainMaster(createInfo));
    }
    auto swapchain = swapchainMaster->CreateSwapchain(ae::gfx_low::SwapchainCreateInfo());

    return 0;
#endif
}
// EOF
