#include "GameplayGameState.h"
#include "raylib.h"

void GameplayGameState::Init()
{
	game_music = LoadMusicStream("data/sacredwar.ogg");
	game_music.looping = true;
	bg = LoadTexture("data/sprites/battlefield.png");
	RegisterActor(new Player());
	gameplaytimestamp = GetTime();
	SetMusicVolume(game_music, 0.2);
	PlayMusicStream(game_music);
}

void GameplayGameState::Think()
{
	UpdateMusicStream(game_music);
	std::vector<Actor*> hihitlers;
	std::vector<Actor*> bullets;
	ClearBackground(GREEN);
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
				//DeregisterActor((*it));
				prosrano_vec = (*it)->GetPosition();
				prosrano += 1; // За каждого упущенноного хихитлера начисляем просро-очки.
			}
		}
	}
	if (prosrano >= 1) {
		if (prosranotics == 4) {
			rt = LoadRenderTexture(800, 600);
			StopMusicStream(game_music);
			oops = LoadSound("data/scratch.wav");
			PlaySoundMulti(oops);
			freezeframe = true;
		}
		if (prosranotics == 1000) {
			for (auto it = actors.begin(); it != actors.end(); it++) {
				delete (*it);
			}
			actors.clear();
			pending_actors.clear();
			dereg_pending_actors.clear();
			globalscore = score;
		}

		if (prosranotics > 1 && prosranotics < 300) {
			BeginTextureMode(rt);
			ClearBackground(BLACK);
			BeginBlendMode(BLEND_SUBTRACT_COLORS);
			DrawCircle(prosrano_vec.x, GetScreenHeight() - prosrano_vec.y, prosranoradius, CLITERAL(Color){255, 255, 255, 255});
			EndBlendMode();
			EndTextureMode();
			prosranoradius -= 7;
		}

		if (prosranotics > 600 && prosranotics <= 850) {
			BeginTextureMode(rt);
			ClearBackground(BLACK);
			BeginBlendMode(BLEND_SUBTRACT_COLORS);
			if(850 - prosranotics > 0)
				DrawCircle(prosrano_vec.x, GetScreenHeight() - prosrano_vec.y, prosranoradius, CLITERAL(Color){255, 255, 255, 255});
			EndBlendMode();
			EndTextureMode();
			prosranoradius -= 8;
		}
		if(prosranoradius < 0 && !IsSoundPlaying(oops) && prosranoradius > -1000){
			oops = LoadSound("data/hihitler_sounds/speak2.wav");
			PlaySoundMulti(oops);
			prosranoradius = -1000;
		}

		if (prosranotics > 1200) {
			freezeframe = false;
			StopSoundMulti();
			UnloadSound(oops);
			UnloadRenderTexture(rt);
			SwitchGameState(new EndGameState());
		}

		DrawTexture(rt.texture, 0, 0, WHITE);
		//DrawCircle(prosrano_vec.x, prosrano_vec.y, 300 - prosranotics, CLITERAL(Color){255, 0, 0, 255});
		prosranotics += 4;
		return;
	}
	// Проверка колизии. (сложнааа)
	for (auto b_it = bullets.begin(); b_it != bullets.end(); b_it++) {
		for (auto h_it = hihitlers.begin(); h_it != hihitlers.end(); h_it++) {
			Rectangle bullet_rec = { (*b_it)->GetPosition().x - (*b_it)->GetOrigin().x, (*b_it)->GetPosition().y - (*b_it)->GetOrigin().y, (*b_it)->GetOrigin().x * 2, (*b_it)->GetOrigin().y * 2 };
			Rectangle hihitler_rec = { (*h_it)->GetPosition().x - (*h_it)->GetOrigin().x, (*h_it)->GetPosition().y - (*h_it)->GetOrigin().y, (*h_it)->GetOrigin().x * 2, (*h_it)->GetOrigin().y * 2};
			//DrawRectangleRec(bullet_rec, YELLOW);
			//DrawRectangleRec(hihitler_rec, RED);
			if (CheckCollisionRecs(bullet_rec, hihitler_rec)) {
				(*h_it)->Die(); // Only Enemy Has Die()!!
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
	DrawTextEx(DefaultFont, TextFormat("Enemy Speed: %f pixels/s", (float)std::min<double>(((70 + (GetTime() - gameplaytimestamp) * 3) * GetFrameTime()), MAX_ENEMY_SPEED)), CLITERAL(Vector2){0, 575}, 25, 1, WHITE);
	m_spawntics += 1;
}

void GameplayGameState::Destroy()
{
	actors.clear();
	pending_actors.clear();
	dereg_pending_actors.clear();
	globalscore = score;
	StopSoundMulti();
	StopMusicStream(game_music);
	UnloadMusicStream(game_music);
	UnloadTexture(bg);
}

GameplayGameState::GameplayGameState()
{
}

GameplayGameState::~GameplayGameState()
{
}
