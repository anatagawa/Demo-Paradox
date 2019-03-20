#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include "starfield.h"
#include <time.h>
#include "data.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Vector2 Screen = (Vector2) { 640, 480 };
Vector2 VirtualScreen = (Vector2) { 640, 480 };

void DrawFrameBuffer(RenderTexture2D renderer);

// -------------------------------------------------------------------------------------------------------------
// Main Game
// -------------------------------------------------------------------------------------------------------------

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow( GetMonitorWidth(0), GetMonitorHeight(0),"Demo Paradox");
	SetWindowMinSize(Screen.x, Screen.y);
	HideCursor();

	InitAudioDevice();

	// -------------------------------------------------------------------------------------------------------------
	// Icone window
	// -------------------------------------------------------------------------------------------------------------

	Image icon = LoadImagePro( icon_data, 32, 32, UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);
	UnloadImage(icon);

	// -------------------------------------------------------------------------------------------------------------
	// font data
	// -------------------------------------------------------------------------------------------------------------

	Image _font_data = LoadImagePro(font_data, 16, 946, UNCOMPRESSED_R8G8B8A8);
	Texture2D font_data = LoadTextureFromImage(_font_data);
	UnloadImage(_font_data);

	// -------------------------------------------------------------------------------------------------------------
	// bar data
	// -------------------------------------------------------------------------------------------------------------

	Image _bar_data = LoadImagePro(bars_data, 4, 480, UNCOMPRESSED_R8G8B8A8);
	Texture2D bar_data = LoadTextureFromImage(_bar_data);
	UnloadImage(_bar_data);

	// -------------------------------------------------------------------------------------------------------------
	// Select bar
	// -------------------------------------------------------------------------------------------------------------

	Image _select_data = LoadImagePro(select_data, 4, 14, UNCOMPRESSED_R8G8B8A8);
	Texture2D select_bar = LoadTextureFromImage(_select_data);
	UnloadImage(_select_data);

	// -------------------------------------------------------------------------------------------------------------
	// Blend grey bar
	// -------------------------------------------------------------------------------------------------------------

	Image _grey_data = LoadImagePro(grey_data, 640, 4, UNCOMPRESSED_R8G8B8A8);
	Texture2D grey_bar = LoadTextureFromImage(_grey_data);
	UnloadImage(_grey_data);

	// -------------------------------------------------------------------------------------------------------------
	// Balles
	// -------------------------------------------------------------------------------------------------------------

	Image _balle1_data = LoadImagePro(ball1_data, 30, 30, UNCOMPRESSED_R8G8B8A8);
	Texture2D balle1 = LoadTextureFromImage(_balle1_data);
	UnloadImage(_balle1_data);

	Image _balle2_data = LoadImagePro(ball2_data, 22, 22, UNCOMPRESSED_R8G8B8A8);
	Texture2D balle2 = LoadTextureFromImage(_balle2_data);
	UnloadImage(_balle2_data);

	Image _balle3_data = LoadImagePro(ball3_data, 18, 18, UNCOMPRESSED_R8G8B8A8);
	Texture2D balle3 = LoadTextureFromImage(_balle3_data);
	UnloadImage(_balle3_data);

	// -------------------------------------------------------------------------------------------------------------
	// Framebuffer
	// -------------------------------------------------------------------------------------------------------------

	RenderTexture2D frameBuffer = LoadRenderTexture( VirtualScreen.x, VirtualScreen.y );
	SetTextureFilter(frameBuffer.texture, FILTER_POINT);

	RenderTexture2D frameBufferBlend = LoadRenderTexture( VirtualScreen.x, VirtualScreen.y );
	SetTextureFilter(frameBufferBlend.texture, FILTER_POINT);

	// -------------------------------------------------------------------------------------------------------------
	// Music
	// -------------------------------------------------------------------------------------------------------------

	Music music = LoadMusicStream("zic.mod");
	PlayMusicStream(music);
	SetMusicVolume(music, 0.05f);

	// -------------------------------------------------------------------------------------------------------------
	// Divers
	// -------------------------------------------------------------------------------------------------------------

	SetTargetFPS(60);

	float sinx = 0;
	float siny = 0;
	float oldsinx = 0;
	float oldsiny = 0;

	char * text1 =  "    PARADOX PROUDLY PRESENTS    \n" \
					"        COUNT DUCKULA +         \n" \
					" TRAINED BY SHAPIRO OF PARADOX  \n" \
					"                                \n" \
					"       GREETS TO THE BEST       \n" \
					"      SKID ROW - FAIRLIGHT      \n" \
					"                                \n" \
					"                                \n" \
					"     UNLIMITED TIME      NO     \n" \
					"          START DUCKULA         \n" \
					"                                \n" \
					"   MADE BY ANATA WITH RAYLIB    \n";

	char *scrollText = "PARADOX PROUDLY PRESENTS -- COUNT DUCKULA + --      TRAINER,INTRO AND MUSIC RIP BY SHAPIRO OF PARADOX              THIS GAME WAS CRACKED BY N.O.M.A.D OF GENESIS                                      TO CONTACT PARADOX CALL THEESE COOL BOARDS          SLEEPY HOLLOW - 703 276 0724        INVOLUNTARY DEATH - 708 599 1537       HALLOWED GROUND - (45) 4343 9398       MIDDLE EARTH - 801 822 4215         PARADOX CANADA - 418 843 5174         THE JUNGLE - 708 983 5764                        OR WRITE TO        BP 110 - 7700 MOUSCRON 1 - BELGIUM             OR         T.N.B. - POST BOX 560 - 2620 ALBERTSLUND - DENMARK             OR          P.O.BOX 2221 - BRIDGEVIEW, IL - 60455 USA              CUL8R                        ";

	Starfield2D starfield1 = Init_Starfield2D(balle1, (Vector2) {-64,-64}, (Vector2) {768,608});
	Starfield2D starfield2 = Init_Starfield2D(balle2, (Vector2) {-64,-64}, (Vector2) {768,608});
	Starfield2D starfield3 = Init_Starfield2D(balle3, (Vector2) {-64,-64}, (Vector2) {768,608});

	SetSpeed_Starfield2D(&starfield1, (Vector2){4,0});
	SetSpeed_Starfield2D(&starfield2, (Vector2){2,0});
	SetSpeed_Starfield2D(&starfield3, (Vector2){1,0});

	float ySin[strlen(scrollText)];
	float sinparam = 0;
	float textX = VirtualScreen.x;
	int textLen = strlen(scrollText);

	// -------------------------------------------------------------------------------------------------------------
	// Game Loop
	// -------------------------------------------------------------------------------------------------------------
	while(!WindowShouldClose()) {
		UpdateMusicStream(music);

		oldsinx = sinx;
		oldsiny = siny;

		sinparam += 0.04f;
		float x = sinparam;

		for (int i = 0; i < textLen; i++) {
			ySin[i] = (float)sin(x*2)*12;
			x += ((PI*2) / 24);
		}

		textX -= 2;
		if(textX < -textLen*16 ) textX = VirtualScreen.x;

		// -------------------------------------------------------------------------------------------------------------
		// Framebuffer
		// -------------------------------------------------------------------------------------------------------------

		// Text Effect
		BeginTextureMode(frameBufferBlend);
			ClearBackground(BLANK);

			// -------------------------------------------------------------------------------------------------------------
			// Scroll Text
			// -------------------------------------------------------------------------------------------------------------

			for(int i=0; i < textLen; i++) {
				if(textX + ( i * 16 + 1 ) < VirtualScreen.x-16 && textX + ( i * 16 + 1 ) > 16) {
					DrawTexturePro(
						font_data,
						(Rectangle) { 0, (scrollText[i] - 32) * 16, 16, 16 },
						(Rectangle) { textX + ( i * 16 + 1 ) , 320 + ySin[i] , 16, 16 },
						(Vector2) {0},
						0,
						WHITE
					);
				}
			}

			BeginBlendMode(BLEND_MULTIPLIED);
				DrawTextureQuad(grey_bar, (Vector2){1,16}, (Vector2){0},(Rectangle){0,300,VirtualScreen.x,64}, WHITE);
			EndBlendMode();

		EndTextureMode();

		BeginTextureMode(frameBuffer);
		{
			ClearBackground(BLANK);

			// -------------------------------------------------------------------------------------------------------------
			// Draw Starfield with balle texture
			// -------------------------------------------------------------------------------------------------------------

			Draw_Starfield2D(&starfield3, (Vector2){1,0});
			Draw_Starfield2D(&starfield2, (Vector2){1,0});
			Draw_Starfield2D(&starfield1, (Vector2){1,0});

			// -------------------------------------------------------------------------------------------------------------
			// FrameBuffer with blend
			// -------------------------------------------------------------------------------------------------------------

			DrawTexturePro (
				frameBufferBlend.texture,
				(Rectangle) { 0.0f, 0.0f, (float)frameBufferBlend.texture.width, (float)-frameBufferBlend.texture.height },
				(Rectangle) { 0 , 52, (float)frameBufferBlend.texture.width, (float)frameBufferBlend.texture.height },
				(Vector2) { 0, 0 },
				0.0f,
				WHITE
			);

			// -------------------------------------------------------------------------------------------------------------
			// Draw Bar
			// -------------------------------------------------------------------------------------------------------------

			DrawTextureQuad(bar_data, (Vector2){160,1}, (Vector2){0},(Rectangle){0,0,VirtualScreen.x,VirtualScreen.y},WHITE);

			// -------------------------------------------------------------------------------------------------------------
			// Draw Sine Flag
			// -------------------------------------------------------------------------------------------------------------

			for(int y = 100; y < 400; y += 40) {
				for(int x = 60; x < 580; x += 20) {
					DrawRectangle(x+sin(sinx) * 32, y + sin(siny) * 32 , 3, 3, (Color) { 85,153,255,255 } );
					sinx += 0.3;
					siny += 0.2;
				}
				siny += 0.5;
				sinx = oldsinx;
			}

			sinx = oldsinx + 0.08;
			siny = oldsiny + 0.1;


			// -------------------------------------------------------------------------------------------------------------
			// Draw Select Bar
			// -------------------------------------------------------------------------------------------------------------

			DrawTextureQuad(select_bar, (Vector2){160,1}, (Vector2){0},(Rectangle){0,282,VirtualScreen.x,14},WHITE);

			// -------------------------------------------------------------------------------------------------------------
			// Draw Page Text
			// -------------------------------------------------------------------------------------------------------------

			Vector2 textOffset = { 0, 0 };

			for(int i = 0; i < strlen(text1); i++) {
				if( (unsigned char)text1[i] == '\n') {
					textOffset.y += 18;
					textOffset.x = 0-(i*16);
				} else {
					DrawTexturePro(
						font_data,
						(Rectangle) { 0, (text1[i] - 32) * 16, 16, 16 },
						(Rectangle) { 60+textOffset.x + ( i * 16 + 1 ) , 120+textOffset.y , 16, 16 },
						(Vector2) {0},
						0,
						WHITE
					);
				}
			}
		}
		EndTextureMode();

		BeginDrawing();
		{
			ClearBackground(BLACK);

			// -------------------------------------------------------------------------------------------------------------
			// Draw final frameBuffer
			// -------------------------------------------------------------------------------------------------------------

			DrawFrameBuffer(frameBuffer);
		}
		EndDrawing();
	}

	UnloadTexture(bar_data);
	UnloadTexture(font_data);
	UnloadTexture(select_bar);
	UnloadTexture(grey_bar);
	UnloadTexture(balle1);
	UnloadTexture(balle2);
	UnloadTexture(balle3);
	UnloadRenderTexture(frameBuffer);
	UnloadRenderTexture(frameBufferBlend);
	UnloadMusicStream(music);
	CloseWindow();
	return 0;
}

// -------------------------------------------------------------------------------------------------------------
// UPDATE BUFFER
// -------------------------------------------------------------------------------------------------------------

void DrawFrameBuffer(RenderTexture2D renderer) {
	float verticalScale = GetScreenHeight () / VirtualScreen.y;
	float horizontalScale = GetScreenWidth () / VirtualScreen.x;
	float scale = min (horizontalScale, verticalScale);

	DrawTexturePro (
		renderer.texture,
		(Rectangle) { 0.0f, 0.0f, (float)renderer.texture.width, (float)-renderer.texture.height },
		(Rectangle) { ( GetScreenWidth () - ( VirtualScreen.x*scale) ) * 0.5 , ( GetScreenHeight () - (VirtualScreen.y * scale) ) * 0.5, VirtualScreen.x * scale, VirtualScreen.y * scale },
		(Vector2) { 0, 0 },
		0.0f,
		WHITE
	);
}
