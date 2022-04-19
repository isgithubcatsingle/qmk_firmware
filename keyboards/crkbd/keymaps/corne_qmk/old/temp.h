#include "keypos.h"

#define COMBO_BASE(NAME, BIND, KEYS, TIMEOUT) \
    combo_##NAME { \
        timeout-ms = <TIMEOUT>; \
        bindings = <BIND>; \
        key-positions = <KEYS>; \
        slow-release; \
    };
    

#define COMBO_S(NAME, BIND, KEYS) COMBO_BASE(NAME, BIND, KEYS, 100)
#define COMBO_F(NAME, BIND, KEYS) COMBO_BASE(NAME, BIND, KEYS, 50)

 / {
    combos {
        compatible = "zmk,combos";
/* List */
COMBO_F(word_delete, &macro_wd, P_BSPC P_SPACE);

COMBO_F(leftspace, &kp SPACE, P_V P_BSPC);
COMBO_F(leftenter, &kp ENT, P_D P_BSPC);

COMBO_F(copy, &K_COPY, P_C P_D);
COMBO_F(paste, &K_PASTE, P_D P_V);
COMBO_F(cut, &K_CUT, P_X P_C)
COMBO_F(undo, &K_UNDO, P_Z P_X)
COMBO_F(redo, &K_REDO, P_Z P_R)
COMBO_F(save, &kp LC(S), P_S P_T)

COMBO_F(exclam, &kp_EXCL, P_Q P_W)
COMBO_F(question, &QMARK, P_DOT P_FSLH)

}
};