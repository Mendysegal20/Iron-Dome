#pragma once
#include <raylib.h>
#include "Constants.h"
#include <cmath>





class Explosion {

public:

	Explosion() = default;
    Explosion(const Vector2& pos);

    void update(const float dt);
    void draw() const;
    bool isActive() const;
	static void loadExplosionTexture();
	static void unloadExplosionTexture();

private:

    static Texture2D explosionTexture;
    Vector2 position;
    float lifetime = 0.7f;
    float currentTime = 0.0f;
    bool active;
};
