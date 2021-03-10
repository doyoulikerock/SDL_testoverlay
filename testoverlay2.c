/*
  Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
/********************************************************************************
 *                                                                              *
 * Test of the overlay used for moved pictures, test more closed to real life.  *
 * Running trojan moose :) Coded by Mike Gorchak.                               *
 *                                                                              *
 ********************************************************************************/

#include <stdlib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "SDL.h"

#define DBG_HSCHOI( fmt, args...)  printf("%s:%s:%d:" fmt, __FILE__, __FUNCTION__, __LINE__, ##args)


#include "testyuv_cvt.h"

#define MOOSEPIC_W 64
#define MOOSEPIC_H 88

#define MOOSEFRAME_SIZE (MOOSEPIC_W * MOOSEPIC_H)
#define MOOSEFRAMES_COUNT 10

SDL_Color MooseColors[84] = {
    {49, 49, 49, SDL_ALPHA_OPAQUE}
    , {66, 24, 0, SDL_ALPHA_OPAQUE}
    , {66, 33, 0, SDL_ALPHA_OPAQUE}
    , {66, 66, 66, SDL_ALPHA_OPAQUE}
    ,
    {66, 115, 49, SDL_ALPHA_OPAQUE}
    , {74, 33, 0, SDL_ALPHA_OPAQUE}
    , {74, 41, 16, SDL_ALPHA_OPAQUE}
    , {82, 33, 8, SDL_ALPHA_OPAQUE}
    ,
    {82, 41, 8, SDL_ALPHA_OPAQUE}
    , {82, 49, 16, SDL_ALPHA_OPAQUE}
    , {82, 82, 82, SDL_ALPHA_OPAQUE}
    , {90, 41, 8, SDL_ALPHA_OPAQUE}
    ,
    {90, 41, 16, SDL_ALPHA_OPAQUE}
    , {90, 57, 24, SDL_ALPHA_OPAQUE}
    , {99, 49, 16, SDL_ALPHA_OPAQUE}
    , {99, 66, 24, SDL_ALPHA_OPAQUE}
    ,
    {99, 66, 33, SDL_ALPHA_OPAQUE}
    , {99, 74, 33, SDL_ALPHA_OPAQUE}
    , {107, 57, 24, SDL_ALPHA_OPAQUE}
    , {107, 82, 41, SDL_ALPHA_OPAQUE}
    ,
    {115, 57, 33, SDL_ALPHA_OPAQUE}
    , {115, 66, 33, SDL_ALPHA_OPAQUE}
    , {115, 66, 41, SDL_ALPHA_OPAQUE}
    , {115, 74, 0, SDL_ALPHA_OPAQUE}
    ,
    {115, 90, 49, SDL_ALPHA_OPAQUE}
    , {115, 115, 115, SDL_ALPHA_OPAQUE}
    , {123, 82, 0, SDL_ALPHA_OPAQUE}
    , {123, 99, 57, SDL_ALPHA_OPAQUE}
    ,
    {132, 66, 41, SDL_ALPHA_OPAQUE}
    , {132, 74, 41, SDL_ALPHA_OPAQUE}
    , {132, 90, 8, SDL_ALPHA_OPAQUE}
    , {132, 99, 33, SDL_ALPHA_OPAQUE}
    ,
    {132, 99, 66, SDL_ALPHA_OPAQUE}
    , {132, 107, 66, SDL_ALPHA_OPAQUE}
    , {140, 74, 49, SDL_ALPHA_OPAQUE}
    , {140, 99, 16, SDL_ALPHA_OPAQUE}
    ,
    {140, 107, 74, SDL_ALPHA_OPAQUE}
    , {140, 115, 74, SDL_ALPHA_OPAQUE}
    , {148, 107, 24, SDL_ALPHA_OPAQUE}
    , {148, 115, 82, SDL_ALPHA_OPAQUE}
    ,
    {148, 123, 74, SDL_ALPHA_OPAQUE}
    , {148, 123, 90, SDL_ALPHA_OPAQUE}
    , {156, 115, 33, SDL_ALPHA_OPAQUE}
    , {156, 115, 90, SDL_ALPHA_OPAQUE}
    ,
    {156, 123, 82, SDL_ALPHA_OPAQUE}
    , {156, 132, 82, SDL_ALPHA_OPAQUE}
    , {156, 132, 99, SDL_ALPHA_OPAQUE}
    , {156, 156, 156, SDL_ALPHA_OPAQUE}
    ,
    {165, 123, 49, SDL_ALPHA_OPAQUE}
    , {165, 123, 90, SDL_ALPHA_OPAQUE}
    , {165, 132, 82, SDL_ALPHA_OPAQUE}
    , {165, 132, 90, SDL_ALPHA_OPAQUE}
    ,
    {165, 132, 99, SDL_ALPHA_OPAQUE}
    , {165, 140, 90, SDL_ALPHA_OPAQUE}
    , {173, 132, 57, SDL_ALPHA_OPAQUE}
    , {173, 132, 99, SDL_ALPHA_OPAQUE}
    ,
    {173, 140, 107, SDL_ALPHA_OPAQUE}
    , {173, 140, 115, SDL_ALPHA_OPAQUE}
    , {173, 148, 99, SDL_ALPHA_OPAQUE}
    , {173, 173, 173, SDL_ALPHA_OPAQUE}
    ,
    {181, 140, 74, SDL_ALPHA_OPAQUE}
    , {181, 148, 115, SDL_ALPHA_OPAQUE}
    , {181, 148, 123, SDL_ALPHA_OPAQUE}
    , {181, 156, 107, SDL_ALPHA_OPAQUE}
    ,
    {189, 148, 123, SDL_ALPHA_OPAQUE}
    , {189, 156, 82, SDL_ALPHA_OPAQUE}
    , {189, 156, 123, SDL_ALPHA_OPAQUE}
    , {189, 156, 132, SDL_ALPHA_OPAQUE}
    ,
    {189, 189, 189, SDL_ALPHA_OPAQUE}
    , {198, 156, 123, SDL_ALPHA_OPAQUE}
    , {198, 165, 132, SDL_ALPHA_OPAQUE}
    , {206, 165, 99, SDL_ALPHA_OPAQUE}
    ,
    {206, 165, 132, SDL_ALPHA_OPAQUE}
    , {206, 173, 140, SDL_ALPHA_OPAQUE}
    , {206, 206, 206, SDL_ALPHA_OPAQUE}
    , {214, 173, 115, SDL_ALPHA_OPAQUE}
    ,
    {214, 173, 140, SDL_ALPHA_OPAQUE}
    , {222, 181, 148, SDL_ALPHA_OPAQUE}
    , {222, 189, 132, SDL_ALPHA_OPAQUE}
    , {222, 189, 156, SDL_ALPHA_OPAQUE}
    ,
    {222, 222, 222, SDL_ALPHA_OPAQUE}
    , {231, 198, 165, SDL_ALPHA_OPAQUE}
    , {231, 231, 231, SDL_ALPHA_OPAQUE}
    , {239, 206, 173, SDL_ALPHA_OPAQUE}
};

Uint8 MooseFrame[MOOSEFRAMES_COUNT][MOOSEFRAME_SIZE*2];

Uint8 MooseFrameARGB[MOOSEFRAMES_COUNT][MOOSEFRAME_SIZE*4];
SDL_Texture *MooseTexture;
SDL_Texture *otherTexture;
SDL_Rect displayrect;
SDL_Rect otherRect;

int window_w;
int window_h;
SDL_Window *window;
SDL_Renderer *renderer;
int paused = 0;
int i;
SDL_bool done = SDL_FALSE;
static int fpsdelay;

//#define TEST_2RENDERER
#if defined(TEST_2RENDERER)
SDL_Renderer *otherRenderer;
#endif


/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{
    SDL_Quit();
    exit(rc);
}

static void
PrintUsage(char *argv0)
{
    SDL_Log("Usage: %s [arg] [arg] [arg] ...\n", argv0);
    SDL_Log("\n");
    SDL_Log("Where 'arg' is any of the following options:\n");
    SDL_Log("\n");
    SDL_Log("    -fps <frames per second>\n");
    SDL_Log("    -nodelay\n");
    SDL_Log("    -format <fmt> (one of the: YV12, IYUV, YUY2, UYVY, YVYU)\n");
    SDL_Log("    -scale <scale factor> (initial scale of the overlay)\n");
    SDL_Log("    -help (shows this help)\n");
    SDL_Log("\n");
    SDL_Log("Press ESC to exit, or SPACE to freeze the movie while application running.\n");
    SDL_Log("\n");
}




static int num_objects =100;
static SDL_bool cycle_color;
static SDL_bool cycle_alpha;
static int cycle_direction = 1;
static int current_alpha = 255;
static int current_color = 255;
static SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;
void
DrawPoints(SDL_Renderer * renderer)
{
    int i;
    int x, y;
    SDL_Rect viewport;

    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);

    for (i = 0; i < num_objects * 4; ++i) {
        /* Cycle the color and alpha, if desired */
        if (cycle_color) {
            current_color += cycle_direction;
            if (current_color < 0) {
                current_color = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_color > 255) {
                current_color = 255;
                cycle_direction = -cycle_direction;
            }
        }
        if (cycle_alpha) {
            current_alpha += cycle_direction;
            if (current_alpha < 0) {
                current_alpha = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_alpha > 255) {
                current_alpha = 255;
                cycle_direction = -cycle_direction;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, (Uint8) current_color,
                               (Uint8) current_color, (Uint8) current_alpha);

        x = rand() % viewport.w;
        y = rand() % viewport.h;
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void
DrawLines(SDL_Renderer * renderer)
{
    int i;
    int x1, y1, x2, y2;
    SDL_Rect viewport;

    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);

    for (i = 0; i < num_objects; ++i) {
        /* Cycle the color and alpha, if desired */
        if (cycle_color) {
            current_color += cycle_direction;
            if (current_color < 0) {
                current_color = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_color > 255) {
                current_color = 255;
                cycle_direction = -cycle_direction;
            }
        }
        if (cycle_alpha) {
            current_alpha += cycle_direction;
            if (current_alpha < 0) {
                current_alpha = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_alpha > 255) {
                current_alpha = 255;
                cycle_direction = -cycle_direction;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, (Uint8) current_color,
                               (Uint8) current_color, (Uint8) current_alpha);

        if (i == 0) {
            SDL_RenderDrawLine(renderer, 0, 0, viewport.w - 1, viewport.h - 1);
            SDL_RenderDrawLine(renderer, 0, viewport.h - 1, viewport.w - 1, 0);
            SDL_RenderDrawLine(renderer, 0, viewport.h / 2, viewport.w - 1, viewport.h / 2);
            SDL_RenderDrawLine(renderer, viewport.w / 2, 0, viewport.w / 2, viewport.h - 1);
        } else {
            x1 = (rand() % (viewport.w*2)) - viewport.w;
            x2 = (rand() % (viewport.w*2)) - viewport.w;
            y1 = (rand() % (viewport.h*2)) - viewport.h;
            y2 = (rand() % (viewport.h*2)) - viewport.h;
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
    }
}

void
DrawRects(SDL_Renderer * renderer)
{
    int i;
    SDL_Rect rect;
    SDL_Rect viewport;
    static int cnt=0;

    if(cnt++ % 10 < 5 ) return;
    
    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);
#if 0
    for (i = 0; i < num_objects / 4; ++i) {
        /* Cycle the color and alpha, if desired */
        if (cycle_color) {
            current_color += cycle_direction;
            if (current_color < 0) {
                current_color = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_color > 255) {
                current_color = 255;
                cycle_direction = -cycle_direction;
            }
        }
        if (cycle_alpha) {
            current_alpha += cycle_direction;
            if (current_alpha < 0) {
                current_alpha = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_alpha > 255) {
                current_alpha = 255;
                cycle_direction = -cycle_direction;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, (Uint8) current_color,
                               (Uint8) current_color, (Uint8) current_alpha);

        rect.w = rand() % (viewport.h / 2);
        rect.h = rand() % (viewport.h / 2);
        rect.x = (rand() % (viewport.w*2) - viewport.w) - (rect.w / 2);
        rect.y = (rand() % (viewport.h*2) - viewport.h) - (rect.h / 2);
        SDL_RenderFillRect(renderer, &rect);

    }

    #else
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 128);
    rect.w = 100;
    rect.h = 100;
    rect.x = 50 + cnt;
    rect.y = 50;
    SDL_RenderFillRect(renderer, &rect);
    #endif
}



void
loop()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_WINDOWEVENT:
            DBG_HSCHOI("SDL_WINDOWEVENT event(%d)\n", event.window.event);

            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_RenderSetViewport(renderer, NULL);
                displayrect.w = window_w = event.window.data1;
                displayrect.h = window_h = event.window.data2;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            DBG_HSCHOI("SDL_MOUSEBUTTONDOWN event\n");
            displayrect.x = event.button.x - window_w / 2;
            displayrect.y = event.button.y - window_h / 2;
            break;
        case SDL_MOUSEMOTION:
            DBG_HSCHOI("SDL_MOUSEMOTION event:%d,%d\n", event.motion.x, event.motion.y);
            if (event.motion.state) {
                displayrect.x = event.motion.x - window_w / 2;
                displayrect.y = event.motion.y - window_h / 2;
            }
            break;
        case SDL_KEYDOWN:
            DBG_HSCHOI("SDL_KEYDOWN event\n");
            if (event.key.keysym.sym == SDLK_SPACE) {
                paused = !paused;
                break;
            }
            if (event.key.keysym.sym != SDLK_ESCAPE) {
                break;
            }
        case SDL_QUIT:
            done = SDL_TRUE;
            break;
        }
    }

#ifndef __EMSCRIPTEN__
    SDL_Delay(fpsdelay);
#endif
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderClear(renderer);


    // bottom
    if (!paused) {
        i = (i + 1) % MOOSEFRAMES_COUNT;
        SDL_UpdateTexture(MooseTexture, NULL, MooseFrame[i], MOOSEPIC_W);

        i = (i + 1) % MOOSEFRAMES_COUNT;
        //SDL_UpdateTextureNative(SDL_Texture * texture,const SDL_Rect * rect,const void * pixels,int pitch)
        SDL_UpdateTexture(otherTexture, NULL, MooseFrameARGB[i], MOOSEPIC_W*4);
    }
    #if 1
    displayrect.w = 800;
    displayrect.h = 800;
    SDL_RenderCopy(renderer, MooseTexture, NULL, &displayrect);
    #endif
    
    otherRect.x = 400; //displayrect.x + displayrect.w + 100;
    otherRect.y = displayrect.y;
    otherRect.w = 800;
    otherRect.h = 800;
    SDL_RenderCopy(renderer, otherTexture, NULL, &otherRect);
    
        // up
    DrawRects(renderer);


    // DrawLines(renderer);
    // DrawPoints(renderer);
    

    SDL_RenderPresent(renderer);

#ifdef __EMSCRIPTEN__
    if (done) {
        emscripten_cancel_main_loop();
    }
#endif
}

int
main(int argc, char **argv)
{
    Uint8 *RawMooseData;
    SDL_RWops *handle;
    SDL_Window *window;
    SDL_Window *otherWindow;
    int j;
    int fps = 12;
    int nodelay = 0;
    int scale = 5;
    int count = 100;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_VERBOSE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return 3;
    }

    while (argc > 1) {
        if (SDL_strcmp(argv[1], "-fps") == 0) {
            if (argv[2]) {
                fps = SDL_atoi(argv[2]);
                if (fps == 0) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                            "The -fps option requires an argument [from 1 to 1000], default is 12.\n");
                    quit(10);
                }
                if ((fps < 0) || (fps > 1000)) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                            "The -fps option must be in range from 1 to 1000, default is 12.\n");
                    quit(10);
                }
                argv += 2;
                argc -= 2;
            } else {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                        "The -fps option requires an argument [from 1 to 1000], default is 12.\n");
                quit(10);
            }
        } else if (SDL_strcmp(argv[1], "-nodelay") == 0) {
            nodelay = 1;
            argv += 1;
            argc -= 1;
        } else if (SDL_strcmp(argv[1], "-scale") == 0) {
            if (argv[2]) {
                scale = SDL_atoi(argv[2]);
                if (scale == 0) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                            "The -scale option requires an argument [from 1 to 50], default is 5.\n");
                    quit(10);
                }
                if ((scale < 0) || (scale > 50)) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                            "The -scale option must be in range from 1 to 50, default is 5.\n");
                    quit(10);
                }
                argv += 2;
                argc -= 2;
            } else {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                        "The -fps option requires an argument [from 1 to 1000], default is 12.\n");
                quit(10);
            }
        } else if ((SDL_strcmp(argv[1], "-help") == 0)
                   || (SDL_strcmp(argv[1], "-h") == 0)) {
            PrintUsage(argv[0]);
            quit(0);
        } else {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unrecognized option: %s.\n", argv[1]);
            quit(10);
        }
        break;
    }

    RawMooseData = (Uint8 *) SDL_malloc(MOOSEFRAME_SIZE * MOOSEFRAMES_COUNT);
    if (RawMooseData == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't allocate memory for movie !\n");
        quit(1);
    }

    /* load the trojan moose images */
    handle = SDL_RWFromFile("moose.dat", "rb");
    if (handle == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't find the file moose.dat !\n");
        SDL_free(RawMooseData);
        quit(2);
    }

    SDL_RWread(handle, RawMooseData, MOOSEFRAME_SIZE, MOOSEFRAMES_COUNT);

    SDL_RWclose(handle);

    /* Create the window and renderer */
    window_w = 1920; //MOOSEPIC_W * scale;
    window_h = 1080; //MOOSEPIC_H * scale;
    window = SDL_CreateWindow("Happy Moose",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              window_w, window_h,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set create window: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(4);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set create renderer: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(4);
    }

#if defined(TEST_2RENDERER)
    otherWindow = SDL_CreateWindow("OSD",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              window_w, window_h,
                              SDL_WINDOW_RESIZABLE);
    if (!otherWindow) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set create window: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(4);
    }

    otherRenderer = SDL_CreateRenderer(otherWindow, -1, 0);
    if (!otherRenderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set create renderer: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(4);
    }
    #endif

    

    MooseTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, MOOSEPIC_W, MOOSEPIC_H);
    if (!MooseTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set create texture: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(5);
    }

    otherTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, MOOSEPIC_W, MOOSEPIC_H);
    if (!otherTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set create texture: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(5);
    }
    if(SDL_SetTextureAlphaMod(otherTexture, 255)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set alpha texture: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(5);

    }
    if(SDL_SetTextureBlendMode(otherTexture, SDL_BLENDMODE_BLEND)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set blend texture: %s\n", SDL_GetError());
        SDL_free(RawMooseData);
        quit(5);
    }
    
    memset(MooseFrameARGB, 0, sizeof(MooseFrameARGB));

    
    /* Uncomment this to check vertex color with a YUV texture */
    /* SDL_SetTextureColorMod(MooseTexture, 0xff, 0x80, 0x80); */

    for (i = 0; i < MOOSEFRAMES_COUNT; i++) {
        Uint8 MooseFrameRGB[MOOSEFRAME_SIZE*3];
        Uint8 *rgb;
        Uint8 *frame;
        Uint8 *p_argb = MooseFrameARGB[i];
        
        rgb = MooseFrameRGB;
        frame = RawMooseData + i * MOOSEFRAME_SIZE;
        for (j = 0; j < MOOSEFRAME_SIZE; ++j) {
            p_argb[2] = rgb[0] = MooseColors[frame[j]].r;
            p_argb[1] = rgb[1] = MooseColors[frame[j]].g;
            p_argb[0] = rgb[2] = MooseColors[frame[j]].b;
            rgb += 3;

            p_argb[3] = MOOSEFRAME_SIZE/3 < j ? 128 : 0;
            p_argb+=4;
        }
        ConvertRGBtoYUV(SDL_PIXELFORMAT_YV12, MooseFrameRGB, MOOSEPIC_W*3, MooseFrame[i], MOOSEPIC_W, MOOSEPIC_H,
            SDL_GetYUVConversionModeForResolution(MOOSEPIC_W, MOOSEPIC_H),
            0, 100);
    }

    SDL_free(RawMooseData);

    /* set the start frame */
    i = 0;
    if (nodelay) {
        fpsdelay = 0;
    } else {
        fpsdelay = 1000 / fps;
    }

    displayrect.x = 100;
    displayrect.y = 100;
    displayrect.w = window_w-100;
    displayrect.h = window_h-100;

    DBG_HSCHOI("%dx%d\n", window_w, window_h);

    /* Ignore key up events, they don't even get filtered */
    SDL_EventState(SDL_KEYUP, SDL_IGNORE);

    /* Loop, waiting for QUIT or RESIZE */
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, nodelay ? 0 : fps, 1);
#else
    while (!done ){ //&& count--> 0) {
        loop();
            }
#endif

    SDL_DestroyRenderer(renderer);
    quit(0);
    return 0;
}

/* vi: set ts=4 sw=4 expandtab: */
