#include <DxLib.h>
#include "Button.h"
#include "Mouse.h"

Button::Button(int x, int y, int w, int h, const char* str) : 
 mListener(NULL)
,IsPressed(false)
{
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	mStr = str;
}

void Button::Update(){
	int x = Mouse::Instance()->GetX();
	int y = Mouse::Instance()->GetY();
	if(Mouse::Instance()->GetPressingCount(Mouse::LEFT)==0){
		IsPressed = false;
	}
	if(Mouse::Instance()->GetPressingCount(Mouse::LEFT)==1){
		if(mX<=x && x<=mX+mW && mY<=y && y<=mY+mH){
			mListener->OnClick(this);
			IsPressed =true;
		}
	}
	if(!(mX<=x && x<=mX+mW && mY<=y && y<=mY+mH)){
		IsPressed = false;
	}
}

void Button::Draw(){
	int sub=0;
	if(IsPressed){
		sub = 2;
	}
	int strW = GetDrawStringWidth(mStr, strlen(mStr));
	DrawBox(mX+sub, mY+sub, mX+mW-sub, mY+mH-sub, GetColor(100,255,255),TRUE);
	DrawBox(mX+sub, mY+sub, mX+mW-sub, mY+mH-sub, GetColor(255,100,100),FALSE);
	int strX = mX+mW/2-strW/2;
	int strY = mY+mH/2-DEFAULT_FONT_SIZE/2;
	DrawString(strX,strY,mStr,GetColor(0,0,0)); 
}

void Button::SetOnClickListener(OnClickListener* listener){
	mListener = listener;
}
