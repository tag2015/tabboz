// generated by Fast Light User Interface Designer (fluid) version 1.0308

#ifndef GUITipa_h
#define GUITipa_h
#include <FL/Fl.H>
extern int n_nuovatipa; 
extern int fig_nuovatipa; 
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *win_tipa;
#include <FL/Fl_Button.H>
extern Fl_Button *tipa_btn_cercatipa;
#include <FL/Fl_Group.H>
extern Fl_Group *tipa_grp_stats;
#include <FL/Fl_Value_Output.H>
extern Fl_Value_Output *tipa_val_figosita;
#include <FL/Fl_Box.H>
extern Fl_Value_Output *tipa_val_rapporti;
extern Fl_Box *tipa_txt_nome;
extern Fl_Value_Output *tipa_val_fama;
#include <FL/Fl_Return_Button.H>
extern Fl_Value_Output *tipa_val_credito;
extern Fl_Button *tipa_btn_tette;
extern Fl_Button *tipa_btn_culo;
Fl_Double_Window* GUITipa();
extern Fl_Double_Window *win_cercatipa;
#include <FL/Fl_Output.H>
extern Fl_Output *cercatipa_txt_nome;
extern Fl_Value_Output *cercatipa_val_figosita;
extern Fl_Output *cercatipa_txt_giudizio;
Fl_Double_Window* GUICercaTipa();
extern Fl_Double_Window *win_duedipicche;
extern Fl_Box *ddp_box;
Fl_Double_Window* GUIDueDiPicche(int messaggio);
extern Fl_Double_Window *win_duetipe;
Fl_Double_Window* GUICasanova(int i_nome_nuovatipa, int figosita_nuovatipa);
#endif
