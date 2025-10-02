//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TInterface : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TGroupBox *GroupBox1;
    TBitBtn *btnCheck;
    TBitBtn *btnQuit;
    TEdit *Proxy;
    TLabel *Label1;
    TEdit *PPort;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Web;
    TLabel *Label4;
    TEdit *WPort;
    void __fastcall btnQuitClick(TObject *Sender);
    void __fastcall btnCheckClick(TObject *Sender);
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
    __fastcall TInterface(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterface *Interface;
//---------------------------------------------------------------------------
#endif
