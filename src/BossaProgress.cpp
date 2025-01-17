///////////////////////////////////////////////////////////////////////////////
// BOSSA
//
// Copyright (c) 2011-2018, ShumaTech
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the <organization> nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////
#include "BossaProgress.h"

DEFINE_LOCAL_EVENT_TYPE(wxEVT_PROGRESS_CANCEL)

BossaProgress::BossaProgress(wxWindow* parent) : ProgressDialog(parent), _parent(parent)
{
    _statusGauge->SetRange(100);
    SetValue(0);

    _sdbSizerCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                             wxCommandEventHandler(BossaProgress::OnCancel),
                             NULL, this);
}

void
BossaProgress::SetValue(int pos)
{
    _statusGauge->SetValue(pos);
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined (__CYGWIN__)
    // Work around slow update on Windows
    _statusGauge->SetValue(pos - 1);
    _statusGauge->SetValue(pos);
#endif
}

void
BossaProgress::SetLabel(const wxString& label)
{
    _infoStaticText->SetLabel(label);
}

void
BossaProgress::OnCancel(wxCommandEvent& event)
{
    wxCommandEvent cmd(wxEVT_PROGRESS_CANCEL);
    _parent->AddPendingEvent(cmd);
}
