#include "bsp_led.h"

static void _Led_Init(BspLedDef *pLed);
static void _Led_On(BspLedDef *pLed);
static void _Led_Off(BspLedDef *pLed);
static void _Led_Toggle(BspLedDef *pLed);

BspLedConDef bspLedCon = {
    _Led_Init,
    _Led_On,
    _Led_Off,
    _Led_Toggle,
};

static void _Led_Init(BspLedDef *pLed)
{
    if (pLed == 0) {
        return;
    }

    pLed->outputLevel = !pLed->activeLevel;
}

static void _Led_On(BspLedDef *pLed)
{
    if (pLed == 0) {
        return;
    }

    pLed->outputLevel = pLed->activeLevel;

    if (pLed->onCallback != 0) {
        pLed->onCallback();
    }
}

static void _Led_Off(BspLedDef *pLed)
{
    if (pLed == 0) {
        return;
    }

    pLed->outputLevel = !pLed->activeLevel;

    if (pLed->offCallback != 0) {
        pLed->offCallback();
    }
}

static void _Led_Toggle(BspLedDef *pLed)
{
    if (pLed == 0) {
        return;
    }

    if (pLed->outputLevel == pLed->activeLevel) {
        _Led_Off(pLed);
    } else {
        _Led_On(pLed);
    }
}
