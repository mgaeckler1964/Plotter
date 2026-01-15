/*
		Project:		Plotter
		Module:			Plotter.cpp
		Description:	A fuction graph plotter
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2026 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Linz, Austria ``AS IS''
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


// --------------------------------------------------------------------- //
// ----- switches ------------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- includes ------------------------------------------------------ //
// --------------------------------------------------------------------- //

#include <fstream>

#include <gak/numericString.h>
#include <gak/fmtNumber.h>
#include <gak/shared.h>
#include <gak/exception.h>
#include <gak/expressionEvaluator.h>

#include <WINLIB/WINAPP.H>
#include <WINLIB/colors.h>

#include "Plotter_rc.h"
#include "Plotter.gui.h"

// --------------------------------------------------------------------- //
// ----- imported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module switches ----------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT-
#	pragma option -b
#	pragma option -a4
#	pragma option -pc
#endif

using namespace gak;
using namespace winlib;
using namespace winlibGUI;

// --------------------------------------------------------------------- //
// ----- constants ----------------------------------------------------- //
// --------------------------------------------------------------------- //

static const size_t MIN_COUNT = 3;

// --------------------------------------------------------------------- //
// ----- macros -------------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- type definitions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class definitions --------------------------------------------- //
// --------------------------------------------------------------------- //

struct FunctionPlot : public gak::Array<Point>
{
	COLORREF	theColor;

	FunctionPlot() : theColor( colors::BLACK ) {}
};

class PlotterMainWindow : public PlotterFORM_form
{
	bool created;

	double minX;
	double maxX;
	double minY;
	double maxY;

	gak::Array<FunctionPlot>	graphValues;

	void paintGraph();
	void recalc();

	virtual ProcessStatus handleCreate();
	virtual ProcessStatus handleButtonClick( int control );
	virtual ProcessStatus handleResize( const Size &newSize );
	virtual ProcessStatus handleRepaint( Device &hDC );
public:
	PlotterMainWindow();
};

class WindowsApplication : public GuiApplication
{
	virtual bool startApplication( HINSTANCE /*hInstance*/, const char * /* cmdLine */ )
	{
		doEnableLogEx(gakLogging::llInfo);
		doDisableLog();
		setApplication("Plotter");
		setComapny("gak");
		return false;
	}
	virtual CallbackWindow  *createMainWindow( const char * /*cmdLine*/, int /*nCmdShow*/ )
	{
		std::auto_ptr<PlotterMainWindow>	mainWindow( new PlotterMainWindow );
		if( mainWindow->create( nullptr ) == scERROR )
		{
			throw gak::LibraryException( "Could not create window!" );
		}
		mainWindow->focus();

		return mainWindow.release();
	}
	virtual void deleteMainWindow( BasicWindow  *mainWindow )
	{
		delete mainWindow;
	}

	public:
	WindowsApplication() : GuiApplication( IDI_PLOTTER ) {}
};

// --------------------------------------------------------------------- //
// ----- exported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module static data -------------------------------------------- //
// --------------------------------------------------------------------- //

static WindowsApplication	app;

// --------------------------------------------------------------------- //
// ----- class static data --------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- prototypes ---------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module functions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class inlines ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class constructors/destructors -------------------------------- //
// --------------------------------------------------------------------- //

PlotterMainWindow::PlotterMainWindow() : PlotterFORM_form( nullptr ), created(false)
{
}

// --------------------------------------------------------------------- //
// ----- class static functions ---------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class privates ------------------------------------------------ //
// --------------------------------------------------------------------- //

void PlotterMainWindow::paintGraph()
{
	int			imageWidth =  PaintBox->getClientSize().width;
	int			imageHeight =  PaintBox->getClientSize().height;
	DrawDevice	dc(PaintBox);
	double		deltaX = (maxX-minX)/imageWidth;
	double		deltaY = (maxY-minY)/imageHeight;

	dc.rectangle( RectBorder( 0, 0, imageWidth-1, imageHeight-1) );
	dc.getPen().setColor(colors::BLACK);

	if( minX <= 0 && maxX >= 0 )
	{
		int yAxis = int(-minX / (-minX+maxX) * imageWidth);
		dc.moveTo( yAxis, 0 );
		dc.lineTo( yAxis, imageHeight-1 );

		for( double y = ceil( minY ); y <= maxY; y++ )
		{
			int iy = int((maxY-y)/deltaY);
			dc.moveTo( yAxis, iy );
			dc.lineTo( yAxis+5, iy );
		}
	}
	if( minY <= 0 && maxY >= 0 )
	{
		int xAxis = int(maxY / (-minY+maxY) * imageHeight);
		dc.moveTo( 0, xAxis );
		dc.lineTo( imageWidth-1, xAxis );

		for( double x = ceil( minX ); x <= maxX; x++ )
		{
			int ix = int((maxY-x)/deltaX);
			dc.moveTo( ix,  xAxis );
			dc.lineTo( ix, xAxis-5 );
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
		dc.getPen().setColor(oneGraph.theColor);
		if( oneGraph.size() >= 2 )
		{
			dc.polyline(
				oneGraph.getDataBuffer(), int(oneGraph.size()-1)
			);
		}
	}
}

void PlotterMainWindow::recalc()
{
	static COLORREF	theColors[] = { colors::BLUE, colors::RED, colors::LIME };

	graphValues.clear();

	minX = EditXmin->getText() > "" ? EditXmin->getText().getValueN<double>() : 0;
	maxX = EditXmax->getText() > "" ? EditXmax->getText().getValueN<double>() : 0;
	minY = EditYmin->getText() > "" ? EditYmin->getText().getValueN<double>() : 0;
	maxY = EditYmax->getText() > "" ? EditYmax->getText().getValueN<double>() : 0;

	if( minX >= maxX )
		throw LibraryException( "X Bounds missing or wrong." );
	if( minY >= maxY )
		throw LibraryException( "Y Bounds missing or wrong." );

	int	imageWidth =  PaintBox->getClientSize().width;
	int	imageHeight =  PaintBox->getClientSize().height;

	double deltaX = (maxX-minX)/imageWidth;
	double deltaY = (maxY-minY)/imageHeight;

	if( EditXmin->getText() == "" || EditXmax->getText() == "" )
	{
		if( EditYmin->getText() == "" || EditYmax->getText() == "" )
			throw LibraryException( "X Bound cannot be calculated" );

		if( EditXmin->getText() == "" )
			minX = maxX - imageWidth * deltaY;
		else
			maxX = minX + imageWidth * deltaY;
		deltaX = deltaY;
	}
	if( EditYmin->getText() == "" || EditYmax->getText() == "" )
	{
		if( EditXmin->getText() == "" || EditXmax->getText() == "" )
			throw LibraryException( "Y Bound cannot be calculated" );

		if( EditYmin->getText() == "" )
			minY = maxY - imageHeight * deltaX;
		else
			maxY = minY + imageHeight * deltaX;
		deltaY = deltaX;
	}

	gak::Stack<gak::STRING>	terms;
	if( EditFunction1->getText() > "" )
		terms.push( EditFunction1->getText() );
	if( EditFunction2->getText() > "" )
		terms.push( EditFunction2->getText() );
	if( EditFunction3->getText() > "" )
		terms.push( EditFunction3->getText() );

	if( terms.size() )
	{
		gak::MathExpression	theEvaluator;

		int		colorIndex = 0;

		do
		{
			gak::STRING	funcTerm = terms.pop();

			COLORREF color = theColors[colorIndex++];

			int	ix, iy;

			double x = minX;
			double y;
			Point	newPoint;

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
						iy = int((maxY-y)/deltaY);
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
						STRING errText = e.what();
						errText += " at \"";
						errText += funcTerm;
						errText += '\"';
						throw LibraryException( errText );
					}
					catch( ... )
					{
						STRING errText = "Unknown ";
						errText += " at \"";
						errText += funcTerm;
						errText += '\"';
						throw LibraryException( errText );
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
					iy = int((maxY-y)/deltaY);

					Point	&newPoint = oneGraph.createElement();

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

// --------------------------------------------------------------------- //
// ----- class protected ----------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class virtuals ------------------------------------------------ //
// --------------------------------------------------------------------- //
   
ProcessStatus PlotterMainWindow::handleCreate()
{
	created = true;
	return psDO_DEFAULT;
}

ProcessStatus PlotterMainWindow::handleButtonClick( int control )
{
	if( control == PUSHrefresh_id )
	{
		recalc();
		invalidateWindow();
		return psPROCESSED;
	}
	return PlotterFORM_form::handleButtonClick( control );
}

ProcessStatus PlotterMainWindow::handleResize( const Size &newSize )
{
	if( created )
		recalc();
	return PlotterFORM_form::handleResize(newSize);
}

ProcessStatus PlotterMainWindow::handleRepaint(Device &hDC)
{
	paintGraph();
	return PlotterFORM_form::handleRepaint(hDC);
}

// --------------------------------------------------------------------- //
// ----- class publics ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- entry points -------------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT.
#	pragma option -b.
#	pragma option -a.
#	pragma option -p.
#endif

