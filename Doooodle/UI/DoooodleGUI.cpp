#include "DoooodleGUI.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UI::DoooodleGUI mainWindow;
	Application::Run(%mainWindow);
}