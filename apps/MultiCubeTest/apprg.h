#pragma once

#include "app.h"

class AppRG : public App {
public:
	AppRG(Options const& o = Options());
	virtual void draw();
private:
	virtual void init();
};