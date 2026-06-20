#ifndef _BSP_LED_H_
#define _BSP_LED_H_

typedef struct _BspLedDef BspLedDef;

typedef struct {
    void (*init)(BspLedDef *pLed);
    void (*on)(BspLedDef *pLed);
    void (*off)(BspLedDef *pLed);
    void (*toggle)(BspLedDef *pLed);
} BspLedConDef;

struct _BspLedDef {
    unsigned char activeLevel;
    unsigned char outputLevel;
    void (*onCallback)(void);
    void (*offCallback)(void);
};

extern BspLedConDef bspLedCon;
extern BspLedDef ledRun;
extern BspLedDef ledError;

#endif /* _BSP_LED_H_ */
