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

#ifndef DGL_NTK_WINDOW_HPP_INCLUDED
#define DGL_NTK_WINDOW_HPP_INCLUDED

#include "NtkApp.hpp"

START_NAMESPACE_DGL

class NtkWidget;

// -----------------------------------------------------------------------

class NtkWindow : public Fl_Double_Window
{
public:
    explicit NtkWindow(NtkApp& app)
        : Fl_Double_Window(100, 100),
          fApp(app),
          fIsVisible(false),
          fUsingEmbed(false),
          fParent(nullptr) {}

    explicit NtkWindow(NtkApp& app, NtkWindow& parent)
        : Fl_Double_Window(100, 100),
          fApp(app),
          fIsVisible(false),
          fUsingEmbed(false),
          fParent(&parent) {}

    explicit NtkWindow(NtkApp& app, intptr_t parentId)
        : Fl_Double_Window(100, 100),
          fApp(app),
          fIsVisible(parentId != 0),
          fUsingEmbed(parentId != 0),
          fParent(nullptr)
    {
        if (fUsingEmbed)
        {
            fl_embed(this, (Window)parentId);
            Fl_Double_Window::show();
            fApp.addWindow(this);
        }
    }

    ~NtkWindow() override
    {
        if (fUsingEmbed)
        {
            fApp.removeWindow(this);
            Fl_Double_Window::hide();
        }
    }

    void show() override
    {
        if (fUsingEmbed || fIsVisible)
            return;

        Fl_Double_Window::show();
        fApp.addWindow(this);
        fIsVisible = true;

        if (fParent != nullptr)
            setTransientWinId((intptr_t)fl_xid(fParent));
    }

    void hide() override
    {
        if (fUsingEmbed || ! fIsVisible)
            return;

        fIsVisible = false;
        fApp.removeWindow(this);
        Fl_Double_Window::hide();
    }

    void setTransientWinId(intptr_t winId)
    {
        DISTRHO_SAFE_ASSERT_RETURN(winId != 0,);

#ifdef DISTRHO_OS_LINUX
        DISTRHO_SAFE_ASSERT_RETURN(fl_display != nullptr,);

        const ::Window ourWindow(fl_xid(this));
        DISTRHO_SAFE_ASSERT_RETURN(ourWindow != 0,);

        XSetTransientForHint(fl_display, ourWindow, winId);
#endif
    }

    NtkApp& getApp() const noexcept
    {
        return fApp;
    }

    intptr_t getWindowId() const
    {
        return (intptr_t)fl_xid(this);
    }

private:
    NtkApp& fApp;
    bool    fIsVisible;
    bool    fUsingEmbed;

    // transient parent, may be null
    NtkWindow* const fParent;

    friend class NtkWidget;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NtkWindow)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif // DGL_NTK_WINDOW_HPP_INCLUDED
