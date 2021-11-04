using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Interop;

namespace WpfApp2
{
    class ControlHost : HwndHost
    {
        internal const int
       WsChild = 0x40000000,
       WsVisible = 0x10000000,
       LbsNotify = 0x00000001,
       HostId = 0x00000002,
       ListboxId = 0x00000001,
       WsVscroll = 0x00200000,
       WsBorder = 0x00800000;

        const uint SwpNosize = 0x0001;
        const uint SwpNomove = 0x0002;
        const uint SwpNozorder = 0x0004;

        const int WmSize = 0x0005;

        private readonly int _hostHeight;
        private readonly int _hostWidth;
        private IntPtr _hwndHost;

        public ControlHost(double height, double width)
        {
            _hostHeight = (int)height;
            _hostWidth = (int)width;
        }

        public IntPtr HwndListBox { get; private set; }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            HwndListBox = IntPtr.Zero;
            _hwndHost = IntPtr.Zero;

            _hwndHost = CreateWindowEx(0, "static", "",
                WsChild | WsVisible,
                0, 0,
                _hostHeight, _hostWidth,
                hwndParent.Handle,
                (IntPtr)HostId,
                IntPtr.Zero,
                0);

            HwndListBox = CreateWindowEx(0, "listbox", "",
                WsChild | WsVisible | LbsNotify
                | WsVscroll | WsBorder,
                0, 0,
                _hostHeight, _hostWidth,
                _hwndHost,
                (IntPtr)ListboxId,
                IntPtr.Zero,
                0);

            return new HandleRef(this, _hwndHost);
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;
            switch (msg)
            {
                case WmSize:
                    // リストボックスのサイズを追従させる
                    SetWindowPos(HwndListBox, IntPtr.Zero, 0, 0, (int)this.ActualWidth, (int)this.ActualHeight, SwpNomove | SwpNozorder);
                    break;
            }
            return IntPtr.Zero;
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            DestroyWindow(hwnd.Handle);
        }

        //PInvoke declarations
        [DllImport("user32.dll", EntryPoint = "CreateWindowEx", CharSet = CharSet.Unicode)]
        internal static extern IntPtr CreateWindowEx(int dwExStyle,
            string lpszClassName,
            string lpszWindowName,
            int style,
            int x, int y,
            int width, int height,
            IntPtr hwndParent,
            IntPtr hMenu,
            IntPtr hInst,
            [MarshalAs(UnmanagedType.AsAny)] object pvParam);

        [DllImport("user32.dll", EntryPoint = "DestroyWindow", CharSet = CharSet.Unicode)]
        internal static extern bool DestroyWindow(IntPtr hwnd);


        [DllImport("user32.dll", EntryPoint = "SetWindowPos", CharSet = CharSet.Unicode)]
        internal static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int x, int y, int cx, int cy, uint flags);
    }
}
