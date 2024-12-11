/*
		Project:		Plotter
		Module:			PlotterMainFrm.h
		Description:	the form uses the interpreter from gaklib
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Austria, Linz ``AS IS''
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

#include <vcl.h>

#include <gak/expressionEvaluator.h>
#include <gak/exception.h>
#include <gak/stack.h>

#pragma hdrstop

#include "PlotterMainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlotterForm *PlotterForm;
//---------------------------------------------------------------------------
__fastcall TPlotterForm::TPlotterForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TPlotterForm::PaintBoxPaint(TObject *)
{
	TCanvas	*Canvas = PaintBox->Canvas;

	int imageWidth =  PaintBox->ClientWidth;
	int imageHeight =  PaintBox->ClientHeight;

	double deltaX = (maxX-minX)/imageWidth;
	double deltaY = (maxY-minY)/imageHeight;

	Canvas->FillRect( Rect( 0, 0, imageWidth-1, imageHeight-1) );
	Canvas->Pen->Color = clBlack;

	if( minX <= 0 && maxX >= 0 )
	{
		int yAxis = -minX / (-minX+maxX) * imageWidth;
		Canvas->MoveTo( yAxis, 0 );
		Canvas->LineTo( yAxis, imageHeight-1 );

		for( double y = ceil( minY ); y <= maxY; y++ )
		{
			int iy = (maxY-y)/deltaY;
			Canvas->MoveTo( yAxis, iy );
			Canvas->LineTo( yAxis+5, iy );
		}
	}
	if( minY <= 0 && maxY >= 0 )
	{
		int xAxis = maxY / (-minY+maxY) * imageHeight;
		Canvas->MoveTo( 0, xAxis );
		Canvas->LineTo( imageWidth-1, xAxis );

		for( double x = ceil( minX ); x <= maxX; x++ )
		{
			int ix = (maxY-x)/deltaX;
			Canvas->MoveTo( ix,  xAxis );
			Canvas->LineTo( ix, xAxis-5 );
		}
	}

	for(
		gak::Array<FunctionPlot>::const_iterator it = graphValues.cbegin(),
			endIT = graphValues.cend();
		it != endIT;
		++it
	)
	{
		const FunctionPlot	&oneGraph = *it;
		Canvas->Pen->Color = oneGraph.theColor;
		if( oneGraph.size() >= 2 )
		{
			Canvas->Polyline(
				oneGraph.getDataBuffer(), oneGraph.size()-1
			);
		}
	}
}
void TPlotterForm::recalc( void )
{
	static TColor	theColors[] = { clBlue, clRed, clGreen };

	graphValues.clear();

	minX = EditXmin->Text > "" ? EditXmin->Text.ToDouble() : 0;
	maxX = EditXmax->Text > "" ? EditXmax->Text.ToDouble() : 0;
	minY = EditYmin->Text > "" ? EditYmin->Text.ToDouble() : 0;
	maxY = EditYmax->Text > "" ? EditYmax->Text.ToDouble() : 0;

	if( minX >= maxX )
		throw Exception( "X Bounds missing or wrong." );
	if( minY >= maxY )
		throw Exception( "Y Bounds missing or wrong." );

	int imageWidth =  PaintBox->ClientWidth;
	int imageHeight =  PaintBox->ClientHeight;

	double deltaX = (maxX-minX)/imageWidth;
	double deltaY = (maxY-minY)/imageHeight;

	if( EditXmin->Text == "" || EditXmax->Text == "" )
	{
		if( EditYmin->Text == "" || EditYmax->Text == "" )
			throw Exception( "X Bound cannot be calculated" );

		if( EditXmin->Text == "" )
			minX = maxX - imageWidth * deltaY;
		else
			maxX = minX + imageWidth * deltaY;
		deltaX = deltaY;
	}
	if( EditYmin->Text == "" || EditYmax->Text == "" )
	{
		if( EditXmin->Text == "" || EditXmax->Text == "" )
			throw Exception( "Y Bound cannot be calculated" );

		if( EditYmin->Text == "" )
			minY = maxY - imageHeight * deltaX;
		else
			maxY = minY + imageHeight * deltaX;
		deltaY = deltaX;
	}

	gak::Stack<gak::STRING>	terms;
	if( EditFunction1->Text > "" )
		terms.push( EditFunction1->Text.c_str() );
	if( EditFunction2->Text > "" )
		terms.push( EditFunction2->Text.c_str() );
	if( EditFunction3->Text > "" )
		terms.push( EditFunction3->Text.c_str() );

	if( terms.size() )
	{
		gak::MathExpression	theEvaluator;

		int		colorIndex = 0;

		do
		{
			gak::STRING	funcTerm = terms.pop();

			TColor	color = theColors[colorIndex++];

			int	ix, iy;

			double x = minX;
			double y;
			Windows::TPoint	newPoint;

			ix = 0;
			while( true )
			{
				// skip invisible points but store the last one in newPoint
				while( true )
				{
					try
					{
						y = theEvaluator.evaluate( funcTerm, x );
						if( y>=minY && y<=maxY )
							break;

						// store this point
						iy = (maxY-y)/deltaY;
						newPoint.x = ix;
						newPoint.y = iy;
					}
					catch( gak::DivisionByZeroError & )
					{
						newPoint.x = -10;
					}
					catch( gak::InvalidResultError & )
					{
						newPoint.x = -10;
					}
					catch( std::exception &e )
					{
						AnsiString errText = e.what();
						errText += " at \"";
						errText += (const char *)funcTerm;
						errText += '\"';
						throw Exception( errText );
					}
					catch( ... )
					{
						AnsiString errText = "Unkonwn error at \"";
						errText += (const char *)funcTerm;
						errText += '\"';
						throw Exception( errText );
					}


					// step to next point
					ix++;
					// reach end of graph?
					if( ix >= imageWidth )
						break;
					x += deltaX;
				}

				// reach end of graph?
				if( ix >= imageWidth )
					break;

				FunctionPlot	&oneGraph = graphValues.createElement();
				oneGraph.theColor = color;
				// add the last invisible point if availabe
				if( newPoint.x+1 == ix )
					oneGraph.addElement( newPoint );

				while( true )
				{
					// add the last evaluation
					iy = (maxY-y)/deltaY;

					Windows::TPoint	&newPoint = oneGraph.createElement();

					newPoint.x = ix;
					newPoint.y = iy;

					// step to next point
					ix++;
					// reach end of graph?
					if( ix >= imageWidth )
						break;
					x += deltaX;

					if( y<minY || y>maxY )
						break;

					y = theEvaluator.evaluate( funcTerm, x );
				}

				// reach end of graph?
				if( ix >= imageWidth )
					break;
			}
		} while( terms.size() );
	}
}
//---------------------------------------------------------------------------

void __fastcall TPlotterForm::FormResize(TObject *Sender)
{
	recalc();
}
//---------------------------------------------------------------------------

void __fastcall TPlotterForm::ButtonRefreshClick(TObject *Sender)
{
	recalc();
	PaintBox->Invalidate();
}
//---------------------------------------------------------------------------

