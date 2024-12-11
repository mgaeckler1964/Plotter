/*
		Project:		Plotter
		Module:			PlotterMainFrm.h
		Description:	the form
		Author:			Martin G�ckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin G�ckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin G�ckler, Austria, Linz ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/

//---------------------------------------------------------------------------

#ifndef PlotterMainFrmH
#define PlotterMainFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <gak/array.h>

//---------------------------------------------------------------------------
class FunctionPlot : public gak::Array<Windows::TPoint>
{
	public:
	TColor	theColor;

	FunctionPlot() : theColor( clBlack ) {}
};
//---------------------------------------------------------------------------
class TPlotterForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPaintBox *PaintBox;
	TLabel *Label1;
	TEdit *EditXmin;
	TEdit *EditXmax;
	TLabel *Label2;
	TEdit *EditYmin;
	TEdit *EditYmax;
	TLabel *Label3;
	TEdit *EditFunction1;
	TButton *ButtonRefresh;
	TEdit *EditFunction2;
	TEdit *EditFunction3;
	void __fastcall PaintBoxPaint(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall ButtonRefreshClick(TObject *Sender);
private:	// User declarations
	double minX;
	double maxX;
	double minY;
	double maxY;
	gak::Array<FunctionPlot>	graphValues;

	void recalc( void );
public:		// User declarations
	__fastcall TPlotterForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPlotterForm *PlotterForm;
//---------------------------------------------------------------------------
#endif

