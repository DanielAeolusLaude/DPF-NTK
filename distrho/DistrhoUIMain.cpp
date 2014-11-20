/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2014 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "src/DistrhoUI.cpp"

#if defined(DISTRHO_PLUGIN_TARGET_CARLA)
// nothing
#elif defined(DISTRHO_PLUGIN_TARGET_JACK)
// nothing
#elif defined(DISTRHO_PLUGIN_TARGET_DSSI)
# include "src/DistrhoUIDSSI.cpp"
#elif defined(DISTRHO_PLUGIN_TARGET_LV2)
# include "src/DistrhoUILV2.cpp"
#elif defined(DISTRHO_PLUGIN_TARGET_VST)
// nothing
#endif

// -----------------------------------------------------------------------

START_NAMESPACE_DGL

void NtkApp::NextUI::run()
{
    const FlScopedLock csl;

    if (create)
    {
        d_stdout("Creating NTK UI in separate thread...");
        d_NtkUI* const ui2 = (func)();
        ui = ui2;
    }
    else
    {
        d_stdout("Destroying NTK UI in separate thread...");
        d_NtkUI* const ui2 = ui;
        ui = nullptr;
        delete ui2;
    }
}

END_NAMESPACE_DGL

// -----------------------------------------------------------------------
