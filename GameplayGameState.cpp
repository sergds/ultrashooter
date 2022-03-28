#include "GameplayGameState.h"

void GameplayGameState::Init()
{
	music = LoadMusicStream("data/sacredwar.ogg");
	music.looping = true;
	bg = LoadTexture("data/sprites/battlefield.png");
	RegisterActor(new Player());
	gameplaytimestamp = GetTime();
	SetMusicVolume(music, 0.5);
	PlayMusicStream(music);
}

void GameplayGameState::Think()
{
	std::vector<Actor*> hihitlers;
	std::vector<Actor*> bullets;
	DrawTexture(bg, 0, 0, WHITE);
	//player.Think();
	//testenemy.Think();
	if (m_spawntics >= 30) {
		RegisterActor(new Enemy());
		m_spawntics = 0;
	}

	// Даём всем зареганным акторам подумать.
	for (auto it = actors.begin(); it != actors.end(); it++) {
		(* it)->Think();
		if ((*it)->GetName() == "Bullet") { // Если пуля
			// Сохраняем для будущей проверки коллизии с хихитлерами.
			bullets.emplace_back((*it));
	// Проверяем высоту и уничтожаем если выше края экрана
			if ((*it)->GetPosition().y <= 0) {
				DeregisterActor((*it));
			}
		}
		if ((*it)->GetName() == "Enemy") { // Если хихитлер
			// Сохраняем для будущей проверки коллизии с пулями.
			hihitlers.emplace_back((*it));
	// Проверяем высоту и уничтожаем если ниже края экрана
			if ((*it)->GetPosition().y >= 600) {
				DeregisterActor((*it));
				prosrano += 1; // За каждого упущенноного хихитлера начисляем просро-очки.
			}
		}
	}
	// Проверка колизии. (сложнааа)
	for (auto b_it = bullets.begin(); b_it != bullets.end(); b_it++) {
		for (auto h_it = hihitlers.begin(); h_it != hihitlers.end(); h_it++) {
			Rectangle bullet_rec = { (*b_it)->GetPosition().x - (*b_it)->GetOrigin().x, (*b_it)->GetPosition().y - (*b_it)->GetOrigin().y, (*b_it)->GetOrigin().x * 2, (*b_it)->GetOrigin().y * 2 };
			Rectangle hihitler_rec = { (*h_it)->GetPosition().x - (*h_it)->GetOrigin().x, (*h_it)->GetPosition().y - (*h_it)->GetOrigin().y, (*h_it)->GetOrigin().x * 2, (*h_it)->GetOrigin().y * 2};
			//DrawRectangleRec(bullet_rec, YELLOW);
			//DrawRectangleRec(hihitler_rec, RED);
			if (CheckCollisionRecs(bullet_rec, hihitler_rec)) {
				DeregisterActor(*b_it);
				DeregisterActor(*h_it);
				score += 1;
			}
		}
	}

	// Обрабатываем акторов в очередях на удаление/регистрацию
	ProcessActors();

	DrawTextEx(DefaultFont, TextFormat("Score: %i", score), CLITERAL(Vector2){0, 25}, 25, 1, WHITE);
	//DrawTextEx(DefaultFont, TextFormat("Lost: %i", prosrano), CLITERAL(Vector2){0, 55}, 25, 1, WHITE);
	DrawTextEx(DefaultFont, TextFormat("Enemy Speed: %f pixels/s", (float)std::min<double>(((70 + (GetTime() - gameplaytimestamp)) * GetFrameTime()), 4)), CLITERAL(Vector2){0, 575}, 25, 1, WHITE);
	m_spawntics += 1;
	if (prosrano >= 1) {
		for (auto it = actors.begin(); it != actors.end(); it++) {
			delete (*it);
		}
		actors.clear();
		pending_actors.clear();
		dereg_pending_actors.clear();
		globalscore = score;
		SwitchGameState(new EndGameState());
	}
}

void GameplayGameState::Destroy()
{
	actors.clear();
	pending_actors.clear();
	dereg_pending_actors.clear();
	globalscore = score;
	StopMusicStream(music);
	UnloadMusicStream(music);
	UnloadTexture(bg);
}

GameplayGameState::GameplayGameState()
{
}

GameplayGameState::~GameplayGameState()
{
}
