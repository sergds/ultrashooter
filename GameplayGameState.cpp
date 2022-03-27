#include "GameplayGameState.h"

void GameplayGameState::Init()
{
	bg = LoadTexture("data/sprites/battlefield.png");
	RegisterActor(new Player());
}

void GameplayGameState::Think()
{
	DrawTexture(bg, 0, 0, WHITE);
	//player.Think();
	//testenemy.Think();

	// Даём всем зареганным акторам подумать.
	for (auto it = actors.begin(); it != actors.end(); it++) {
		(* it)->Think();
		if ((*it)->GetName() == "Bullet") { // Если пуля
	// Проверяем высоту и уничтожаем если выше края экрана
			if ((*it)->GetPosition().y <= 0) {
				DeregisterActor((*it));
			}
		}
	}
	// Обрабатываем акторов в очередях на удаление/регистрацию
	ProcessActors();

	DrawTextEx(DefaultFont, TextFormat("Score: %i", score), CLITERAL(Vector2){0, 25}, 25, 1, WHITE);
	DrawTextEx(DefaultFont, TextFormat("Lost: %i", prosrano), CLITERAL(Vector2){0, 55}, 25, 1, WHITE);
}

void GameplayGameState::Destroy()
{
	UnloadTexture(bg);
}

GameplayGameState::GameplayGameState()
{
}

GameplayGameState::~GameplayGameState()
{
}
