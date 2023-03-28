// stworz funkcje ktora bedzie zamieniala strukture webPlayerInfo na stringa i vice versa
// w tym pliku nic nie zmieniasz, piszesz tylko w pliku encoder_decoder.c w folderze src
// w mainie mozesz sobie printowac poszczegolne rzeczy zeby sprawdzic czy dziala
// pisz do mnie jak cokolwiek nie bedziesz wiedziala
// kocham cie

typedef struct webPlayerInfo {
    int posX;
    int posY;
    int shot;   // 1 albo 0, tak jak boolean
} webPlayerInfo;

webPlayerInfo *decode(char *info);

char *encode(webPlayerInfo info);
