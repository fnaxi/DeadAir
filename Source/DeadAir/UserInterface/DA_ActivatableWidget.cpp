// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_ActivatableWidget.h"

TOptional<FUIInputConfig> UDA_ActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case EDA_WidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
		
	case EDA_WidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
		
	case EDA_WidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		
	case EDA_WidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}

