#include <DxLib.h>
#include "GameMgr.h"
#include "Button.h"
#include "Mouse.h"

void GameMgr::Main(){
	ChangeWindowMode(TRUE),DxLib_Init(),SetDrawScreen(DX_SCREEN_BACK);

	mPrevButton = new Button(320,200,100,50,"�O��");
	mPrevButton->SetOnClickListener(this);

	mNextButton = new Button(440,200,100,50,"����");
	mNextButton->SetOnClickListener(this);

	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){
		Mouse::Instance()->Update();
		mPrevButton->Update();
		mNextButton->Update();
		mPrevButton->Draw();
		mNextButton->Draw();
	}

	delete mPrevButton;
	delete mNextButton;
	DxLib_End();
}

void GameMgr::OnClick(View* view){
	if(view==mPrevButton){
		printfDx("�u�O�ցv��������܂���\n");
	}
	if(view==mNextButton){
		printfDx("�u���ցv��������܂���\n");
	}
}