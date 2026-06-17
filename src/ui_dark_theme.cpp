// Copyright (c) 2026
// Aegisub Shadow dark theme helpers

#include "ui_dark_theme.h"

#include "options.h"

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/dataview.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/window.h>

namespace {
wxColour const bg(30, 30, 30);
wxColour const panel_bg(37, 37, 38);
wxColour const input_bg(32, 32, 32);
wxColour const text_fg(230, 230, 230);
wxColour const muted_fg(190, 190, 190);

void apply_to_window(wxWindow *window) {
	if (!window) return;

	window->SetBackgroundColour(panel_bg);
	window->SetForegroundColour(text_fg);

	if (dynamic_cast<wxTextCtrl *>(window) ||
		dynamic_cast<wxComboBox *>(window) ||
		dynamic_cast<wxChoice *>(window) ||
		dynamic_cast<wxSpinCtrl *>(window)) {
		window->SetBackgroundColour(input_bg);
		window->SetForegroundColour(text_fg);
	}
	else if (dynamic_cast<wxButton *>(window)) {
		window->SetBackgroundColour(wxColour(47, 47, 47));
		window->SetForegroundColour(text_fg);
	}
	else if (dynamic_cast<wxListBox *>(window) ||
		dynamic_cast<wxDataViewCtrl *>(window)) {
		window->SetBackgroundColour(bg);
		window->SetForegroundColour(text_fg);
	}
	else if (dynamic_cast<wxStaticText *>(window) ||
		dynamic_cast<wxCheckBox *>(window) ||
		dynamic_cast<wxRadioBox *>(window)) {
		window->SetBackgroundColour(panel_bg);
		window->SetForegroundColour(text_fg);
	}
	else if (dynamic_cast<wxNotebook *>(window)) {
		window->SetBackgroundColour(panel_bg);
		window->SetForegroundColour(muted_fg);
	}

	for (auto node = window->GetChildren().GetFirst(); node; node = node->GetNext()) {
		apply_to_window(node->GetData());
	}
}
}

namespace dark_ui {
bool Enabled() {
	return OPT_GET("App/Dark Mode")->GetBool();
}

void Apply(wxWindow *window) {
	if (!Enabled() || !window) return;

	apply_to_window(window);
	window->Refresh();
}
}
