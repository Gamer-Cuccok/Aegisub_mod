// Copyright (c) 2026
// Aegisub Shadow dark theme helpers

#include "ui_dark_theme.h"

#include "options.h"

#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/control.h>
#include <wx/dataview.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/radiobut.h>
#include <wx/scrolbar.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/window.h>

namespace {
wxColour const bg(24, 24, 24);
wxColour const panel_bg(30, 30, 30);
wxColour const panel_bg_2(37, 37, 38);
wxColour const input_bg(25, 25, 25);
wxColour const button_bg(47, 47, 47);
wxColour const text_fg(232, 232, 232);
wxColour const muted_fg(195, 195, 195);

void paint(wxWindow *window, wxColour const& background, wxColour const& foreground) {
    if (!window) return;

    window->SetBackgroundColour(background);
    window->SetForegroundColour(foreground);
    window->SetOwnBackgroundColour(background);
    window->SetOwnForegroundColour(foreground);
}

void apply_to_window(wxWindow *window) {
    if (!window) return;

    paint(window, panel_bg, text_fg);

    if (dynamic_cast<wxTextCtrl *>(window) ||
        dynamic_cast<wxComboBox *>(window) ||
        dynamic_cast<wxChoice *>(window) ||
        dynamic_cast<wxSpinCtrl *>(window) ||
        dynamic_cast<wxSpinCtrlDouble *>(window)) {
        paint(window, input_bg, text_fg);
    }
    else if (dynamic_cast<wxButton *>(window) ||
        dynamic_cast<wxBitmapButton *>(window)) {
        paint(window, button_bg, text_fg);
    }
    else if (dynamic_cast<wxListBox *>(window) ||
        dynamic_cast<wxListCtrl *>(window) ||
        dynamic_cast<wxDataViewCtrl *>(window)) {
        paint(window, bg, text_fg);
    }
    else if (dynamic_cast<wxPanel *>(window) ||
        dynamic_cast<wxStaticBox *>(window) ||
        dynamic_cast<wxStaticLine *>(window) ||
        dynamic_cast<wxSlider *>(window) ||
        dynamic_cast<wxScrollBar *>(window)) {
        paint(window, panel_bg_2, text_fg);
    }
    else if (dynamic_cast<wxStaticText *>(window) ||
        dynamic_cast<wxCheckBox *>(window) ||
        dynamic_cast<wxRadioButton *>(window) ||
        dynamic_cast<wxRadioBox *>(window)) {
        paint(window, panel_bg, text_fg);
    }
    else if (dynamic_cast<wxNotebook *>(window)) {
        paint(window, panel_bg_2, muted_fg);
    }

    for (auto node = window->GetChildren().GetFirst(); node; node = node->GetNext()) {
        apply_to_window(node->GetData());
    }

    window->Refresh();
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
    window->Update();
}
}