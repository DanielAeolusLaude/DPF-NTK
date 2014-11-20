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

#ifndef DGL_NTK_WIDGET_HPP_INCLUDED
#define DGL_NTK_WIDGET_HPP_INCLUDED

#include "NtkWindow.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

/**
   DGL compatible Widget class that uses NTK instead of OpenGL.
   @see Widget
 */
class NtkWidget : public Fl_Double_Window
{
public:
   /**
      Constructor.
    */
    explicit NtkWidget(NtkWindow& parent)
        : Fl_Double_Window(100, 100),
          fParent(parent)
    {
        fParent.add(this);
        show();
    }

   /**
      Destructor.
    */
    ~NtkWidget() override
    {
        hide();
        fParent.remove(this);
    }

   /**
      Get this widget's window application.
      Same as calling getParentWindow().getApp().
    */
    NtkApp& getParentApp() const noexcept
    {
        return fParent.getApp();
    }

   /**
      Get parent window, as passed in the constructor.
    */
    NtkWindow& getParentWindow() const noexcept
    {
        return fParent;
    }

private:
    NtkWindow& fParent;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NtkWidget)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif // DGL_NTK_WIDGET_HPP_INCLUDED
