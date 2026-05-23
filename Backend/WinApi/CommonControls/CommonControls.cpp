#include "CommonControls.h"


namespace Blade::Backend {


auto CommonControls::DpiAwareness() -> void
{
    // DPI awareness
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    // Optional good practice comctl32
    INITCOMMONCONTROLSEX icc{};
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_STANDARD_CLASSES;

    InitCommonControlsEx(&icc);
}


} // namespace
