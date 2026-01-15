/*
	this file was created from C:\CRESD\Source\Plotter\Plotter.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/
#ifndef C__CRESD_SOURCE_PLOTTER_PLOTTER_GUI_H
#define C__CRESD_SOURCE_PLOTTER_PLOTTER_GUI_H
#include <winlib/popup.h>
#include <winlib/frame.h>
#include <winlib/scrollFrame.h>
#include <winlib/ControlW.h>
#include <winlib/xmlEditorChild.h>
#include <winlib/chartWin.h>
#include <winlib/gridView.h>

#include <winlib/winApp.h>

namespace winlibGUI {

	const int ControlCHILD_id=137;
	const int EditFunction1_id=134;
	const int EditFunction2_id=135;
	const int EditFunction3_id=136;
	const int EditXmax_id=130;
	const int EditXmin_id=129;
	const int EditYmax_id=132;
	const int EditYmin_id=131;
	const int PaintBox_id=138;
	const int PlotterFORM_id=128;
	const int PUSHrefresh_id=133;

	class GuiApplication : public winlib::Application {
		public:
		virtual gak::xml::Document *getGuiDoc();
		GuiApplication(int iconID=-1) : winlib::Application(iconID) {}
	};

	class PlotterFORM_form : public winlib::OverlappedWindow {
		public:
		PlotterFORM_form(winlib::BasicWindow *owner) : OverlappedWindow(owner) {}
		winlib::SuccessCode create(winlib::BasicWindow*parent) {
			return OverlappedWindow::create(parent,"PlotterFORM");
		}

		winlib::EditControl *EditXmin;
		winlib::EditControl *EditXmax;
		winlib::EditControl *EditYmin;
		winlib::EditControl *EditYmax;
		winlib::PushButton *PUSHrefresh;
		winlib::EditControl *EditFunction1;
		winlib::EditControl *EditFunction2;
		winlib::EditControl *EditFunction3;
		winlib::FrameChild *ControlCHILD;
		winlib::FrameChild *PaintBox;
		private:
		virtual void getControls();
	};	// end of PlotterFORM
}	// namespace winlibGUI

#endif // C__CRESD_SOURCE_PLOTTER_PLOTTER_GUI_H
