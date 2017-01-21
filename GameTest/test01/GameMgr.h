#pragma once

#include "OnClickListener.h"
#include "Button.h"

class GameMgr : public OnClickListener {
	Button *mPrevButton;
	Button *mNextButton;
public:
	void Main();
	void OnClick(View* view)override;
};