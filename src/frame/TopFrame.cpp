#include "TopFrame.h"
#include "functional.h"

#undef _
#define _(x) wxT(x)

//(*InternalHeaders(TopFrame)
#include <wx/button.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>
//*)

//(*IdInit(TopFrame)
const long TopFrame::ID_STATICTEXT1 = wxNewId();
const long TopFrame::ID_TEXTCTRL1 = wxNewId();
const long TopFrame::ID_STATICTEXT2 = wxNewId();
const long TopFrame::ID_TEXTCTRL2 = wxNewId();
const long TopFrame::ID_BUTTON1 = wxNewId();
const long TopFrame::ID_STATICTEXT3 = wxNewId();
const long TopFrame::ID_STATICTEXT4 = wxNewId();
const long TopFrame::ID_STATICTEXT5 = wxNewId();
const long TopFrame::ID_STATICTEXT6 = wxNewId();
const long TopFrame::ID_STATICTEXT7 = wxNewId();
const long TopFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TopFrame,wxFrame)
	//(*EventTable(TopFrame)
	//*)
END_EVENT_TABLE()

TopFrame::TopFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TopFrame)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxStaticBoxSizer* StaticBoxSizer6;

	Create(parent, wxID_ANY, _("a2s查看器（目前仅支持L4D2）"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(400,400));
	SetIcon(wxIcon(wxT("aaaa")));
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(328,376), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("地址"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("IP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer4->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	text_IP = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer4->Add(text_IP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer4, 1, wxALL|wxEXPAND, 0);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("端口"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer5->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	text_port = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("27015"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer5->Add(text_port, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer5, 1, wxALL|wxEXPAND, 0);
	BoxSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
	button_query = new wxButton(Panel1, ID_BUTTON1, _("查询"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(button_query, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("服务器名"));
	label_servername = new wxStaticText(Panel1, ID_STATICTEXT3, _("Label"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT3"));
	wxFont label_servernameFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Times New Roman"),wxFONTENCODING_DEFAULT);
	label_servername->SetFont(label_servernameFont);
	StaticBoxSizer2->Add(label_servername, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("地图"));
	label_mapname = new wxStaticText(Panel1, ID_STATICTEXT4, _("Label"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT4"));
	wxFont label_mapnameFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	label_mapname->SetFont(label_mapnameFont);
	StaticBoxSizer3->Add(label_mapname, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("玩家"));
	label_player_count = new wxStaticText(Panel1, ID_STATICTEXT5, _("Label"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT5"));
	wxFont label_player_countFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	label_player_count->SetFont(label_player_countFont);
	StaticBoxSizer4->Add(label_player_count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("VAC"));
	label_vac = new wxStaticText(Panel1, ID_STATICTEXT6, _("Label"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT6"));
	wxFont label_vacFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	label_vac->SetFont(label_vacFont);
	StaticBoxSizer5->Add(label_vac, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer5, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("标签"));
	label_keywords = new wxStaticText(Panel1, ID_STATICTEXT7, _("Label"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT7"));
	wxFont label_keywordsFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
	label_keywords->SetFont(label_keywordsFont);
	StaticBoxSizer6->Add(label_keywords, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 5);
	Panel1->SetSizer(BoxSizer1);
	BoxSizer1->Fit(Panel1);
	BoxSizer1->SetSizeHints(Panel1);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TopFrame::OnQueryClick);
	//*)

    label_servername->SetLabel(wxEmptyString);
    label_mapname->SetLabel(wxEmptyString);
    label_player_count->SetLabel(wxEmptyString);
    label_vac->SetLabel(wxEmptyString);
    label_keywords->SetLabel(wxEmptyString);


}

TopFrame::~TopFrame()
{
	//(*Destroy(TopFrame)
	//*)
}