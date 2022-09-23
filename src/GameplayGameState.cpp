#include "GameplayGameState.h"

void GameplayGameState::Init()
{
	game_music = LoadMusicStream("data/sacredwar.ogg");
	game_music.looping = true;
	bg = LoadTexture("data/sprites/battlefield.png");
	RegisterActor(new Player());
	gameplaytimestamp = GetTime();
	SetMusicVolume(game_music, 0.3);
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

	// ��� ���� ���������� ������� ��������.
	for (auto it = actors.begin(); it != actors.end(); it++) {
		(* it)->Think();
		if ((*it)->GetName() == "Bullet") { // ���� ����
			// ��������� ��� ������� �������� �������� � �����������.
			bullets.emplace_back((*it));
	// ��������� ������ � ���������� ���� ���� ���� ������
			if ((*it)->GetPosition().y <= 0) {
				DeregisterActor((*it));
			}
		}
		if ((*it)->GetName() == "Enemy") { // ���� ��������
			// ��������� ��� ������� �������� �������� � ������.
			hihitlers.emplace_back((*it));
	// ��������� ������ � ���������� ���� ���� ���� ������
			if ((*it)->GetPosition().y >= 600) {
				//DeregisterActor((*it));
				prosrano_vec = (*it)->GetPosition();
				prosrano += 1; // �� ������� ������������ ��������� ��������� ������-����.
			}
		}
	}
	if (prosrano >= 1) {
		if (prosranotics == 1) {
			rt = LoadRenderTexture(800, 600);
			StopMusicStream(game_music);
			freezeframe = true;
		}
		if (prosranotics == 290) {
			for (auto it = actors.begin(); it != actors.end(); it++) {
				delete (*it);
			}
			actors.clear();
			pending_actors.clear();
			dereg_pending_actors.clear();
			globalscore = score;
		}

		if (prosranotics > 1) {
			BeginTextureMode(rt);
			ClearBackground(BLACK);
			BeginBlendMode(BLEND_SUBTRACT_COLORS);
			DrawCircle(prosrano_vec.x, GetScreenHeight() - prosrano_vec.y, 300 - prosranotics, CLITERAL(Color){255, 255, 255, 255});
			EndBlendMode();
			EndTextureMode();
		}

		DrawTexture(rt.texture, 0, 0, WHITE);
		//DrawCircle(prosrano_vec.x, prosrano_vec.y, 300 - prosranotics, CLITERAL(Color){255, 0, 0, 255});
		if (prosranotics > 300) {
			freezeframe = false;
			UnloadRenderTexture(rt);
			SwitchGameState(new EndGameState());
		}
		prosranotics += 1;
		return;
	}
	// �������� �������. (��������)
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

	// ������������ ������� � �������� �� ��������/�����������
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
