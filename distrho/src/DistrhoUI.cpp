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

#include "DistrhoUIInternal.hpp"

START_NAMESPACE_DISTRHO

/* ------------------------------------------------------------------------------------------------------------
 * Static data, see DistrhoUIInternal.hpp */

double     d_lastUiSampleRate = 0.0;
void*      d_lastUiDspPtr = nullptr;
NtkWindow* d_lastUiWindow = nullptr;

/* ------------------------------------------------------------------------------------------------------------
 * NtkUI */

NtkUI::NtkUI()
    : NtkWidget(*d_lastUiWindow),
      pData(new PrivateData()) {}

NtkUI::~NtkUI()
{
    delete pData;
}

/* ------------------------------------------------------------------------------------------------------------
 * Host state */

double NtkUI::d_getSampleRate() const noexcept
{
    return pData->sampleRate;
}

void NtkUI::d_editParameter(const uint32_t index, const bool started)
{
    pData->editParamCallback(index + pData->parameterOffset, started);
}

void NtkUI::d_setParameterValue(const uint32_t index, const float value)
{
    pData->setParamCallback(index + pData->parameterOffset, value);
}

#if DISTRHO_PLUGIN_WANT_STATE
void NtkUI::d_setState(const char* const key, const char* const value)
{
    pData->setStateCallback(key, value);
}
#endif

#if DISTRHO_PLUGIN_IS_SYNTH
void NtkUI::d_sendNote(const uint8_t channel, const uint8_t note, const uint8_t velocity)
{
    pData->sendNoteCallback(channel, note, velocity);
}
#endif

#if DISTRHO_PLUGIN_WANT_DIRECT_ACCESS
/* ------------------------------------------------------------------------------------------------------------
 * Direct DSP access */

void* NtkUI::d_getPluginInstancePointer() const noexcept
{
    return pData->dspPtr;
}
#endif

/* ------------------------------------------------------------------------------------------------------------
 * DSP/Plugin Callbacks (optional) */

void NtkUI::d_sampleRateChanged(double) {}

/* ------------------------------------------------------------------------------------------------------------
 * UI Resize Handling, internal */

void NtkUI::resize(int x, int y, int w, int h)
{
    NtkWidget::resize(x, y, w, h);
    pData->setSizeCallback(w, h);
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
