#pragma once

class View {
public:
	View();
	virtual ~View();
	virtual void Update();
	virtual void Draw();
};