#include <NotificationBar.h>

np::NotificationBar::NotificationBar( CEGUI::WindowManager* wmgr )
{
	text = "";

	this->wmgr = wmgr;

	


	textWindow = wmgr->createWindow("TaharezLook/StaticText", "NotificationBar/Text");
	textWindow->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	textWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0, 600), CEGUI::UDim(0, 60)));
	textWindow->setFont("Text");
	textWindow->setAlpha(0.5);

	sheet = textWindow;
}

void np::NotificationBar::setText( std::string newText )
{
	text = newText;

	textWindow->setText(text);
}

void np::NotificationBar::show()
{
	sheet->setVisible(true);
}

void np::NotificationBar::hide()
{
	sheet->setVisible(false);
}

