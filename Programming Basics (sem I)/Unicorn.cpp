#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define JUMP_HEIGHT		300
#define JUMP_SPEED		300
#define LEVEL_SPEED		250
#define FLY_SPEED		400
#define DASH_DURATION	0.5
#define JUMP_INCRESE	5000
#define ADD_TO_JUMP_MAX	100


// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
	};


// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};


// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};

struct rect {
	double x, y, w, h, distanceFromCamera;
};

struct jump {
	int jumpSpeed, jumpHeight, jumpsInARow, jump, stopJump;
	double takeCurrentHeight, jumpAbsoluteHeight, addToJump;
};

struct dash {
	int dash, canDash;
	double dashStartTime, dashHeight;
};

struct game {
	int quit, newGame, levelSpeed, frames, testingControls, platformsNr, bumpersNr, stalacNr;
	double delta, worldTime, fpsTimer, fps;
};

struct unicorn {
	int flySpeed, stopUnicorn, unicornMove, stopFalling, stopRising;
	double unicornOnGroundY;
};

double absolute(double value) {
	if (value < 0) {
		return -value;
	}
	return value;
}

int isColliding(rect a, rect b) {
	if (absolute(a.x - b.x) <= a.w / 2 + b.w / 2 && absolute(a.y - b.y) <= a.h / 2 + b.h / 2) {			//are colliding
		if (absolute(a.x - b.x) / (a.w / 2 + b.w / 2) > absolute(a.y - b.y) / (a.h / 2 + b.h / 2)) {		//it's side to side collision
			if (a.x < b.x) {
				return 1;		//collding side to side (a on the left)
			}
			return 0;		//collding side to side (a on the right)
		}
		if (a.y < b.y) {
			return 2;		//collinding top-bottom (a on top of b)
		}
		return 3;		//collinding top-bottom (a under b)
	}
	return 0;
}

void drawRects(SDL_Surface* screen, SDL_Surface* obstacle, rect obstacles[], int numberOfObstacles) {
	for (int i = 0; i < numberOfObstacles; i++) {
		DrawSurface(screen, obstacle, obstacles[i].x, obstacles[i].y);
	}
}

void moveRects(rect obstacles[], game *gameInfo, int numberOfObstacles) {
	for (int i = 0; i < numberOfObstacles; i++) {
		if (obstacles[i].x + obstacles[i].w / 2 > 0) {	
			obstacles[i].x -= gameInfo->levelSpeed * gameInfo->delta;
		}
		else {		//looping level
			obstacles[i].x += 5 * SCREEN_WIDTH;
		}
	}
}

void handleCollision(rect *unicornRec, rect obstacles[], unicorn *unicornParams, double delta, int numberOfRects) {
	for (int i = 0; i < numberOfRects; i++) {	
		if (isColliding(*unicornRec, obstacles[i]) == 1) {		//colliding side to side (unicorn bumping into the platform)
			unicornParams->stopUnicorn = 1;
		}
		else if (isColliding(*unicornRec, obstacles[i]) == 2) {		//colliding top to bottom (unicorn on top of the platfrom)
			if (unicornParams->flySpeed > 0) {
				unicornRec->y -= unicornParams->flySpeed * delta;
			}
		}
		else if (isColliding(*unicornRec, obstacles[i]) == 3) {		//colliding top to bottom (unicorn under the platform)
			if (unicornParams->flySpeed < 0) {
				unicornRec->y -= unicornParams->flySpeed * delta;
			}
		}
	}
}

void unicornMovment(rect* unicornRect, jump *jumpParams, dash *dashParams, game *gameInfo, unicorn *unicornParams) {
	if (gameInfo->testingControls) {
		unicornRect->y += unicornParams->flySpeed * gameInfo->delta;
		if (unicornRect->y - unicornRect->h / 2 < 0) {		//stop when escaping screen
			unicornRect->y -= unicornParams->flySpeed * gameInfo->delta;
		}
		else if (unicornRect->y + unicornRect->h / 2 > SCREEN_HEIGHT) {		//stop when escaping screen
			unicornRect->y -= unicornParams->flySpeed * gameInfo->delta;
		}
	}
	else {
		if (jumpParams->jump) {
			if (unicornRect->y >= jumpParams->jumpAbsoluteHeight - jumpParams->addToJump && !unicornParams->stopRising) {		//going up if there is nothing on top
				unicornRect->y -= jumpParams->jumpSpeed * gameInfo->delta;
			}
			else
			{
				jumpParams->jump = 0;
			}
		}
		else {
			if (unicornRect->y <= unicornParams->unicornOnGroundY && !unicornParams->stopFalling) {			//going down if there is nothing under
				unicornRect->y += jumpParams->jumpSpeed * gameInfo->delta;
				jumpParams->addToJump = 0;
			}
			else {
				jumpParams->jumpsInARow = 0;
				jumpParams->jump = 0;
				dashParams->canDash = 1;
			}
		}
		unicornParams->stopFalling = 0;
		unicornParams->stopRising = 0;
		if (dashParams->dash && gameInfo->worldTime - dashParams->dashStartTime < DASH_DURATION) {
			gameInfo->levelSpeed = 2 * LEVEL_SPEED;
			jumpParams->jumpsInARow = 1;		//adding possibilty to jump one more time after dash
			unicornRect->y = dashParams->dashHeight;
			jumpParams->jump = 0;
		}
		else if (!gameInfo->testingControls) {
			gameInfo->levelSpeed = LEVEL_SPEED;
			dashParams->dash = 0;
		}
	}
}

void cameraScrolling(rect *middleOfTheScreen, rect unicornRect, rect platforms[], double delta, int numberOfPlatforms) {
	if (middleOfTheScreen->y - unicornRect.y < -100) {	
		middleOfTheScreen->y += 1000 * delta;		//moving center of the view relative to unicorn position
	}
	if (middleOfTheScreen->y - unicornRect.y > 100) {
		middleOfTheScreen->y -= 1000 * delta;		//moving center of the view relative to unicorn position
	}
	for (int i = 0; i < numberOfPlatforms; i++) {
		platforms[i].y = platforms[i].distanceFromCamera - (middleOfTheScreen->y - SCREEN_HEIGHT / 2);		//moving platforms relative to be in view range
	}
}

//functions for giving starting values

void setJumpDefaultValues(jump* jump) {
	jump->jump = 0;
	jump->addToJump = 0;
	jump->takeCurrentHeight = 1;
	jump->jumpsInARow = 0;
	jump->stopJump = 0;
	jump->jumpSpeed = JUMP_SPEED;
	jump->jumpHeight = JUMP_HEIGHT;
	jump->jumpAbsoluteHeight = jump->jumpHeight;
}

void setGameDefaultValues(game* game) {
	game->newGame = 0;
	game->fps = 0;
	game->worldTime = 0;
	game->frames = 0;
	game->fpsTimer = 0;
	game->levelSpeed = 0;
	game->testingControls = 0;
}

void setUnicornDefaultValues(unicorn* unicornParams) {
	unicornParams->stopUnicorn = 0;
	unicornParams->unicornMove = 0;
	unicornParams->stopFalling = 0;
	unicornParams->flySpeed = 0;
	unicornParams->stopRising = 0;
}

void setDashDefaultValues(dash* dash) {
	dash->dash = 0;
	dash->dashStartTime = 0;
	dash->dashHeight = 0;
}

void setMiddle(rect* middle) {
	middle->x = SCREEN_WIDTH / 2;
	middle->y = SCREEN_HEIGHT / 2;
	middle->h = 2;
	middle->w = 2;
}

void setUnicornDefPos(rect* unicornRect, SDL_Surface *unicorn) {
	unicornRect->x = unicorn->w / 2;
	unicornRect->y = SCREEN_HEIGHT / 2;
	unicornRect->h = unicorn->h;
	unicornRect->w = unicorn->w;
}

void handleFpsAndTime(game* game) {
	game->worldTime += game->delta;

	game->fpsTimer += game->delta;
	if (game->fpsTimer > 0.5) {
		game->fps = game->frames * 2;
		game->frames = 0;
		game->fpsTimer -= 0.5;
	};
}

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	int t1, t2, rc, keyReleased, posSaved;
	jump jump;
	dash dash;
	game game;
	unicorn unicornParams;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *unicorn, *ground, *obstacle, *platform, *stalactite, *bumper;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	rect obstacles[5], unicornRect, platforms[5], middleOfTheScreen, stalactites[2], bumpers[2];

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe³noekranowy / fullscreen mode
	//rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Robot Unicorn Attack");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	unicorn = SDL_LoadBMP("./unicorn.bmp");
	if(unicorn == NULL) {
		printf("SDL_LoadBMP(unicorn.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};	
	
	ground = SDL_LoadBMP("./ground.bmp");
	if(ground == NULL) {
		printf("SDL_LoadBMP(ground.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};	
	
	obstacle = SDL_LoadBMP("./obstacle.bmp");
	if(obstacle == NULL) {
		printf("SDL_LoadBMP(obstacle.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};	
	
	platform = SDL_LoadBMP("./platform1.bmp");
	if(platform == NULL) {
		printf("SDL_LoadBMP(platform.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};	
	
	stalactite = SDL_LoadBMP("./stalactite.bmp");
	if(stalactite == NULL) {
		printf("SDL_LoadBMP(stalactite.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};	
	
	bumper = SDL_LoadBMP("./bumper.bmp");
	if(bumper == NULL) {
		printf("SDL_LoadBMP(bumper.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int bialy = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);

	t1 = SDL_GetTicks();

	game.quit = 0;
	game.newGame = 1;

	while(!game.quit) {
		if (game.newGame) {
			setGameDefaultValues(&game);				//setting up starting values
			setUnicornDefaultValues(&unicornParams);
			setJumpDefaultValues(&jump);
			setDashDefaultValues(&dash);
			setMiddle(&middleOfTheScreen);
			setUnicornDefPos(&unicornRect, unicorn); 
			unicornParams.unicornOnGroundY = SCREEN_HEIGHT - unicorn->h / 2;
			keyReleased = 1;
			posSaved = 0;
			game.stalacNr = 2;
			game.bumpersNr = 2;
			game.platformsNr = 5;
														//creating level - setting up platforms positions
			for (int i = 0; i < game.platformsNr; i++) {
				platforms[i].w = platform->w;
				platforms[i].h = platform->h;
				bumpers[i % game.bumpersNr].w = bumper->w;
				bumpers[i % game.bumpersNr].h = bumper->h;
				stalactites[i % game.stalacNr].w = stalactite->w;
				stalactites[i % game.stalacNr].h = stalactite->h;
			}
			platforms[0].x = 300;
			platforms[0].y = -200;
			platforms[1].x = 700;
			platforms[1].y = 50;
			platforms[2].x = 1500;
			platforms[2].y = -100;
			platforms[3].x = 1800;
			platforms[3].y = 100;
			platforms[4].x = 2500;
			platforms[4].y = -50;
													//setting up vertical scrolling params
			for (int i = 0; i < game.platformsNr; i++) {
				platforms[i].distanceFromCamera = middleOfTheScreen.y - platforms[i].y;
			}
		}

		t2 = SDL_GetTicks();

		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		game.delta = (t2 - t1) * 0.001;
		t1 = t2;

		handleFpsAndTime(&game);

		SDL_FillRect(screen, NULL, bialy);	//setting up background color
		
		//drawing unicorn
		DrawSurface(screen, unicorn,
			unicornRect.x, unicornRect.y);				

		//setting up obstacles on platforms
		bumpers[0].x = platforms[1].x + (platform->w / 2 - bumper->w / 2);
		bumpers[0].y = platforms[1].y - (platform->h / 2 + bumper->h / 2);
		bumpers[1].x = platforms[2].x + (platform->w / 2 - bumper->w / 2);
		bumpers[1].y = platforms[2].y - (platform->h / 2 + bumper->h / 2);
		stalactites[0].x = platforms[1].x;
		stalactites[0].y = platforms[1].y - 250;
		stalactites[1].x = platforms[3].x + platform->w / 2;
		stalactites[1].y = platforms[3].y - 250;

		//handling collision detection
		handleCollision(&unicornRect, platforms, &unicornParams, game.delta, game.platformsNr);
		handleCollision(&unicornRect, bumpers, &unicornParams, game.delta, game.bumpersNr);
		handleCollision(&unicornRect, stalactites, &unicornParams, game.delta, game.stalacNr);

		for (int i = 0; i < game.platformsNr; i++) {
			if (isColliding(unicornRect, platforms[i]) == 2 || isColliding(unicornRect, bumpers[i % game.bumpersNr]) == 2
				|| isColliding(unicornRect, stalactites[i % game.stalacNr]) == 2) {
				unicornParams.stopFalling = 1;
			}
			if (isColliding(unicornRect, platforms[i]) == 3 || isColliding(unicornRect, bumpers[i % game.bumpersNr]) == 3
				|| isColliding(unicornRect, stalactites[i % game.stalacNr]) == 3 || unicornRect.y < stalactites[1].y + 50) {
				unicornParams.stopRising = 1;
			}
		}

		//drawing level
		drawRects(screen, platform, platforms, game.platformsNr);
		drawRects(screen, bumper, bumpers, game.bumpersNr);
		drawRects(screen, stalactite, stalactites, game.stalacNr);
		if (!unicornParams.stopUnicorn) {
			moveRects(platforms, &game, game.platformsNr);
		}
		unicornParams.stopUnicorn = 0;


		unicornMovment(&unicornRect, &jump, &dash, &game, &unicornParams);

		cameraScrolling(&middleOfTheScreen, unicornRect, platforms, game.delta, game.platformsNr);
		
		// tekst informacyjny / info text
		DrawRectangle(screen, (SCREEN_WIDTH - (SCREEN_WIDTH - 8) / 3) - 4, 4, (SCREEN_WIDTH - 8) / 3, 36, czerwony, czarny);
		sprintf(text, "%.1lf s %.0lf klatek / s", game.worldTime, game.fps);
		DrawString(screen, (SCREEN_WIDTH - (SCREEN_WIDTH - 8) / 3), 10, text, charset);
		sprintf(text, "Esc - wyjscie n - restart");
		DrawString(screen, (SCREEN_WIDTH - (SCREEN_WIDTH - 8) / 3), 26, text, charset);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) game.quit = 1;
					else if (event.key.keysym.sym == SDLK_n) game.newGame = 1;
					else if (event.key.keysym.sym == SDLK_d) {
						game.testingControls = !game.testingControls;
						game.levelSpeed = 0;
					}
					if (game.testingControls) {
						if (event.key.keysym.sym == SDLK_UP) {
							unicornParams.flySpeed = -FLY_SPEED;
						}
						else if (event.key.keysym.sym == SDLK_DOWN) {
							unicornParams.flySpeed = FLY_SPEED;
						}
						else if (event.key.keysym.sym == SDLK_RIGHT) {
							game.levelSpeed = LEVEL_SPEED;
						}
					}
					else {
						if (event.key.keysym.sym == SDLK_z) {
							if (jump.jumpsInARow < 2 && !dash.dash) {	//can't jump while dashing and used both jumps
								if (keyReleased) {
									jump.jump = 1;
									keyReleased = 0;
									if (jump.takeCurrentHeight) {		//taking unicorn y pos when jump pressed
										jump.jumpAbsoluteHeight = jump.jumpHeight - (SCREEN_HEIGHT - unicornRect.y);
										jump.takeCurrentHeight = 0;
									}
								}
								if (jump.addToJump < ADD_TO_JUMP_MAX) {
									jump.addToJump += JUMP_INCRESE * game.delta;
								}
							}
						}
						if (event.key.keysym.sym == SDLK_x) {
							if (dash.canDash) {
								dash.dash = 1;
								dash.dashStartTime = game.worldTime;	//taking current time
								dash.dashHeight = unicornRect.y;		//taking current unicorn y pos
								dash.canDash = 0;
							}
						}
					}
					break;
				case SDL_KEYUP:
					if (game.testingControls) {
						if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_UP) unicornParams.flySpeed = 0;
						else if (event.key.keysym.sym == SDLK_RIGHT) game.levelSpeed = 0;
					}
					else {
						if (event.key.keysym.sym == SDLK_z) {		//if jump key release
							jump.takeCurrentHeight = 1;
							keyReleased = 1;
							jump.jumpsInARow++;
						}
					}
					break;
				case SDL_QUIT:
					game.quit = 1;
					break;
			};
		};
		game.frames++;
	};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	};
