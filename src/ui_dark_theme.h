// Copyright (c) 2026
// Aegisub Shadow dark theme helpers

#pragma once

class wxWindow;

namespace dark_ui {
/// Return true when Aegisub's experimental dark mode is enabled.
bool Enabled();

/// Apply the shared dark palette to a window and all of its children.
/// This is intentionally conservative: it only changes colours, not layout,
/// labels, sizing, validators, bindings, or control behaviour.
void Apply(wxWindow *window);
}
