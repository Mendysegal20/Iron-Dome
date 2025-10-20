#include "Explosion.h"
#include "Constants.h"


Texture2D Explosion::explosionTexture = { 0 };




Explosion::Explosion(const Vector2& pos) 
	: position(pos), active(true) {}




void Explosion::update(const float dt)
{
	currentTime += dt;
	if (currentTime >= lifetime) active = false;
}




bool Explosion::isActive() const
{
	return active;
}





void Explosion::draw() const
{
	
	if (!active) return;

	float progress = currentTime / lifetime; // 0 -> 1

	// ���� ����� ��� ������
	float scale = 0.7f + 0.7f * progress; // ����� �-0.5, ��� �� 1.0

	// ���� �����: ������ ����� �� ����
	float alpha = 1.0f - progress; // 1.0 ������ ������, 0 ����

	Vector2 drawPos = {
		position.x - explosionTexture.width * scale / 2.0f,
		position.y - explosionTexture.height * scale / 2.0f
	};

	DrawTextureEx(explosionTexture, drawPos, 0.0f, scale, { 255, 255, 255, static_cast<unsigned char>(255 * alpha) });
}





void Explosion::loadExplosionTexture()
{
	
	if (explosionTexture.id == 0)
	{
		Image img = LoadImage(constants::explosionTexture);
		explosionTexture = LoadTextureFromImage(img);
		UnloadImage(img);
	}
}





void Explosion::unloadExplosionTexture()
{
	if (explosionTexture.id != 0)
	{
		UnloadTexture(explosionTexture);
		explosionTexture.id = 0;
	}
}
