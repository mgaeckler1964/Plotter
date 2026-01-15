/*
	this file was created from C:\CRESD\Source\Plotter\Plotter.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/

#include "C:\CRESD\Source\Plotter\Plotter.gui.h"

namespace winlibGUI {

	gak::xml::Document *GuiApplication::getGuiDoc() {
		gak::xml::Document *doc = winlib::Application::getGuiDoc();
		if(!doc) {
			gak::STRING xmlSrc = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
"<gui>\n"
"<forms>\n"
"<form name=\"PlotterFORM\" style=\"277807104\" width=\"777\" height=\"603\" caption=\"Function plotter\" id=\"128\" baseClass=\"OverlappedWindow\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layoutManager type=\"AttachmentManager\" />\n"
"<child type=\"FrameChild\" name=\"ControlCHILD\" caption=\"\" x=\"0\" y=\"0\" width=\"760\" height=\"145\" style=\"1342308352\" id=\"137\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout attachment=\"1\" growHeight=\"0\" x=\"0\" y=\"0\" growWidth=\"1\" />\n"
"<layoutManager type=\"TableManager\" marginLeft=\"4\" marginRight=\"4\" marginTop=\"4\" marginBottom=\"4\" />\n"
"<child type=\"Label\" name=\"\" caption=\"X-Interval\" x=\"20\" y=\"29\" width=\"0\" height=\"0\" style=\"1342242827\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout x=\"0\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditXmin\" caption=\"-5\" x=\"96\" y=\"16\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"129\">\n"
"<layout x=\"1\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"2\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditXmax\" caption=\"+5\" x=\"208\" y=\"21\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"130\">\n"
"<layout x=\"2\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"2\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"Y-Intervall\" x=\"322\" y=\"27\" width=\"80\" height=\"25\" style=\"1342242827\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout x=\"3\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditYmin\" caption=\"-5\" x=\"428\" y=\"23\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"131\">\n"
"<layout x=\"4\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"2\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditYmax\" caption=\"+5\" x=\"564\" y=\"32\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"132\">\n"
"<layout x=\"5\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"2\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"PushButton\" name=\"PUSHrefresh\" caption=\"Aktualisieren\" x=\"678\" y=\"41\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"133\">\n"
"<layout x=\"6\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"f(x)=\" x=\"21\" y=\"65\" width=\"80\" height=\"25\" style=\"1342242827\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout x=\"0\" y=\"1\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditFunction1\" caption=\"sin(x)\" x=\"129\" y=\"38\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"134\">\n"
"<layout x=\"1\" y=\"1\" width=\"5\" height=\"1\" growWidth=\"2\" growHeight=\"0\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditFunction2\" caption=\"cos(x)\" x=\"140\" y=\"77\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"135\">\n"
"<layout x=\"1\" y=\"2\" width=\"5\" growWidth=\"2\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"EditFunction3\" caption=\"tan(x)\" x=\"132\" y=\"123\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"136\">\n"
"<layout x=\"1\" y=\"3\" width=\"5\" growWidth=\"2\" paddingLeft=\"4\" paddingRight=\"4\" paddingTop=\"4\" paddingBottom=\"4\" />\n"
"</child>\n"
"</child>\n"
"<child type=\"FrameChild\" name=\"PaintBox\" caption=\"\" x=\"136\" y=\"323\" width=\"80\" height=\"25\" style=\"1342308352\" id=\"138\">\n"
"<layout attachment=\"4\" y=\"1\" growWidth=\"10\" growHeight=\"10\" />\n"
"</child>\n"
"</form>\n"
"</forms>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return doc;
	}


	void PlotterFORM_form::getControls() {
		EditXmin=static_cast<winlib::EditControl*>(findChild(EditXmin_id));
		EditXmax=static_cast<winlib::EditControl*>(findChild(EditXmax_id));
		EditYmin=static_cast<winlib::EditControl*>(findChild(EditYmin_id));
		EditYmax=static_cast<winlib::EditControl*>(findChild(EditYmax_id));
		PUSHrefresh=static_cast<winlib::PushButton*>(findChild(PUSHrefresh_id));
		EditFunction1=static_cast<winlib::EditControl*>(findChild(EditFunction1_id));
		EditFunction2=static_cast<winlib::EditControl*>(findChild(EditFunction2_id));
		EditFunction3=static_cast<winlib::EditControl*>(findChild(EditFunction3_id));
		ControlCHILD=static_cast<winlib::FrameChild*>(findChild(ControlCHILD_id));
		PaintBox=static_cast<winlib::FrameChild*>(findChild(PaintBox_id));
	}	// PlotterFORM
}	// namespace winlibGUI
