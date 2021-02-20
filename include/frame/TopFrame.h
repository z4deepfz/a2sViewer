#ifndef TOPFRAME_H
#define TOPFRAME_H

#include <memory>
#include <set>

#include <boost/asio.hpp>

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/msgdlg.h>

#include "query.h"
#include "a2s_info_l4d2.h"
#include "a2s_player.h"
#include "QuickQuerySubscribe.h"

// storage
#include "LocalDataManager.h"
#include "serverConfigStorage.h"
#include "BufferChoice.h"

//(*Headers(TopFrame)
#include <wx/frame.h>
class wxBoxSizer;
class wxButton;
class wxChoice;
class wxListCtrl;
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
		void loadConfigToChoiceBox();
		void queryInfo(const std::string& addr, uint16_t port);
		void queryPlayers(const std::string& addr, uint16_t port, uint8_t retry=5); // 5 times retry


		//(*Declarations(TopFrame)
		BufferChoice* choice_quickQuery;
		wxButton* Button1;
		wxButton* Button2;
		wxButton* button_query;
		wxListCtrl* list_playerlist;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* label_keywords;
		wxStaticText* label_mapname;
		wxStaticText* label_player_count;
		wxStaticText* label_servername;
		wxStaticText* label_vac;
		wxTextCtrl* text_IP;
		wxTextCtrl* text_name;
		wxTextCtrl* text_port;
		//*)

	protected:

		//(*Identifiers(TopFrame)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_CHOICE1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_LISTCTRL1;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(TopFrame)
		void OnQueryClick(wxCommandEvent& event);
		void OnquickQuerySelect(wxCommandEvent& event);
		void OnSaveConfig(wxCommandEvent& event);
		void OnDeleteConfig(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

	protected:

        void clearAll();
        void updateBoard(
            const wxString& server_name,
            const wxString& map_name,
            const wxString& players,
            const wxString& vac,
            const wxString& keywords
        );
        void updatePlayers(
            const std::vector<std::string>& name,
            const std::vector<int>& score,
            const std::vector<float>& time
        );

        void updateBoard(const std::tuple<std::string,std::string,uint8_t,uint8_t,bool,std::string,bool>&);

        void receiveHandler(bool success);
        void quickQueryReceiveHandler(bool success);
        void playerQueryHandler(bool success);

        void subscribe();

    protected: // data structures

        L4D2::a2s_info_Response response;
        QuickQuerySubscribe     sub_response;
        a2s_player              player_response;

        std::string recv_buffer;

    protected: // about qiuck query

        std::set<quickQuery> remote, local;

    protected:

        LocalDataManager local_manager;
            serverConfigStorage server_conf_proxy;



};

#endif
