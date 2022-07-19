
#include <Unknwn.h> // Required to interop with IUnknown. Must be included before C++/WinRT headers.
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.ApplicationModel.Preview.Holographic.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Text.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Graphics.Holographic.h>

namespace windows {
	using namespace winrt::Windows::ApplicationModel::Activation;
	using namespace winrt::Windows::ApplicationModel::Core;
	using namespace winrt::Windows::UI::Core;
	using namespace winrt::Windows::UI::Text::Core;
	using namespace winrt::Windows::UI::ViewManagement;
	using namespace winrt::Windows::Graphics::Holographic;
	using namespace winrt::Windows::ApplicationModel::Preview::Holographic;
} // namespace windows

import Hololens.Platform;

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int) {
    windows::CoreApplication::Run(winrt::make<HololensPlatformSource>());
}