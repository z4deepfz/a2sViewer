#ifndef TOPFRAME_H
#define TOPFRAME_H

#include "query.h"
#include "a2s_info_l4d2.h"
#include <boost/asio.hpp>
//#include <boost/timer/timer.hpp>
#include <wx/msgdlg.h>
#include <memory>

//(*Headers(TopFrame)
#include <wx/frame.h>
class wxBoxSizer;
class wxButton;
class wxPanel;
class wxStaticBoxSizer;
class wxStaticText;
class wxTextCtrl;
//*)

class TopFrame: public wxFrame
{
	public:

		TopFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TopFrame();

		void Refresh();
		void queryInfo(const char* addr, uint16_t port);
		void receiveHandler();

		//(*Declarations(TopFrame)
		wxButton* button_query;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* label_keywords;
		wxStaticText* label_mapname;
		wxStaticText* label_player_count;
		wxStaticText* label_servername;
		wxStaticText* label_vac;
		wxTextCtrl* text_IP;
		wxTextCtrl* text_port;
		//*)

	protected:

		//(*Identifiers(TopFrame)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(TopFrame)
		void OnQueryClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

	protected:

        void updateBoard(
            const wxString& server_name,
            const wxString& map_name,
            const wxString& players,
            const wxString& vac,
            const wxString& keywords
        );

        void updateBoard(const std::tuple<std::string,std::string,uint8_t,uint8_t,bool,std::string,bool>&);

    protected: // data structures

        L4D2::a2s_info_Response response;
        std::string  recv_buffer;


};

#endif
