module;

#include <Unknwn.h> // Required to interop with IUnknown. Must be included before C++/WinRT headers.
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.ApplicationModel.Preview.Holographic.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Text.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Graphics.Holographic.h>

export module Hololens.Platform;
import Engine.Core.GameEngine;
import Engine.Core.Platform;
import Engine.XR.Service;

namespace windows {
	using namespace winrt::Windows::ApplicationModel::Activation;
	using namespace winrt::Windows::ApplicationModel::Core;
	using namespace winrt::Windows::UI::Core;
	using namespace winrt::Windows::UI::Text::Core;
	using namespace winrt::Windows::UI::ViewManagement;
	using namespace winrt::Windows::Graphics::Holographic;
	using namespace winrt::Windows::ApplicationModel::Preview::Holographic;
} // namespace windows

export struct HololensPlatform : 
	public Engine::Core::IPlatform,
	public winrt::implements<HololensPlatform, windows::IFrameworkView>
{
public:

	explicit HololensPlatform() :
		_shouldUpdate{true},
		_windowClosed{false},
		_openXrService{nullptr}
	{
	}
	
	// ================= Engine IPlatform ===================================

	virtual void Update() override
	{
	}

	virtual bool ShouldContinue() override
	{
		return _shouldUpdate;
	}

	
	// ============= WinRT bullshit =============================================
	void Initialize(windows::CoreApplicationView const& applicationView) {
		//::Trace("IFrameworkView::Initialize");
		applicationView.Activated({ this, &HololensPlatform::OnActivated });
	}

	void Load(winrt::hstring const& entryPoint) {
		//::Trace("IFrameworkView::Load entryPoint : {}", winrt::to_string(entryPoint).c_str());
	}

	void Uninitialize() {
		//::Trace("IFrameworkView::Uninitialize");
	}

	void OnActivated(windows::CoreApplicationView const&, windows::IActivatedEventArgs const& args) {
		if (args.Kind() == windows::ActivationKind::Protocol) {
			windows::ProtocolActivatedEventArgs eventArgs{ args.as<windows::ProtocolActivatedEventArgs>() };
			//::Trace("Protocol uri : {}", winrt::to_string(eventArgs.Uri().RawUri()).c_str());
		}

		// Inspecting whether the application is launched from within holographic shell or from desktop.
		if (windows::HolographicApplicationPreview::IsHolographicActivation(args)) {
			//::Trace("App activation is targeted at the holographic shell.");
		}
		else {
			//::Trace("App activation is targeted at the desktop.");
		}

		// NOTE: CoreWindow will be activated later after the HolographicSpace has been created.
	}

	void Run() {
		//::Trace("IFrameworkView::Run");

		// Creating a HolographicSpace before activating the CoreWindow to make it a holographic window
		windows::CoreWindow window = windows::CoreWindow::GetForCurrentThread();
		windows::HolographicSpace holographicSpace = windows::HolographicSpace::CreateForCoreWindow(window);
		window.Activate();

		//XrHolographicWindowAttachmentMSFT holographicWindowAttachment{ XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT };
		//holographicWindowAttachment.coreWindow = window.as<::IUnknown>().get();
		//holographicWindowAttachment.holographicSpace = holographicSpace.as<::IUnknown>().get();
		Engine::Core::GameEngineCreationInfo info{};
		info._platform = this;
		info._targetFps = 60;

		Engine::XR::ExtensionList extensionsList{};

		_openXrService = new Engine::XR::OpenXrService();
		if (!_openXrService->Initialize(extensionsList))
		{
			return;
		}

		Engine::Core::GameEngine gameEngine{info};
		gameEngine.Start();
	}

	void SetWindow(windows::CoreWindow const& window) {
		//::Trace("IFrameworkView::SetWindow");

		InitializeTextEditingContext();
		window.KeyDown({ this, &HololensPlatform::OnKeyDown });
		window.Closed({ this, &HololensPlatform::OnWindowClosed });
	}

	void InitializeTextEditingContext() {
		// This // customizes the text input pane with manual display policy and email address scope.
		windows::CoreTextServicesManager manager = windows::CoreTextServicesManager::GetForCurrentView();
		windows::CoreTextEditContext editingContext = manager.CreateEditContext();
		editingContext.InputPaneDisplayPolicy(windows::CoreTextInputPaneDisplayPolicy::Manual);
		editingContext.InputScope(windows::CoreTextInputScope::EmailAddress);
	}

	void OnKeyDown(windows::CoreWindow const& sender, windows::KeyEventArgs const& args) {
		//::Trace("OnKeyDown : 0x{:x}", (int)args.VirtualKey());

		// This sample toggles the software keyboard in HMD using space key
		if (args.VirtualKey() == winrt::Windows::System::VirtualKey::Space) {
			windows::InputPane inputPane = windows::InputPane::GetForCurrentView();
			if (inputPane.Visible()) {
				const bool hidden = inputPane.TryHide();
				//sample::Trace("InputPane::TryHide() -> {}", hidden);
			}
			else {
				const bool shown = inputPane.TryShow();
				//::Trace("InputPane::TryShow() -> {}", shown);
			}
		}
	}

	void OnWindowClosed(windows::CoreWindow const& sender, windows::CoreWindowEventArgs const& args) {
		_windowClosed = true;
	}

private:
	bool _shouldUpdate;
	bool _windowClosed;
	Engine::XR::OpenXrService* _openXrService;

};

export struct HololensPlatformSource :
	winrt::implements<HololensPlatformSource, windows::IFrameworkViewSource>
{
	windows::IFrameworkView CreateView() {
		return winrt::make<HololensPlatform>();
	}
};
