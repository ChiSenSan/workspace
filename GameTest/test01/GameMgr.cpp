#include <DxLib.h>
#include "GameMgr.h"
#include "Button.h"
#include "Mouse.h"

void GameMgr::Main(){
	ChangeWindowMode(TRUE),DxLib_Init(),SetDrawScreen(DX_SCREEN_BACK);

	mPrevButton = new Button(320,200,100,50,"前へ");
	mPrevButton->SetOnClickListener(this);

	mNextButton = new Button(440,200,100,50,"次へ");
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
		printfDx("「前へ」が押されました\n");
	}
	if(view==mNextButton){
		printfDx("「次へ」が押されました\n");
	}
}